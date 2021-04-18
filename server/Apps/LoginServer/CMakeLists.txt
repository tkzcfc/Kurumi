
# GLOB 遍历当前文件夹
# GLOB_RECURSE 递归遍历
file(GLOB_RECURSE LoginServer_HPP 
	*.h)
	
file(GLOB_RECURSE LoginServer_CPP 
	*.cpp)

G_add_console(LoginServer
    ${LoginServer_HPP}
	${LoginServer_CPP}
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

