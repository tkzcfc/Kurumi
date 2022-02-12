project(sqliter)


file(GLOB_RECURSE SQLITER_HPP 
	*.h)
	
file(GLOB_RECURSE SQLITER_C 
	*.c)
	
file(GLOB_RECURSE SQLITER_CPP
	*.cpp)


# STATIC SHARED
G_add_library(${PROJECT_NAME} STATIC
    ${SQLITER_HPP}
	${SQLITER_C}
	${SQLITER_CPP}
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


