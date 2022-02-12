
# GLOB 遍历当前文件夹
# GLOB_RECURSE 递归遍历
file(GLOB_RECURSE GateServer_HPP 
	*.h)
	
file(GLOB_RECURSE GateServer_CPP 
	*.cpp)

G_add_console(GateServer
    ${GateServer_HPP}
	${GateServer_CPP}
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

