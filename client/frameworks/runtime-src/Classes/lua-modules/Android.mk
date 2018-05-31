
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := lua_modules_static
LOCAL_MODULE_FILENAME := libluamodules

LOCAL_SRC_FILES  += $(LOCAL_PATH)/lua_modules.cpp \
				 += $(LOCAL_PATH)/LuaFunction.cpp

LOCAL_SRC_FILES  += $(LOCAL_PATH)/bit/bit.c

LOCAL_SRC_FILES  += $(LOCAL_PATH)/lfs/lfs.c

LOCAL_SRC_FILES  += $(LOCAL_PATH)/cjson/fpconv.c \
                    $(LOCAL_PATH)/cjson/lua_cjson.c \
                    $(LOCAL_PATH)/cjson/strbuf.c

LOCAL_SRC_FILES  += $(LOCAL_PATH)/../deps/libuv/src/inet.c \
                    $(LOCAL_PATH)/../deps/libuv/src/threadpool.c \
                    $(LOCAL_PATH)/../deps/libuv/src/unix/android-ifaddrs.c \
                    $(LOCAL_PATH)/../deps/libuv/src/unix/async.c \
                    $(LOCAL_PATH)/../deps/libuv/src/unix/core.c \
                    $(LOCAL_PATH)/../deps/libuv/src/unix/dl.c \
                    $(LOCAL_PATH)/../deps/libuv/src/unix/fs.c \
                    $(LOCAL_PATH)/../deps/libuv/src/unix/getaddrinfo.c \
                    $(LOCAL_PATH)/../deps/libuv/src/unix/getnameinfo.c \
                    $(LOCAL_PATH)/../deps/libuv/src/unix/linux-core.c \
                    $(LOCAL_PATH)/../deps/libuv/src/unix/linux-inotify.c \
                    $(LOCAL_PATH)/../deps/libuv/src/unix/linux-syscalls.c \
                    $(LOCAL_PATH)/../deps/libuv/src/unix/loop-watcher.c \
                    $(LOCAL_PATH)/../deps/libuv/src/unix/loop.c \
                    $(LOCAL_PATH)/../deps/libuv/src/unix/pipe.c \
                    $(LOCAL_PATH)/../deps/libuv/src/unix/poll.c \
                    $(LOCAL_PATH)/../deps/libuv/src/unix/process.c \
                    $(LOCAL_PATH)/../deps/libuv/src/unix/proctitle.c \
                    $(LOCAL_PATH)/../deps/libuv/src/unix/pthread-fixes.c \
                    $(LOCAL_PATH)/../deps/libuv/src/unix/signal.c \
                    $(LOCAL_PATH)/../deps/libuv/src/unix/stream.c \
                    $(LOCAL_PATH)/../deps/libuv/src/unix/tcp.c \
                    $(LOCAL_PATH)/../deps/libuv/src/unix/thread.c \
                    $(LOCAL_PATH)/../deps/libuv/src/unix/timer.c \
                    $(LOCAL_PATH)/../deps/libuv/src/unix/tty.c \
                    $(LOCAL_PATH)/../deps/libuv/src/unix/udp.c \
                    $(LOCAL_PATH)/../deps/libuv/src/uv-common.c \
                    $(LOCAL_PATH)/../deps/libuv/src/version.c \
                    $(LOCAL_PATH)/../deps/libuv/src/fs-poll.c \
                    $(LOCAL_PATH)/net/tcpSocket/md5.cpp \
                    $(LOCAL_PATH)/net/tcpSocket/TCPClient.cpp \
                    $(LOCAL_PATH)/net/tcpSocket/TCPCommon.cpp \
                    $(LOCAL_PATH)/net/tcpSocket/TCPServer.cpp \
                    $(LOCAL_PATH)/net/tcpSocket/TCPSocket.cpp \
                    $(LOCAL_PATH)/net/tcpSocket/TCPUtils.cpp \
                    $(LOCAL_PATH)/net/Client.cpp \
                    $(LOCAL_PATH)/net/lua_net.cpp

LOCAL_SRC_FILES  += $(LOCAL_PATH)/pbc/src/alloc.cpp \
                    $(LOCAL_PATH)/pbc/src/array.cpp \
                    $(LOCAL_PATH)/pbc/src/bootstrap.cpp \
                    $(LOCAL_PATH)/pbc/src/context.cpp \
                    $(LOCAL_PATH)/pbc/src/decode.cpp \
                    $(LOCAL_PATH)/pbc/src/map.cpp \
                    $(LOCAL_PATH)/pbc/src/pattern.cpp \
                    $(LOCAL_PATH)/pbc/src/proto.cpp \
                    $(LOCAL_PATH)/pbc/src/register.cpp \
                    $(LOCAL_PATH)/pbc/src/rmessage.cpp \
                    $(LOCAL_PATH)/pbc/src/stringpool.cpp \
                    $(LOCAL_PATH)/pbc/src/varint.cpp \
                    $(LOCAL_PATH)/pbc/src/wmessage.cpp \
                    $(LOCAL_PATH)/pbc/binding/lua/pbc-lua.c

LOCAL_SRC_FILES  += $(LOCAL_PATH)/gamecore/GameActor.cpp \
                    $(LOCAL_PATH)/gamecore/GameMath.cpp \
                    $(LOCAL_PATH)/gamecore/GameWord.cpp \
                    $(LOCAL_PATH)/gamecore/lua_gamecore.cpp



LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/../../../cocos2d-x \
                    $(LOCAL_PATH)/../../../cocos2d-x/cocos \
                    $(LOCAL_PATH)/../../../cocos2d-x/cocos/editor-support \
                    $(LOCAL_PATH)/../../../cocos2d-x/cocos/platform/android \
                    $(LOCAL_PATH)/../../../cocos2d-x/cocos/scripting/lua-bindings/manual \
                    $(LOCAL_PATH)/../../../cocos2d-x/external \
                    $(LOCAL_PATH)/../../../cocos2d-x/external/curl/include/android \
                    $(LOCAL_PATH)/../../../cocos2d-x/external/freetype2/include/android/freetype2 \
                    $(LOCAL_PATH)/../../../cocos2d-x/external/lua/luajit/include \
                    $(LOCAL_PATH)/../../../cocos2d-x/external/lua/tolua \
                    $(LOCAL_PATH)/../deps \
                    $(LOCAL_PATH)/../deps/libuv/include \
                    $(LOCAL_PATH)/../deps/libuv/src \
                    $(LOCAL_PATH)/bit \
                    $(LOCAL_PATH)/cjson \
                    $(LOCAL_PATH)/pbc/ \
                    $(LOCAL_PATH)/pbc/src \
                    $(LOCAL_PATH)/pbc/pbc \
                    $(LOCAL_PATH)/pbc/binding/lua \
                    $(LOCAL_PATH)/lfs \
                    $(LOCAL_PATH)/net/tcpSocket \
                    $(LOCAL_PATH)/net \
                    $(LOCAL_PATH)/gamecore \
					

include $(BUILD_STATIC_LIBRARY)
