#include "include/breakpad.h"
#include <android/log.h>

#define  LOG_TAG   "Breakpad"


static google_breakpad::ExceptionHandler* exceptionHandler;
bool DumpCallback(const google_breakpad::MinidumpDescriptor& descriptor,
                  void* context,
                  bool succeeded) {


  __android_log_print(ANDROID_LOG_INFO, LOG_TAG,"Dump path: %s\n", descriptor.path());

  return succeeded;
}


void setUpBreakpad(const char *path) {
   __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Configuring breakpad...");



    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "path is %s", path);
    google_breakpad::MinidumpDescriptor descriptor(path);
    exceptionHandler = new google_breakpad::ExceptionHandler(descriptor, NULL, DumpCallback, NULL, true, -1);
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Breakpad is configured!");

}



