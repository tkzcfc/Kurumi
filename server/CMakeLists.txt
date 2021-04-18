cmake_minimum_required(VERSION 3.8)
project(GameServer)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD            14)
set(CMAKE_CXX_STANDARD_REQUIRED   YES)

if (DEFINED MSVC_VERSION)
    if (MSVC_VERSION GREATER_EQUAL 1500)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++14")
    endif()
    if (MSVC_VERSION GREATER_EQUAL 1910)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /permissive-")
    endif()
endif()



function(assign_source_group)
    foreach(_source IN ITEMS ${ARGN})
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        else()
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path "${_source_rel}" PATH)
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach()
endfunction(assign_source_group)

function(G_add_library)
    foreach(_source IN ITEMS ${ARGN})
        assign_source_group(${_source})
    endforeach()
    add_library(${ARGV})
endfunction(G_add_library)



add_subdirectory(ThirdParty/easyloggingpp)
add_subdirectory(ThirdParty/libuv)
add_subdirectory(ThirdParty/net_uv)
add_subdirectory(ThirdParty/protobuf-lite)
add_subdirectory(ThirdParty/sqliter)


add_subdirectory(Apps)

