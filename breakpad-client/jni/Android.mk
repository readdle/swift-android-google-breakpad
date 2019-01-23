LOCAL_PATH := $(call my-dir)

# If NDK_MODULE_PATH is defined, import the module, otherwise do a direct
# includes. This allows us to build in all scenarios easily.
ifneq ($(NDK_MODULE_PATH),)
  $(call import-module,google_breakpad)
else
  include $(LOCAL_PATH)/../breakpad/src/android/google_breakpad/Android.mk
endif
