#ifndef SERIALDEVICE_HPP_
#define SERIALDEVICE_HPP_

#include "bluetooth-obd-access.hpp"
#include "device.hpp"
#include "obd-serial-provider.hpp"
#include "serial-obd-access.hpp"

#include "elm327-command-processor.hpp"

#include "test-helpers.hpp"

bool testGetAvailablePids(Elm327CommandProcessor& commandProcessor, Response& availablePids)
{
    try {
        availablePids = commandProcessor.GetCommandResponse(ObdCommandPid::S01P00);
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

void runSerialDeviceTest(TestResults& results)
{
    Elm327CommandProcessor commandProcessor;

    auto serialDevices = Obd::ObdSerialProvider::GetAvailableDevices();
    bool connectionSuccessful { false };
    for (auto const& device : serialDevices) {
        commandProcessor.SetObdAccess(std::make_unique<Obd::UsbObdAccess>());
        commandProcessor.GetObdAccess()->SetDevice(device);
        if (commandProcessor.OpenConnection()) {
            std::clog << "Successful connection with " << device.m_DeviceFilePath << std::endl;
            connectionSuccessful = true;
            break;
        }
    }

    if (!connectionSuccessful) {
        std::cerr << "Opening connection failed" << std::endl;
        return;
    }

    Response availablePids;

    results.testCounter++;
    if (!testGetAvailablePids(commandProcessor, availablePids)) {
        results.failCounter++;
        return;
    }
    results.passCounter++;
}

#endif // SERIALDEVICE_HPP_