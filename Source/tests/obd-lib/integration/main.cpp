#include "serialDevice.hpp"

#include <iostream>

int main()
{
    TestResults results;
    runSerialDeviceTest(results);

    return verifyResults(results);
}