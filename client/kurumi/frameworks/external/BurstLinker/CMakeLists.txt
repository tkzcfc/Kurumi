cmake_minimum_required(VERSION 3.6)

set(lib_name BurstLinker)
set(target_name ext_${lib_name})

project(${lib_name})

set(src_dir ${CMAKE_CURRENT_SOURCE_DIR}/src/src)

set(${target_name}_src
  ${src_dir}/ThreadPool.h
  ${src_dir}/GifEncoder.h ${src_dir}/GifEncoder.cpp
  ${src_dir}/GifAnalyzer.cpp ${src_dir}/GifAnalyzer.h
  ${src_dir}/GifBlockWriter.cpp ${src_dir}/GifBlockWriter.h
  ${src_dir}/KDTree.cpp ${src_dir}/KDTree.h
  ${src_dir}/LzwEncoder.cpp ${src_dir}/LzwEncoder.h
  ${src_dir}/Logger.cpp ${src_dir}/Logger.h

  ${src_dir}/Ditherer.h
  ${src_dir}/NoDitherer.cpp ${src_dir}/NoDitherer.h
  ${src_dir}/BayerDitherer.cpp ${src_dir}/BayerDitherer.h
  ${src_dir}/M2Ditherer.cpp ${src_dir}/M2Ditherer.h
  ${src_dir}/FloydSteinbergDitherer.cpp ${src_dir}/FloydSteinbergDitherer.h

  ${src_dir}/ColorQuantizer.h
  ${src_dir}/UniformQuantizer.cpp ${src_dir}/UniformQuantizer.h
  ${src_dir}/RandomQuantizer.cpp ${src_dir}/RandomQuantizer.h
  ${src_dir}/MedianCutQuantizer.cpp ${src_dir}/MedianCutQuantizer.h
  ${src_dir}/KMeansQuantizer.cpp ${src_dir}/KMeansQuantizer.h
  ${src_dir}/OctreeQuantizer.cpp ${src_dir}/OctreeQuantizer.h
  ${src_dir}/NeuQuant.cpp ${src_dir}/NeuQuant.h
  ${src_dir}/NeuQuantQuantizer.cpp ${src_dir}/NeuQuantQuantizer.h
  ${src_dir}/BurstLinker.cpp ${src_dir}/BurstLinker.h
)

add_library(${target_name} STATIC
  ${${target_name}_src}
)
use_cocos2dx_compile_options(${target_name})

target_include_directories(${target_name} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src/include)

set_target_properties(${target_name}
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  FOLDER "External"
)

if(XCODE OR VS)
  cocos_mark_code_files(${target_name})
endif()
