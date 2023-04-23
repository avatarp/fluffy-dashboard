cmake_minimum_required(VERSION 3.10)
project(fluffy-obd-lib VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")


message("Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")

add_subdirectory(obd-access)
add_subdirectory(diagnostics-engine)
add_subdirectory(utils)

add_library(${PROJECT_NAME}
obd-access
diagnostics-engine
utils
)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)