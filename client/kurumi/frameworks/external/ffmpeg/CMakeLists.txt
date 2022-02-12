cmake_minimum_required(VERSION 3.6)

set(lib_name ffmpeg)
set(target_name ext_${lib_name})
set(PREBUILT_ROOT "")

if(WINDOWS OR ANDROID OR LINUX)
  project(${lib_name})
  add_library(${target_name} SHARED IMPORTED GLOBAL)
  
  set_target_properties(${target_name} PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include
  )
endif()

if(WINDOWS)
  if(WIN64)
    set(PREBUILT_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/prebuilt_win64)
  else()
    set(PREBUILT_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/prebuilt_win32)
  endif()

  set_target_properties(${target_name} PROPERTIES
    IMPORTED_LOCATION "${PREBUILT_ROOT}/ffmpeg-4.dll"
    IMPORTED_IMPLIB "${PREBUILT_ROOT}/ffmpeg.lib"
  )
elseif(ANDROID)
  set(PREBUILT_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/prebuilt_android/${ANDROID_ABI})
  set_target_properties(${target_name} PROPERTIES
    IMPORTED_LOCATION "${PREBUILT_ROOT}/libffmpeg.so"
  )
elseif(MACOSX OR IOS)
  if(MACOSX)
    set(PREBUILT_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/prebuilt_mac)
  elseif(IOS)
    set(PREBUILT_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/prebuilt_ios)
  endif()

  set(FFMPEG_FRAMEWORK "libffmpeg.4.dylib.framework" CACHE INTERNAL "FFmpeg Framework name")
  set(FFMPEG_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include" CACHE INTERNAL "FFmpeg header location")
  set(FFMPEG_FRAMEWORK_PATH "${PREBUILT_ROOT}" CACHE INTERNAL "FFmpeg Framework location")
  set(FFMPEG_LIBRARY "${PREBUILT_ROOT}/${FFMPEG_FRAMEWORK}" CACHE INTERNAL "FFmpeg library")
elseif(LINUX)
  set(PREBUILT_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/prebuilt_linux)
  set_target_properties(${target_name} PROPERTIES
    IMPORTED_LOCATION "${PREBUILT_ROOT}/libffmpeg.so"
  )
endif()
