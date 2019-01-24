
#ifndef BREAKPAD_H
#define BREAKPAD_H

#import <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef bool (*SwiftMinidumpCallback)(const char *dump_path, bool succeeded);

void setUpBreakpad(const char* path);
void setUpBreakpadWithCallback(const char* path, SwiftMinidumpCallback callback);

#ifdef __cplusplus
}
#endif

#endif //BREAKPAD_H



