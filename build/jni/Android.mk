LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := breakpad
LOCAL_SRC_FILES := breakpad.cpp
LOCAL_STATIC_LIBRARIES += breakpad_client

LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)

# If NDK_MODULE_PATH is defined, import the module, otherwise do a direct
# includes. This allows us to build in all scenarios easily.
ifneq ($(NDK_MODULE_PATH),)
  $(call import-module,google_breakpad)
else
  include $(LOCAL_PATH)/../breakpad/src/android/google_breakpad/Android.mk
endif
