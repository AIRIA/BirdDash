LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/base/BaseLayer.cpp \
                   ../../Classes/base/BaseScene.cpp \
                   ../../Classes/base/BaseSprite.cpp \
                   ../../Classes/base/BaseUserDefault.cpp \
                   ../../Classes/base/MaskLayer.cpp \
                   ../../Classes/base/BaseMenuSprite.cpp \
                   ../../Classes/common/VisibleRect.cpp \
                   ../../Classes/game/components/ExitWin.cpp \
                   ../../Classes/game/components/PauseLayer.cpp \
                   ../../Classes/game/components/ShakeBird.cpp \
                   ../../Classes/game/scenes/ClassicScene.cpp \
                   ../../Classes/game/scenes/SettingScene.cpp \
                   ../../Classes/game/scenes/SplashScene.cpp \
                   ../../Classes/game/utils/BirdUtil.cpp \
                   ../../Classes/game/GameMain.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static \
PluginProtocolStatic
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)

$(call import-module,plugin/publish/protocols/android)
