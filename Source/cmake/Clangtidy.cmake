function(add_clang_tidy_to_target target)
    get_target_property(TARGET_SOURCES ${target} SOURCES)
    list(
        FILTER
        TARGET_SOURCES
        INCLUDE
        REGEX
        ".*.(cc|h|cpp|hpp)")

    find_package(Python3 COMPONENTS Interpreter)

    if(NOT ${Python_FOUND})
        message(WARNING "Python3 needed for Clang-Tidy")
        return()
    endif()

    find_program(CLANGTIDY clang-tidy)

    if(CLANGTIDY)
        message(STATUS "Added Clang Tidy for Target: ${target}")
        add_custom_target(
            ${target}_clangtidy
            COMMAND
            ${Python3_EXECUTABLE}
            ${CMAKE_SOURCE_DIR}/tools/run-clang-tidy.py
            ${TARGET_SOURCES}
            -config-file=${CMAKE_SOURCE_DIR}/.clang-tidy
            -extra-arg-before=-std=${CMAKE_CXX_STANDARD}
            -header-filter="\(src|app\)\/*.\(h|hpp\)"
            -p=${CMAKE_BINARY_DIR}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            USES_TERMINAL)
    else()
        message(WARNING "CLANGTIDY NOT FOUND")
    endif()
endfunction()