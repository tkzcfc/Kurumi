project(LibBase)

file(GLOB_RECURSE LibBase_H
	*.h)
	
file(GLOB_RECURSE LibBase_HPP 
	*.hpp)
	
file(GLOB_RECURSE LibBase_CPP 
	*.cpp)
	
file(GLOB_RECURSE LibBase_CC
	*.cc)

# STATIC SHARED
add_library(${PROJECT_NAME} STATIC ${LibBase_H} ${LibBase_HPP} ${LibBase_CPP} ${LibBase_CC})

target_link_libraries(
	${PROJECT_NAME}
	PUBLIC
	easyloggingpp
	net_uv
	libuv
	sqliter
)
#protobuf-lite

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
