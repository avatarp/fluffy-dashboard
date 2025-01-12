#include "bluetoothDevice.hpp"
#include "serialDevice.hpp"

int main()
{
    TestResults results;

    runBluetoothDeviceTestMain(results);

    return verifyResults(results);
}