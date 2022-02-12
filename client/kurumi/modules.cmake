#

set(EXTEND_LIBS "")
set(GAME_MOD_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/extend)
set(GAME_MOD_EXTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/external)

# apple

# ffmpeg, video

if(NOT LSTGX_NO_VIDEO)
	set(CC_VIDEO_DEPEND_LIBS)
	add_subdirectory(${GAME_MOD_EXTERNAL_DIR}/ffmpeg)
	if(APPLE)
		include_directories(${GAME_MOD_EXTERNAL_DIR}/ffmpeg/include)
		#target_link_libraries(${APP_NAME} ${FFMPEG_LIBRARY})
		target_link_options(${APP_NAME} PRIVATE -F ${FFMPEG_FRAMEWORK_PATH})
		target_link_options(${APP_NAME} PRIVATE -framework libffmpeg.4.dylib)
		# copy to Frameworks, need to check sign option in Xcode project
		target_sources(${APP_NAME} PUBLIC ${FFMPEG_LIBRARY})
		set_source_files_properties(${FFMPEG_LIBRARY} PROPERTIES MACOSX_PACKAGE_LOCATION Frameworks HEADER_FILE_ONLY 1)
		set_target_properties(${APP_NAME} PROPERTIES XCODE_ATTRIBUTE_FRAMEWORK_SEARCH_PATHS ${FFMPEG_FRAMEWORK_PATH})
		# set rpath
		target_link_options(${APP_NAME} PRIVATE -Wl,-rpath,@loader_path/../Frameworks/${FFMPEG_FRAMEWORK})
		# set_target_properties(${APP_NAME} PROPERTIES LINK_FLAGS "-Wl,-rpath,@loader_path/../Frameworks/${FFMPEG_FRAMEWORK}")
	else()
		list(APPEND CC_VIDEO_DEPEND_LIBS ext_ffmpeg)
	endif()
	add_subdirectory(${GAME_MOD_ROOT}/Video)
	list(APPEND EXTEND_LIBS cc_video)
else()
	target_compile_definitions(${APP_NAME} PUBLIC LSTGX_NO_VIDEO)
endif()

# BurstLinker

add_subdirectory(${GAME_MOD_EXTERNAL_DIR}/BurstLinker)
list(APPEND EXTEND_LIBS ext_BurstLinker)

target_link_libraries(${APP_NAME} ${EXTEND_LIBS})
