#include "serialDevice.hpp"

int main()
{
    TestResults results;
    runSerialDeviceTest(results);

    return verifyResults(results);
}