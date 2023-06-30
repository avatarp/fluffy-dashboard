cmake_minimum_required(VERSION 3.10)
project(diagnostics-engine-base VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

add_library(${PROJECT_NAME} SHARED
 command-repository.hpp
 data-decoding-handler.hpp
 data-filters.hpp
 dtc-handler.hpp
 dtc-handler.cpp
 obd-command-pid.hpp
 diagnostics-engine.cpp
 diagnostics-engine.hpp
 response.cpp
 response.hpp
)
