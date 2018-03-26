
#ifndef BREAKPAD_H
#define BREAKPAD_H

#ifdef __cplusplus

#include "../../breakpad/src/src/client/linux/handler/exception_handler.h"
#include "../../breakpad/src/src/client/linux/handler/minidump_descriptor.h"

extern "C" {

bool DumpCallback(const google_breakpad::MinidumpDescriptor& descriptor,
                  void* context,
                  bool succeeded);
#endif

void setUpBreakpad(const char* );
void Crash();
#ifdef __cplusplus
}
#endif

#endif //BREAKPAD_H



