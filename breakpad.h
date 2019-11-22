
#ifndef BREAKPAD_H
#define BREAKPAD_H

#import <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*BreakPadCallback)();

void setUpBreakpad(const char* path);
void setUpBreakpadWithCallback(const char* path, const char* errorMessagePath, BreakPadCallback callback);
void setBreakpadFatalErrorMessage(const char* message);

#ifdef __cplusplus
}
#endif

#endif //BREAKPAD_H



