LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := breakpad_client
LOCAL_EXPORT_C_INCLUDES :=  $(LOCAL_PATH)/../breakpad-client/include
LOCAL_SRC_FILES := ../breakpad-client/libs/armeabi-v7a/libbreakpad_client.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := breakpad
LOCAL_SRC_FILES := ../breakpad.cpp
LOCAL_STATIC_LIBRARIES += breakpad_client

LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)
