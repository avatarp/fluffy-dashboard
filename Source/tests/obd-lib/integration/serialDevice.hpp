#ifndef SERIALDEVICE_HPP_
#define SERIALDEVICE_HPP_

#include "bluetooth-obd-access.hpp"
#include "device.hpp"
#include "obd-serial-provider.hpp"
#include "serial-obd-access.hpp"

#include "elm327-data-decoder.hpp"
#include "elm327-engine.hpp"

#include "test-helpers.hpp"

bool testGetAvailablePids(Elm327Engine& engine, Response& availablePids)
{
    try {
        availablePids = engine.GetCommandResponse(ObdCommandPid::S01P00);
    } catch (const std::exception& exc) {
        std::cerr << exc.what() << '\n';
        return false;
    }

    if (availablePids.m_dataType == DataType::bitset) {
        return true;
    } else {
        std::cout << "Response dataType does not match expected dataType." << std::endl;
        return false;
    }
}

void runSerialDeviceTest(TestResults& results)
{
    Elm327Engine engine;

    auto serialDevices = Obd::ObdSerialProvider::GetAvailableDevices();
    bool connectionSuccessful { false };
    for (auto const& device : serialDevices) {
        engine.SetObdAccess(std::make_unique<Obd::UsbObdAccess>());
        engine.SetSerialDevice(device);
        if (engine.OpenConnection()) {
            std::cout << "Successful connection with " << device.GetDeviceFilePath() << std::endl;
            connectionSuccessful = true;
            break;
        }
    }

    if (!connectionSuccessful) {
        std::cout << "Opening connection failed" << std::endl;
        return;
    }

    Response availablePids;

    results.testCounter++;
    if (!testGetAvailablePids(engine, availablePids)) {
        results.failCounter++;
        return;
    }
    results.passCounter++;
    testAvailablePids(engine, availablePids, results);
}

#endif // SERIALDEVICE_HPP_