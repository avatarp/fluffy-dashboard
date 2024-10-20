#ifndef BLUETOOTHDEVICE_HPP_
#define BLUETOOTHDEVICE_HPP_

#include "bluetooth-obd-access.hpp"
#include "bluetooth-provider.hpp"
#include "device.hpp"

#include "elm327-data-decoder.hpp"
#include "elm327-engine.hpp"

#include "test-helpers.hpp"

const QString elm327MAC { "00:1D:A5:68:98:8B" };

bool testBTGetAvailablePids(Elm327Engine& engine, Response& availablePids)
{
    try {
        availablePids = engine.GetCommandResponse(ObdCommandPid::S01P00);
    } catch (const std::exception& exc) {
        std::cerr << exc.what() << '\n';
        return false;
    }

    if (availablePids.m_dataType == DataType::bitset) {
        std::cout << "Response:" << availablePids;
        return true;
    } else {
        std::cout << "Response dataType does not match expected dataType." << std::endl;
        return false;
    }
}

void runBluetoothDeviceTest(TestResults& results)
{
    Elm327Engine engine;
    Obd::BluetoothProvider btProvider;
    btProvider.StartScan();
    sleep(1);
    btProvider.StopScan();
    auto bluetoothDevices = btProvider.GetAvailableDevicesInfo();
    bool connectionSuccessful { false };
    for (auto const& device : bluetoothDevices) {
        if (device.address().toString() == elm327MAC) {
            engine.SetObdAccess(std::make_unique<Obd::BluetoothObdAccess>());

            Obd::Device obdDevice = btProvider.CreateDevice(device);
            engine.SetSerialDevice(obdDevice);

            if (engine.OpenConnection()) {
                std::cout << "Successful connection with " << obdDevice.GetDeviceFilePath() << std::endl;
                connectionSuccessful = true;
                break;
            }
        }
    }

    if (!connectionSuccessful) {
        std::cout << "Opening connection failed" << std::endl;
        return;
    }

    Response availablePids;

    results.testCounter++;
    if (!testBTGetAvailablePids(engine, availablePids)) {
        results.failCounter++;
        return;
    }
    results.passCounter++;
}

#endif // BLUETOOTHDEVICE_HPP_