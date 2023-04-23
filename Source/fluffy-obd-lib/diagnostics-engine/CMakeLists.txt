cmake_minimum_required(VERSION 3.16.3)
project(diagnostics-engine)

add_subdirectory(decoders)
add_subdirectory(diagnostics-engine-base)
add_subdirectory(elm327)

add_library(diagnostics-engine api.hpp api.cpp)

target_link_libraries(${PROJECT_NAME}
decoders
diagnostics-engine-base
elm327-lib)