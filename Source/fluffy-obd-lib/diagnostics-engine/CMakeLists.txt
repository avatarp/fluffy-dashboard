cmake_minimum_required(VERSION 3.16.3)
project(diagnostics-engine)

add_subdirectory(diagnostics-engine-base)
add_subdirectory(elm327)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" )

add_library(diagnostics-engine api.hpp api.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
target_link_libraries(${PROJECT_NAME}
diagnostics-engine-base
elm327-lib)