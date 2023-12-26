#include "../../../fluffy-obd-lib/obd-access/bluetooth-obd-access.hpp"
#include "../../../fluffy-obd-lib/obd-access/device.hpp"
#include "../../../fluffy-obd-lib/obd-access/obd-serial-provider.hpp"
#include "../../../fluffy-obd-lib/obd-access/serial-obd-access.hpp"

#include "../../../fluffy-obd-lib/diagnostics-engine/elm327/elm327-data-decoder.hpp"
#include "../../../fluffy-obd-lib/diagnostics-engine/elm327/elm327-engine.hpp"

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

void testAvailablePids(Elm327Engine& engine, const Response& availablePids, int32_t& testCounter, int32_t& passCounter, int32_t& failCounter)
{
    const auto& bitset = availablePids.m_dataBitset;
    // TODO testResponse for all available pids
}

void runSerialDeviceTest(int32_t& testCounter, int32_t& passCounter, int32_t& failCounter)
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

    testCounter++;
    if (!testGetAvailablePids(engine, availablePids)) {
        failCounter++;
        return;
    }
    passCounter++;
    testAvailablePids(engine, availablePids, testCounter, passCounter, failCounter);
}