#include $(app-root-dir)jniOne/Android.mk
#include $(app-root-dir)jniTwo/Android.mk


LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
#LOCAL_ARM_MODE := arm
LOCAL_MODULE := TestJniMethodsOne
#APP_BUILD_SCRIPT:=./Android.mk
LOCAL_LDLIBS    := -llog
LOCAL_SRC_FILES := jniOne/com_xiaomakj_hellogcc_TestJniMethods.c
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
#LOCAL_ARM_MODE := arm
LOCAL_MODULE := TestJniMethodsTwo
#APP_BUILD_SCRIPT:=./Android.mk
LOCAL_LDLIBS    := -llog
LOCAL_SRC_FILES := jniTwo/com_xiaomakj_hellogcc_MuchJNIShow.cpp
include $(BUILD_SHARED_LIBRARY)