project(LibBase)

file(GLOB_RECURSE LibBase_HPP 
	*.h)
	
file(GLOB_RECURSE LibBase_CPP 
	*.cpp)

# STATIC SHARED
add_library(${PROJECT_NAME} STATIC ${LibBase_HPP} ${LibBase_CPP})

target_link_libraries(
	${PROJECT_NAME}
	PUBLIC
	easyloggingpp
	net_uv
	libuv
	protobuf-lite
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
