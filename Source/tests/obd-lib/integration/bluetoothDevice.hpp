#ifndef BLUETOOTHDEVICE_HPP_
#define BLUETOOTHDEVICE_HPP_

#include "bluetooth-obd-access.hpp"
#include "bluetooth-provider.hpp"
#include "device.hpp"

#include "elm327-data-decoder.hpp"
#include "elm327-engine.hpp"

#include "test-helpers.hpp"

bool connectWithDevice(Elm327Engine& engine, const std::string& deviceMAC)
{
    Obd::BluetoothProvider btProvider;
    if (!btProvider.IsBluetoothAvailable()) {
        std::cerr << "Bluetooth not available" << std::endl;
        return false;
    }

    std::clog << "Scanning for devices..." << std::endl;
    btProvider.StartScan();
    sleep(1);
    btProvider.StopScan();

    auto bluetoothDevices = btProvider.GetAvailableDevicesInfo();

    for (auto const& device : bluetoothDevices) {
        std::clog << "Found device: " << device.name().toStdString() << '\n'
                  << "MAC: " << device.address().toString().toStdString() << "\n\n";

        if (deviceMAC == device.address().toString().toStdString()) {
            engine.SetObdAccess(std::make_unique<Obd::BluetoothObdAccess>());

            Obd::Device obdDevice = btProvider.CreateDevice(device);
            engine.GetObdAccess()->SetDevice(obdDevice);

            std::clog << "Connecting to device..." << std::endl;

            if (engine.OpenConnection()) {
                return true;
            }
        }
    }
    std::cerr << "No device with MAC " << deviceMAC << " found." << std::endl;
    return false;
}

bool testBTGetAvailablePids(Elm327Engine& engine, Response& availablePids)
{
    try {
        availablePids = engine.GetCommandResponse(ObdCommandPid::S01P00);
    } catch (const std::exception& exc) {
        std::cerr << exc.what() << '\n';
        return false;
    }

    if (availablePids.dataType == DataType::bitset) {
        return true;
    } else {
        std::cerr << "Response dataType does not match expected dataType." << std::endl;
        return false;
    }
}

void runBluetoothDeviceTestMain(TestResults& results)
{
    Elm327Engine engine;

    const std::string elm327MAC { "00:1D:A5:68:98:8B" };
    if (!connectWithDevice(engine, elm327MAC)) {
        std::cerr << "Opening connection failed" << std::endl;
        return;
    }
    std::clog << "Opening connection success!\n\n"
              << std::endl;

    std::clog << "Getting available PIDs..." << std::endl;
    Response availablePids;

    results.testCounter++;
    if (!testBTGetAvailablePids(engine, availablePids)) {
        results.failCounter++;
        return;
    }
    results.passCounter++;
    std::clog << "Received available PIDs:\n"
              << availablePids << std::endl;

    auto& availablePidsBitset = std::get<Bitset_32>(availablePids.decodedData);

    // Traversing bitset from the highest bit
    size_t bitsetSize = availablePidsBitset.size() - 1;
    for (size_t i { bitsetSize }; i != 0; i--) {
        if (availablePidsBitset[i]) {
            ObdCommandPid commandPid = static_cast<ObdCommandPid>(bitsetSize - i + 1u);
            try {
                auto pidResponse = engine.GetCommandResponse(commandPid);
                std::clog << "\nPID (hex): 0x10" << std::hex << bitsetSize - i + 1u << std::dec
                          << " Response\n"
                          << pidResponse << std::endl;
            } catch (const std::exception& e) {
                std::cerr << e.what() << '\n';
                continue;
            }
        }
    }
}

#endif // BLUETOOTHDEVICE_HPP_