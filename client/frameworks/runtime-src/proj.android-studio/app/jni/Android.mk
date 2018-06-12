LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#增加模块查找目录
$(call import-add-path,$(LOCAL_PATH)/../../../Classes)

LOCAL_MODULE := cocos2dlua_shared

LOCAL_MODULE_FILENAME := libcocos2dlua

LOCAL_SRC_FILES := \
../../../Classes/AppDelegate.cpp \
../../../Classes/ide-support/SimpleConfigParser.cpp \
../../../Classes/ide-support/RuntimeLuaImpl.cpp \
../../../Classes/ide-support/lua_debugger.c \
../../../Classes/net/Client.cpp \
../../../Classes/gamecore/GameActor.cpp \
../../../Classes/gamecore/GameMath.cpp \
../../../Classes/gamecore/GameWord.cpp \
../../../Classes/gamecore/SpeedController.cpp \
../../../Classes/lua_game.cpp \
hellolua/main.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes \
					$(LOCAL_PATH)/../../../Classes/lua-modules/net \
					$(LOCAL_PATH)/../../../Classes/lua-modules/net/libuv/include \
					$(LOCAL_PATH)/../../../Classes/lua-modules


# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END

LOCAL_STATIC_LIBRARIES := cocos2d_lua_static
LOCAL_STATIC_LIBRARIES += cocos2d_simulator_static
LOCAL_STATIC_LIBRARIES += lua_modules_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,scripting/lua-bindings/proj.android)
$(call import-module,tools/simulator/libsimulator/proj.android)
$(call import-module,lua-modules)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
