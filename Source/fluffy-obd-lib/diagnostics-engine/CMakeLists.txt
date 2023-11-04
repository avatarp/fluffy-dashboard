cmake_minimum_required(VERSION 3.16.3)
project(diagnostics-engine)

add_subdirectory(elm327)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" )

add_library(diagnostics-engine 
base/command-repository.hpp
base/data-decoding-handler.hpp
base/data-filters.hpp
base/dtc-handler.hpp
base/dtc-handler.cpp
base/obd-command-pid.hpp
base/diagnostics-engine.cpp
base/diagnostics-engine.hpp
base/response.cpp
base/response.hpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
target_link_libraries(${PROJECT_NAME}
elm327-lib)