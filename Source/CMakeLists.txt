cmake_minimum_required(VERSION 3.16)
project(fluffy-obd-lib
    VERSION 0.1
    LANGUAGES CXX)

# Global CMake variables
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(fluffy-obd-lib)
add_subdirectory(tests/obd-lib/unit)
add_subdirectory(tests/obd-lib/integration)
