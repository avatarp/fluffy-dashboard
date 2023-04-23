cmake_minimum_required(VERSION 3.10)
project(elm327-lib VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

add_library(${PROJECT_NAME} SHARED
 elm327-command-repository.cpp
 elm327-command-repository.hpp
 elm327-data-decoder.cpp
 elm327-data-decoder.hpp
 elm327-data-filter.cpp
 elm327-data-filter.hpp
 elm327-dtc-handler.hpp
 elm327-engine.cpp
 elm327-engine.hpp
)
