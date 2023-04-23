cmake_minimum_required(VERSION 3.14)
project(lib-test)

set(CMAKE_CXX_STANDARD 20)

enable_testing()
find_package(GTest REQUIRED)

add_executable( lib-test
main.cpp
  bluetooth-obd-access.h
  obd-access-utils.h
  usb-obd-access.h
  elm327/decoders.h
  elm327/elm327-live-data.h
  elm327/parser.h
  )
  
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
add_subdirectory(../../fluffy-obd-lib/ fluffy-obd-lib/)

target_link_libraries(
  lib-test
  obd-access
  diagnostics-engine
  utils
  fluffy-obd-lib
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lib-test)
