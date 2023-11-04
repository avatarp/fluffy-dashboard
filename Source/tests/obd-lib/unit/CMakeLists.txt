cmake_minimum_required(VERSION 3.14)
project(lib-test)

set(CMAKE_CXX_STANDARD 20)

enable_testing()
find_package(GTest REQUIRED)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" )

add_executable( lib-test
main.cpp
  bluetooth-obd-access.h
  obd-access-utils.h
  usb-obd-access.h
  mocks/mock-obd-access.hpp
  elm327/command-repo.h
  elm327/decoders.h
  elm327/live-data.h
  elm327/parser.h
  )

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
add_subdirectory(../../../fluffy-obd-lib/ fluffy-obd-lib/)

target_link_libraries(
  lib-test
  fluffy-obd-lib
  gtest
  gmock
  gtest_main
  gmock_main
  pthread
)

include(GoogleTest)

gtest_discover_tests(lib-test)

enable_testing()

add_test(lib-unit lib-test)