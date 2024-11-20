add_executable(
  elm327-decoders-ut
  main.cpp
  decoders-test.h)

set_target_properties(
  elm327-decoders-ut PROPERTIES CMAKE_CXX_STANDARD 20)

target_compile_features(elm327-decoders-ut PRIVATE cxx_std_20)

target_link_libraries(
  elm327-decoders-ut
  fluffy-obd-lib
  gtest
  gmock
  gtest_main
  gmock_main
  pthread)

add_test(elm327-decoders-ut elm327-decoders-ut)

if(${ENABLE_WARNINGS})
    test_target_set_warnings(
        TARGET
        elm327-decoders-ut
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()