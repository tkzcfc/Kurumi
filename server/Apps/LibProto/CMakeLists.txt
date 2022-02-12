project(LibProto)

file(GLOB_RECURSE LibBase_HPP 
	*.h)
	
file(GLOB_RECURSE LibBase_CPP 
	*.cpp)
	
file(GLOB_RECURSE LibBase_CC
	*.cc)

# STATIC SHARED
add_library(${PROJECT_NAME} STATIC ${LibBase_HPP} ${LibBase_CPP} ${LibBase_CC})

target_link_libraries(
	${PROJECT_NAME}
	PUBLIC
	protobuf-lite
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
