#include "../breakpad.h"
#include "client/linux/handler/exception_handler.h"
#include "client/linux/handler/minidump_descriptor.h"

#include <android/log.h>
#include <sys/stat.h>

#define  LOG_TAG   "Breakpad"

static google_breakpad::ExceptionHandler* exceptionHandler = NULL;
static BreakPadCallback swiftCallback = NULL;

static char* fatalErrorMessagesPath = NULL;
static char* fatalErrorMessage = NULL;

bool DumpCallback(const google_breakpad::MinidumpDescriptor& descriptor,
                  void* context,
                  bool succeeded) {
  	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Dump path: %s\n", descriptor.path());

  	if (swiftCallback != NULL) {
  	    swiftCallback();
  	}

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

void setUpBreakpad(const char *path) {
   	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Configuring breakpad...");
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "path is %s", path);
    google_breakpad::MinidumpDescriptor descriptor(path);
    exceptionHandler = new google_breakpad::ExceptionHandler(descriptor, NULL, DumpCallback, NULL, true, -1);
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Breakpad is configured!");
}

void setUpBreakpadWithCallback(const char* path, const char* errorMessagePath, BreakPadCallback callback) {
    fatalErrorMessagesPath = (char*) malloc((strlen(errorMessagePath) + 1) * sizeof(char));
    strcpy(fatalErrorMessagesPath, errorMessagePath);
	swiftCallback = callback;
	setUpBreakpad(path);
}

void setBreakpadFatalErrorMessage(const char* message) {
	fatalErrorMessage = (char*) malloc((strlen(message) + 1) * sizeof(char));
	strcpy(fatalErrorMessage, message);
}
