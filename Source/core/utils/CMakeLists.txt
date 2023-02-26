cmake_minimum_required(VERSION 3.10)
project(obd-utils VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} SHARED
 system-calls.h
)
