add_executable(fluffy-obd-it main.cpp serialDevice.hpp)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")

set_target_properties(
    fluffy-obd-it PROPERTIES CMAKE_CXX_STANDARD 20 CMAKE_CXX_CLANG_TIDY
    "${CLANG_TIDY_EXE}")

target_compile_features(fluffy-obd-it PRIVATE cxx_std_20)

target_link_libraries(fluffy-obd-it fluffy-obd-lib)
