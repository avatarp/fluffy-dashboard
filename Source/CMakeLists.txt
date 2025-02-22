cmake_minimum_required(VERSION 3.16)
project(fluffy-obd-lib
    VERSION 0.1
    LANGUAGES CXX)

# Global CMake variables
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#Options
option(ENABLE_WARNINGS "Enable to add warnings to a target." ON)
option(ENABLE_WARNINGS_AS_ERRORS "Enable to treat warnings as errors." OFF)

option(ENABLE_COVERAGE "Enable a Code Coverage build." ON)

option(ENABLE_CLANG_TIDY "Enable to add clang tidy." ON)

option(ENABLE_SANITIZE_ADDR "Enable address sanitize." OFF)
option(ENABLE_SANITIZE_UNDEF "Enable undefined sanitize." OFF)
option(ENABLE_SANITIZE_LEAK "Enable leak sanitize." OFF)
option(ENABLE_SANITIZE_THREAD "Enable thread sanitize." OFF)

option(ENABLE_CLANG_FORMAT "Enable to add clang-format." ON)

# CMAKE MODULES
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include(Clangtidy)
include(Clangformat)

if(ENABLE_WARNINGS)
    include(Warnings)
endif()

if(ENABLE_COVERAGE)
    include(CodeCoverage)
    append_coverage_compiler_flags()
endif()

add_clang_format_target()

if(ENABLE_SANITIZE_ADDR
   OR ENABLE_SANITIZE_UNDEF
   OR ENABLE_SANITIZE_LEAK
   OR ENABLE_SANITIZE_THREAD)
    include(Sanitizer)
    add_sanitizer_flags()
endif()

add_subdirectory(fluffy-obd-lib)

find_package(GTest REQUIRED)
include(GoogleTest)
enable_testing()

add_subdirectory(tests/obd-lib/unit)
add_subdirectory(tests/obd-lib/integration)

if(ENABLE_COVERAGE)
    set(COVERAGE_MAIN "coverage")
    set(COVERAGE_EXCLUDES
    "${PROJECT_SOURCE_DIR}/obd-scanner/*"
    "${PROJECT_SOURCE_DIR}/tests/*"
    "${PROJECT_SOURCE_DIR}/tools/*"
        "/usr/include/*")
    set(COVERAGE_EXTRA_FLAGS)
    set(COVERAGE_DEPENDENCIES 
    fluffy-obd-lib
    bt-access-ut
    elm327-ut
    elm327-decoders-ut
    serial-access-ut)

    setup_target_for_coverage_gcovr_html(
        NAME
        ${COVERAGE_MAIN}
        EXECUTABLE
        ctest
        DEPENDENCIES
        ${COVERAGE_DEPENDENCIES}
        BASE_DIRECTORY
        ${CMAKE_SOURCE_DIR})
endif()