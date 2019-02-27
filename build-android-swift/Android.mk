LOCAL_PATH := $(call my-dir)

include $(LOCAL_PATH)/src/android/google_breakpad/Android.mk

include $(CLEAR_VARS)
LOCAL_MODULE := breakpad
LOCAL_SRC_FILES := ../breakpad.cpp
LOCAL_STATIC_LIBRARIES += breakpad_client

LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)
