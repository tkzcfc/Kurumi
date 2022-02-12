
macro(G_add_console name)
    project(${name})

    set(_Sources
        ${ARGN}
    )

    source_group("" FILES ${_Sources})
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${_Sources})

    add_executable(${name} ${_Sources})

    target_link_libraries(${name} PRIVATE LibBase LibProto)

    set(GameBinDir ${CMAKE_BINARY_DIR}/Bin)

    set_target_properties(${name} PROPERTIES
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
        TARGET ${name}
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ARGS ${GameBinDir}
    )

endmacro()

add_subdirectory(LibBase)
add_subdirectory(LibProto)
add_subdirectory(FightServer)
add_subdirectory(GateServer)
add_subdirectory(GameServer)
add_subdirectory(LoginServer)
add_subdirectory(CodeConv)
add_subdirectory(AddBOM)
add_subdirectory(Test)
add_subdirectory(ClientLog)


