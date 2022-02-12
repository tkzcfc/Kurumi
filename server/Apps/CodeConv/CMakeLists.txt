project(CodeConv)

set(_Sources
    main.cpp
)

source_group("" FILES ${_Sources})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${_Sources})

add_executable(CodeConv ${_Sources})

target_link_libraries(CodeConv PRIVATE LibBase LibProto uchardet)

set(GameBinDir ${CMAKE_BINARY_DIR}/Bin)

set_target_properties(CodeConv PROPERTIES
    FOLDER "Apps"
    RUNTIME_OUTPUT_DIRECTORY                "${GameBinDir}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG          "${GameBinDir}"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${GameBinDir}"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL     "${GameBinDir}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE        "${GameBinDir}"
    DEBUG_POSTFIX                           _d
    RELWITHDEBINGO_POSTFIX                  _rd
    MINSIZEREL_POSTFIX                      _r
    VS_DEBUGGER_WORKING_DIRECTORY           ${GameBinDir}
)

add_custom_command(
    TARGET CodeConv
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ARGS ${GameBinDir}
)