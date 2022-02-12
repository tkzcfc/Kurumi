
# GLOB 遍历当前文件夹
# GLOB_RECURSE 递归遍历
file(GLOB_RECURSE GameServer_HPP 
	*.h)
	
file(GLOB_RECURSE GameServer_CPP 
	*.cpp)

G_add_console(GameServer
    ${GameServer_HPP}
	${GameServer_CPP}
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

