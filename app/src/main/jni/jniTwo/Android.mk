LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
#LOCAL_ARM_MODE := arm
LOCAL_MODULE := TestJniMethodsTwo
#APP_BUILD_SCRIPT:=./Android.mk
LOCAL_LDLIBS    := -llog
LOCAL_SRC_FILES := com_xiaomakj_hellogcc_MuchJNIShow.cpp
include $(BUILD_SHARED_LIBRARY)