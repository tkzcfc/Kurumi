LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dlua_shared

LOCAL_MODULE_FILENAME := libcocos2dlua

LOCAL_SRC_FILES := \
../../../Classes/AppDelegate.cpp \
../../../Classes/ide-support/SimpleConfigParser.cpp \
../../../Classes/ide-support/RuntimeLuaImpl.cpp \
../../../Classes/ide-support/lua_debugger.c \
hellolua/main.cpp

# lua_function
LOCAL_SRC_FILES  += ../../../Classes/lua_function/LuaFunction.cpp \
                    ../../../Classes/lua_function/LuaFunctionBond.cpp \
                    ../../../Classes/lua_function/tolua_ext.cpp \

# gamecore
LOCAL_SRC_FILES  += ../../../Classes/gamecore/GameActor.cpp \
                    ../../../Classes/gamecore/GameCharacter.cpp \
                    ../../../Classes/gamecore/GameCharacterBox2d.cpp \
                    ../../../Classes/gamecore/GameMap.cpp \
                    ../../../Classes/gamecore/GameMath.cpp \
                    ../../../Classes/gamecore/GLES-Render.cpp \
                    ../../../Classes/gamecore/GameWord.cpp

# lua_modules/game
LOCAL_SRC_FILES  += ../../../Classes/lua_modules/game/lua_game.cpp


# lua_modules/net
LOCAL_SRC_FILES  += ../../../Classes/lua_modules/net/libuv/src/inet.c \
                    ../../../Classes/lua_modules/net/libuv/src/threadpool.c \
                    ../../../Classes/lua_modules/net/libuv/src/unix/android-ifaddrs.c \
                    ../../../Classes/lua_modules/net/libuv/src/unix/async.c \
                    ../../../Classes/lua_modules/net/libuv/src/unix/core.c \
                    ../../../Classes/lua_modules/net/libuv/src/unix/dl.c \
                    ../../../Classes/lua_modules/net/libuv/src/unix/fs.c \
                    ../../../Classes/lua_modules/net/libuv/src/unix/getaddrinfo.c \
                    ../../../Classes/lua_modules/net/libuv/src/unix/getnameinfo.c \
                    ../../../Classes/lua_modules/net/libuv/src/unix/linux-core.c \
                    ../../../Classes/lua_modules/net/libuv/src/unix/linux-inotify.c \
                    ../../../Classes/lua_modules/net/libuv/src/unix/linux-syscalls.c \
                    ../../../Classes/lua_modules/net/libuv/src/unix/loop-watcher.c \
                    ../../../Classes/lua_modules/net/libuv/src/unix/loop.c \
                    ../../../Classes/lua_modules/net/libuv/src/unix/pipe.c \
                    ../../../Classes/lua_modules/net/libuv/src/unix/poll.c \
                    ../../../Classes/lua_modules/net/libuv/src/unix/process.c \
                    ../../../Classes/lua_modules/net/libuv/src/unix/proctitle.c \
                    ../../../Classes/lua_modules/net/libuv/src/unix/pthread-fixes.c \
                    ../../../Classes/lua_modules/net/libuv/src/unix/signal.c \
                    ../../../Classes/lua_modules/net/libuv/src/unix/stream.c \
                    ../../../Classes/lua_modules/net/libuv/src/unix/tcp.c \
                    ../../../Classes/lua_modules/net/libuv/src/unix/thread.c \
                    ../../../Classes/lua_modules/net/libuv/src/unix/timer.c \
                    ../../../Classes/lua_modules/net/libuv/src/unix/tty.c \
                    ../../../Classes/lua_modules/net/libuv/src/unix/udp.c \
                    ../../../Classes/lua_modules/net/libuv/src/uv-common.c \
                    ../../../Classes/lua_modules/net/libuv/src/version.c \
                    ../../../Classes/lua_modules/net/libuv/src/fs-poll.c \
                    ../../../Classes/lua_modules/net/net_uv/base/Client.cpp \
                    ../../../Classes/lua_modules/net/net_uv/base/Common.cpp \
                    ../../../Classes/lua_modules/net/net_uv/base/Mutex.cpp \
                    ../../../Classes/lua_modules/net/net_uv/base/Runnable.cpp \
                    ../../../Classes/lua_modules/net/net_uv/base/Server.cpp \
                    ../../../Classes/lua_modules/net/net_uv/base/Session.cpp \
                    ../../../Classes/lua_modules/net/net_uv/base/SessionManager.cpp \
                    ../../../Classes/lua_modules/net/net_uv/base/Socket.cpp \
                    ../../../Classes/lua_modules/net/net_uv/base/md5.cpp \
                    ../../../Classes/lua_modules/net/net_uv/base/uv_func.cpp \
                    ../../../Classes/lua_modules/net/net_uv/tcp/TCPSession.cpp \
                    ../../../Classes/lua_modules/net/net_uv/tcp/TCPSocket.cpp \
                    ../../../Classes/lua_modules/net/net_uv/tcp/TCPClient.cpp \
                    ../../../Classes/lua_modules/net/net_uv/tcp/TCPServer.cpp \
                    ../../../Classes/lua_modules/net/net_uv/tcp/TCPUtils.cpp \
                    ../../../Classes/lua_modules/net/net_uv/kcp/KCPSession.cpp \
                    ../../../Classes/lua_modules/net/net_uv/kcp/KCPSocket.cpp \
                    ../../../Classes/lua_modules/net/net_uv/kcp/KCPSocketManager.cpp \
                    ../../../Classes/lua_modules/net/net_uv/kcp/KCPClient.cpp \
                    ../../../Classes/lua_modules/net/net_uv/kcp/KCPServer.cpp \
                    ../../../Classes/lua_modules/net/net_uv/kcp/KCPUtils.cpp \
                    ../../../Classes/lua_modules/net/net_uv/kcp/ikcp.c \
                    ../../../Classes/lua_modules/net/TCPLuaClient.cpp \
                    ../../../Classes/lua_modules/net/KCPLuaClient.cpp \
                    ../../../Classes/lua_modules/net/TCPLuaServer.cpp \
                    ../../../Classes/lua_modules/net/KCPLuaServer.cpp \
                    ../../../Classes/lua_modules/net/lua_net.cpp \


# lua_modules/pbc
LOCAL_SRC_FILES  += ../../../Classes/lua_modules/pbc/src/alloc.cpp \
                    ../../../Classes/lua_modules/pbc/src/array.cpp \
                    ../../../Classes/lua_modules/pbc/src/bootstrap.cpp \
                    ../../../Classes/lua_modules/pbc/src/context.cpp \
                    ../../../Classes/lua_modules/pbc/src/decode.cpp \
                    ../../../Classes/lua_modules/pbc/src/map.cpp \
                    ../../../Classes/lua_modules/pbc/src/pattern.cpp \
                    ../../../Classes/lua_modules/pbc/src/proto.cpp \
                    ../../../Classes/lua_modules/pbc/src/register.cpp \
                    ../../../Classes/lua_modules/pbc/src/rmessage.cpp \
                    ../../../Classes/lua_modules/pbc/src/stringpool.cpp \
                    ../../../Classes/lua_modules/pbc/src/varint.cpp \
                    ../../../Classes/lua_modules/pbc/src/wmessage.cpp \
                    ../../../Classes/lua_modules/pbc/binding/lua/pbc-lua.c


# lua_modules/bit
LOCAL_SRC_FILES  += ../../../Classes/lua_modules/bit/bit.c

# lua_modules/lfs
LOCAL_SRC_FILES  += ../../../Classes/lua_modules/lfs/lfs.c

# lua_modules/cjson
LOCAL_SRC_FILES  += ../../../Classes/lua_modules/cjson/fpconv.c \
                    ../../../Classes/lua_modules/cjson/lua_cjson.c \
                    ../../../Classes/lua_modules/cjson/strbuf.c

# lua_modules
LOCAL_SRC_FILES  += ../../../Classes/lua_modules/lua_modules.cpp



LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes \
                    $(LOCAL_PATH)/../../../Classes/lua_modules \
                    $(LOCAL_PATH)/../../../Classes/lua_modules/game \
                    $(LOCAL_PATH)/../../../Classes/lua_modules/net/libuv/include \
                    $(LOCAL_PATH)/../../../Classes/lua_modules/net/libuv/src \
                    $(LOCAL_PATH)/../../../Classes/lua_modules/net/net_uv \
					$(LOCAL_PATH)/../../../Classes/lua_modules/bit \
                    $(LOCAL_PATH)/../../../Classes/lua_modules/cjson \
                    $(LOCAL_PATH)/../../../Classes/lua_modules/pbc \
                    $(LOCAL_PATH)/../../../Classes/lua_modules/pbc/src \
                    $(LOCAL_PATH)/../../../Classes/lua_modules/pbc/pbc \
                    $(LOCAL_PATH)/../../../Classes/lua_modules/pbc/binding/lua \
                    $(LOCAL_PATH)/../../../Classes/lua_modules/lfs \


# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END

LOCAL_STATIC_LIBRARIES := cocos2d_lua_static
LOCAL_STATIC_LIBRARIES += cocos2d_simulator_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,scripting/lua-bindings/proj.android)
$(call import-module,tools/simulator/libsimulator/proj.android)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
