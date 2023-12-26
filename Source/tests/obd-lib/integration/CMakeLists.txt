cmake_minimum_required(VERSION 3.14)
project(lib-integration-test)

set(CMAKE_CXX_STANDARD 20)

enable_testing()
# find_package(GTest REQUIRED)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" )

add_executable( ${PROJECT_NAME}
main.cpp
serialDevice.hpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
add_subdirectory(../../../fluffy-obd-lib/ fluffy-obd-lib/)

target_link_libraries(
  ${PROJECT_NAME}
  fluffy-obd-lib
  # gtest
  # gmock
  # gtest_main
  # gmock_main
  pthread
)

# include(GoogleTest)

# gtest_discover_tests(${PROJECT_NAME})

# enable_testing()

# add_test(${PROJECT_NAME} ${PROJECT_NAME})