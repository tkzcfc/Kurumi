#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/
cmake_minimum_required(VERSION 3.6)

set(APP_NAME kurumi)
  
project(${APP_NAME})

if(XCODE)
    if(NOT DEFINED CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET)
        SET (CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET 9.0)
    endif()
endif()

set(RUNTIME_SRC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/runtime-src)
set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x)
set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

include(CocosBuildSet)
set(BUILD_LUA_LIBS ON)
add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)

# script and source files info, not need to compile
set(res_res_folders
    "${CMAKE_CURRENT_SOURCE_DIR}/res"
    )
set(res_src_folders
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    )
if(APPLE OR VS)
    cocos_mark_multi_resources(res_res RES_TO "Resources/res" FOLDERS ${res_res_folders})
    cocos_mark_multi_resources(res_src RES_TO "Resources/src" FOLDERS ${res_src_folders})
    set(cc_common_res ${res_res} ${res_src} ${res_script})
endif()

################################################# record sources, headers#################################################
set(GAME_HEADER ${RUNTIME_SRC_ROOT}/Classes/AppDelegate.h)
set(GAME_SOURCE ${RUNTIME_SRC_ROOT}/Classes/AppDelegate.cpp)

set(GAME_HEADER 
    ${RUNTIME_SRC_ROOT}/Classes/AppDelegate.h
    ${RUNTIME_SRC_ROOT}/Classes/lua_function/LuaFunction.h
    ${RUNTIME_SRC_ROOT}/Classes/lua_function/LuaFunctionBond.h
    ${RUNTIME_SRC_ROOT}/Classes/lua_function/tolua_ext.h
    ${RUNTIME_SRC_ROOT}/Classes/lua_modules/custom_lua_modules.h
    ${RUNTIME_SRC_ROOT}/Classes/lua_modules/game/lua_game.h
    ${RUNTIME_SRC_ROOT}/Classes/net_uv_cc/CCClient.h
    ${RUNTIME_SRC_ROOT}/Classes/net_uv_cc/CCNetClient.h
    ${RUNTIME_SRC_ROOT}/Classes/foundation/GTools.h
    ${RUNTIME_SRC_ROOT}/Classes/test/TestScene.h
    ${RUNTIME_SRC_ROOT}/Classes/test/TestScene1.h
)


set(GAME_SOURCE 
    ${RUNTIME_SRC_ROOT}/Classes/AppDelegate.cpp
    ${RUNTIME_SRC_ROOT}/Classes/lua_function/LuaFunction.cpp
    ${RUNTIME_SRC_ROOT}/Classes/lua_function/LuaFunctionBond.cpp
    ${RUNTIME_SRC_ROOT}/Classes/lua_function/tolua_ext.cpp
    ${RUNTIME_SRC_ROOT}/Classes/lua_modules/custom_lua_modules.cpp
    ${RUNTIME_SRC_ROOT}/Classes/lua_modules/game/lua_game.cpp
    ${RUNTIME_SRC_ROOT}/Classes/net_uv_cc/CCNetClient.cpp
    ${RUNTIME_SRC_ROOT}/Classes/foundation/GTools.cpp
    ${RUNTIME_SRC_ROOT}/Classes/test/TestScene.cpp
    ${RUNTIME_SRC_ROOT}/Classes/test/TestScene1.cpp
)


###################### mugen
file(GLOB_RECURSE MUGEN_HEADERS_FILES 
    ${RUNTIME_SRC_ROOT}/Classes/mugen/*.h)

file(GLOB_RECURSE MUGEN_SRC_FILES 
    ${RUNTIME_SRC_ROOT}/Classes/mugen/*.cpp)

file(GLOB_RECURSE MUGEN_C_FILES 
    ${RUNTIME_SRC_ROOT}/Classes/mugen/*.c)
    
list(APPEND GAME_HEADER
    ${MUGEN_HEADERS_FILES}
     )

list(APPEND GAME_SOURCE
    ${MUGEN_SRC_FILES}
     )

list(APPEND GAME_SOURCE
    ${MUGEN_C_FILES}
     )

###################### eventpp
file(GLOB_RECURSE EVENTPP_HEADERS_FILES 
    ${RUNTIME_SRC_ROOT}/Classes/eventpp/*.h)

list(APPEND GAME_SOURCE
    ${EVENTPP_HEADERS_FILES}
     )

###################### game
file(GLOB_RECURSE GAME_HEADERS_FILES 
    ${RUNTIME_SRC_ROOT}/Classes/game/*.h)

file(GLOB_RECURSE GAME_SRC_FILES 
    ${RUNTIME_SRC_ROOT}/Classes/game/*.cpp)


list(APPEND GAME_SOURCE
    ${GAME_HEADERS_FILES}
     )

list(APPEND GAME_SOURCE
    ${GAME_SRC_FILES}
     )

# sources need to compile info, include dirs and source files

if(ANDROID)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME cocos2dlua)
    list(APPEND GAME_SOURCE ${RUNTIME_SRC_ROOT}/proj.android/app/jni/hellolua/main.cpp)
elseif(LINUX)
    list(APPEND GAME_SOURCE ${RUNTIME_SRC_ROOT}/proj.linux/main.cpp)
elseif(WINDOWS)
    list(APPEND GAME_HEADER
         ${RUNTIME_SRC_ROOT}/proj.win32/main.h
         ${RUNTIME_SRC_ROOT}/proj.win32/resource.h
         )
    list(APPEND GAME_SOURCE
         ${RUNTIME_SRC_ROOT}/proj.win32/main.cpp
         ${RUNTIME_SRC_ROOT}/proj.win32/game.rc
         ${cc_common_res}
         )
elseif(APPLE)
    if(IOS)
        list(APPEND GAME_HEADER
             ${RUNTIME_SRC_ROOT}/proj.ios_mac/ios/AppController.h
             ${RUNTIME_SRC_ROOT}/proj.ios_mac/ios/RootViewController.h
             )
        set(APP_UI_RES
            ${RUNTIME_SRC_ROOT}/proj.ios_mac/ios/LaunchScreen.storyboard
            ${RUNTIME_SRC_ROOT}/proj.ios_mac/ios/LaunchScreenBackground.png
            ${RUNTIME_SRC_ROOT}/proj.ios_mac/ios/Images.xcassets
            )
        list(APPEND GAME_SOURCE
             ${RUNTIME_SRC_ROOT}/proj.ios_mac/ios/main.m
             ${RUNTIME_SRC_ROOT}/proj.ios_mac/ios/AppController.mm
             ${RUNTIME_SRC_ROOT}/proj.ios_mac/ios/RootViewController.mm
             ${RUNTIME_SRC_ROOT}/proj.ios_mac/ios/Prefix.pch
             ${APP_UI_RES}
             )
    elseif(MACOSX)
        list(APPEND GAME_HEADER
             ${RUNTIME_SRC_ROOT}/proj.ios_mac/mac/ConsoleWindowController.h
             )
        set(APP_UI_RES
            ${RUNTIME_SRC_ROOT}/proj.ios_mac/mac/Icon.icns
            ${RUNTIME_SRC_ROOT}/proj.ios_mac/mac/Info.plist
            ${RUNTIME_SRC_ROOT}/proj.ios_mac/mac/ConsoleWindow.xib
            )
        list(APPEND GAME_SOURCE
             ${RUNTIME_SRC_ROOT}/proj.ios_mac/mac/main.mm
             ${RUNTIME_SRC_ROOT}/proj.ios_mac/mac/Prefix.pch
             ${RUNTIME_SRC_ROOT}/proj.ios_mac/mac/ConsoleWindowController.m
             ${APP_UI_RES}
             )
    endif()
    list(APPEND GAME_SOURCE ${cc_common_res})
endif()

set(APP_SRC ${GAME_HEADER} ${GAME_SOURCE})

# mark app complie info and libs info
if(NOT ANDROID)
    add_executable(${APP_NAME} ${APP_SRC})
else()
    add_library(${APP_NAME} SHARED ${APP_SRC})
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/platform/android ${ENGINE_BINARY_PATH}/cocos/platform)
    target_link_libraries(${APP_NAME} -Wl,--whole-archive cpp_android_spec -Wl,--no-whole-archive)
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/proj.android ${ENGINE_BINARY_PATH}/cocos/lua-android)
    target_link_libraries(${APP_NAME} -Wl,--whole-archive lua_android_spec -Wl,--no-whole-archive)
endif()

target_link_libraries(${APP_NAME} luacocos2d)
target_include_directories(${APP_NAME} PRIVATE ${RUNTIME_SRC_ROOT}/Classes)

# mark app resources, resource will be copy auto after mark
setup_cocos_app_config(${APP_NAME})


include(modules.cmake)


if(APPLE)
    set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")
	set_xcode_property(${APP_NAME} INSTALL_PATH "\${LOCAL_APPS_DIR}") # fix archive no file
    if(MACOSX)
        set_target_properties(${APP_NAME} PROPERTIES
                              MACOSX_BUNDLE_INFO_PLIST "${RUNTIME_SRC_ROOT}/proj.ios_mac/mac/Info.plist"
                              )
        set_target_properties(${APP_NAME} PROPERTIES
            LINK_FLAGS "-pagezero_size 10000 -image_base 100000000"
        )
    elseif(IOS)
        set_xcode_property(${APP_NAME} INFOPLIST_FILE "${RUNTIME_SRC_ROOT}/proj.ios_mac/ios/Info.plist")
        set_xcode_property(${APP_NAME} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon")
        set_xcode_property(${APP_NAME} DEVELOPMENT_TEAM "")
        set_xcode_property(${APP_NAME} CODE_SIGN_IDENTITY "iPhone Developer")
    endif()
elseif(WINDOWS)
    cocos_copy_target_dll(${APP_NAME})
endif()
# copy resource on linux or WINDOWS
if(LINUX OR WINDOWS)
    cocos_get_resource_path(APP_RES_DIR ${APP_NAME})
    #cocos_sync_folder(${APP_NAME} ${res_res_folders} ${APP_RES_DIR}/res)
    cocos_sync_folder(${APP_NAME} ${res_res_folders}/binary ${APP_RES_DIR}/res/binary)
    cocos_sync_folder(${APP_NAME} ${res_res_folders}/ccs ${APP_RES_DIR}/res/ccs)
    cocos_sync_folder(${APP_NAME} ${res_src_folders} ${APP_RES_DIR}/src)
endif()
