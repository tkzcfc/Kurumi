
# GLOB 遍历当前文件夹
# GLOB_RECURSE 递归遍历
file(GLOB_RECURSE FightServer_HPP 
	*.h)
	
file(GLOB_RECURSE FightServer_CPP 
	*.cpp)

G_add_console(FightServer
    ${FightServer_HPP}
	${FightServer_CPP}
)

#target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/anax/include)

