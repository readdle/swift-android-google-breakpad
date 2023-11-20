#include "breakpad.h"
#include "client/linux/handler/exception_handler.h"
#include "client/linux/handler/minidump_descriptor.h"

#include <android/log.h>
#include <sys/stat.h>

#include <jni.h>
#include <string>
#include <malloc.h>
#include <dlfcn.h>

#define LOG_TAG                             "Breakpad"
#define CRASHREPORTER_ANNOTATIONS_VERSION   5
#define CRASHREPORTER_ANNOTATIONS_SECTION   "__crash_info"

struct crashreporter_annotations_t {
    uint64_t version;          // unsigned long
    uint64_t message;          // char *
    uint64_t signature_string; // char *
    uint64_t backtrace;        // char *
    uint64_t message2;         // char *
    uint64_t thread;           // uint64_t
    uint64_t dialog_mode;      // unsigned int
    uint64_t abort_cause;      // unsigned int
};

const crashreporter_annotations_t *gCRAnnotations = NULL;

static inline const char *CRGetCrashLogMessage() {
    if (gCRAnnotations != NULL) {
        return reinterpret_cast<const char *>(gCRAnnotations->message);      
    }
    return NULL;
}

static google_breakpad::ExceptionHandler* exceptionHandler = NULL;

static char* fatalErrorMessagesPath = NULL;

bool DumpCallback(const google_breakpad::MinidumpDescriptor& descriptor,
                  void* context,
                  bool succeeded) {
  	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Dump path: %s\n", descriptor.path());

    const char* fatalErrorMessage = CRGetCrashLogMessage();
  	if (fatalErrorMessage != NULL) {
        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Fatal error message: %s\n", fatalErrorMessage);

        struct stat file_info;
        if (stat(descriptor.path(), &file_info) != 0) {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Can't get file stats from dump");
            return succeeded;
        }

        char sbuf[strlen(fatalErrorMessagesPath) + 20];
        int len = sprintf(sbuf, "%s/%ld", fatalErrorMessagesPath, file_info.st_mtime);

        FILE * pFile;
        pFile = fopen(sbuf, "w");
        if (pFile != NULL) {
            fputs(fatalErrorMessage, pFile);
            fclose(pFile);
            __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Fatal error written for: %s\n", sbuf);
        }
        else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "fopen failed for description file: %s\n", sbuf);
        }
  	}
  	else {
        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "No fatal error message");
  	}
  	return succeeded;
}

void setUpBreakpad(const char* path, const char* errorMessagePath) {
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Configuring breakpad...");
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "path is %s", path);
    fatalErrorMessagesPath = (char*) malloc((strlen(errorMessagePath) + 1) * sizeof(char));
    strcpy(fatalErrorMessagesPath, errorMessagePath);

    google_breakpad::MinidumpDescriptor descriptor(path);
    exceptionHandler = new google_breakpad::ExceptionHandler(descriptor, NULL, DumpCallback, NULL, true, -1);

    /* find the address of gCRAnnotations struct*/
    auto* ptr = dlsym(RTLD_DEFAULT, "gCRAnnotations");
    if (ptr != NULL) {
        gCRAnnotations = reinterpret_cast<const crashreporter_annotations_t *>(ptr);
        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "gCRAnnotations saved sucessfully \n");        
    }
    else {
        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Can't find gCRAnnotations! \n");           
    }

    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Breakpad is configured!");
}
