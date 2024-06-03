cmake_minimum_required(VERSION 3.16)
project(lib-integration-test
LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp serialDevice.hpp)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")

set_target_properties(${PROJECT_NAME} PROPERTIES
    CMAKE_CXX_STANDARD 20
    CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}"
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

add_subdirectory(../../../fluffy-obd-lib/ fluffy-obd-lib/)
target_link_libraries(${PROJECT_NAME} fluffy-obd-lib)
