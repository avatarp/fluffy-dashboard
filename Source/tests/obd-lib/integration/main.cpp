#include "bluetoothDevice.hpp"
#include "serialDevice.hpp"

int main()
{
    TestResults results;

    runBluetoothDeviceTest(results);

    return verifyResults(results);
}