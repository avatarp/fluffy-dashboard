add_executable(fluffy-obd-it main.cpp bluetoothDevice.hpp serialDevice.hpp)

set_target_properties(
    fluffy-obd-it PROPERTIES CMAKE_CXX_STANDARD 20)

target_compile_features(fluffy-obd-it PRIVATE cxx_std_20)

find_package(Qt5 COMPONENTS Bluetooth REQUIRED)

qt5_use_modules(${PROJECT_NAME} Bluetooth)

target_link_libraries(fluffy-obd-it fluffy-obd-lib Qt5::Bluetooth)

if(${ENABLE_WARNINGS})
    test_target_set_warnings(
        TARGET
        fluffy-obd-it
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()