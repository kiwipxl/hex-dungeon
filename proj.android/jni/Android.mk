LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

ROOT_SRC_FILES := $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp)
ROOT_SRC_FILES := $(ROOT_SRC_FILES:$(LOCAL_PATH)/%=%)

INPUT_SRC_FILES := $(wildcard $(LOCAL_PATH)/../../Classes/input/*.cpp)
INPUT_SRC_FILES := $(INPUT_SRC_FILES:$(LOCAL_PATH)/%=%)

UTILITY_SRC_FILES := $(wildcard $(LOCAL_PATH)/../../Classes/utility/*.cpp)
UTILITY_SRC_FILES := $(UTILITY_SRC_FILES:$(LOCAL_PATH)/%=%)

ENTITIES_SRC_FILES := $(wildcard $(LOCAL_PATH)/../../Classes/entities/*.cpp)
ENTITIES_SRC_FILES := $(ENTITIES_SRC_FILES:$(LOCAL_PATH)/%=%)

LOCAL_SRC_FILES := $(ROOT_SRC_FILES)
LOCAL_SRC_FILES += $(INPUT_SRC_FILES)
LOCAL_SRC_FILES += $(UTILITY_SRC_FILES)
LOCAL_SRC_FILES += $(ENTITIES_SRC_FILES)
LOCAL_SRC_FILES += $(LOCAL_PATH)/../hellocpp/main.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
