add_executable(
  elm327-ut
  main.cpp
  ../mocks/obd-access-mock.hpp
  command-repo-test.h
  decoders-test.h
  live-data-test.h
  parser-test.h)

set_target_properties(
  elm327-ut PROPERTIES CMAKE_CXX_STANDARD 20)

target_compile_features(elm327-ut PRIVATE cxx_std_20)

target_link_libraries(
  elm327-ut
  fluffy-obd-lib
  gtest
  gmock
  gtest_main
  gmock_main
  pthread)

add_test(elm327-ut elm327-ut)

if(${ENABLE_WARNINGS})
    test_target_set_warnings(
        TARGET
        elm327-ut
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()