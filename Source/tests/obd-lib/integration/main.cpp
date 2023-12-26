#include "serialDevice.hpp"

#include <iostream>
#include <memory>

int main()
{
    int32_t testCounter{0};
    int32_t passCounter{0};
    int32_t failCounter{0};

    runSerialDeviceTest(testCounter, passCounter, failCounter);

    return static_cast<int>(failCounter > 1);
}