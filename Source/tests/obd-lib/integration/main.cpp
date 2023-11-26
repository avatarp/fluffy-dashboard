#include "../../../fluffy-obd-lib/obd-access/bluetooth-obd-access.hpp"
#include "../../../fluffy-obd-lib/obd-access/device.hpp"
#include "../../../fluffy-obd-lib/obd-access/usb-obd-access.hpp"

#include "../../../fluffy-obd-lib/diagnostics-engine/elm327/elm327-data-decoder.hpp"
#include "../../../fluffy-obd-lib/diagnostics-engine/elm327/elm327-engine.hpp"

#include <iostream>
#include <memory>

int main()
{
    int testResult { 0 };
    bool btTest { false };
    Obd::Device btDevice{"/dev/rfcomm0",Obd::ConnectionType::Bluetooth,"ELM327bt"};
    Obd::Device usbDevice{"/dev/SETMEUP",Obd::ConnectionType::Usb,"ELM327usb"};

    Elm327Engine engine;

    if (btTest) {
        engine.SetObdAccess(std::make_unique<Obd::BluetoothObdAccess>());
        engine.SetSerialDevice(btDevice);
    } else {
        engine.SetObdAccess(std::make_unique<Obd::UsbObdAccess>());
        engine.SetSerialDevice(usbDevice);
    }

    if (!engine.OpenConnection()) {
        std::cout << "Open connection failed" << std::endl;
        return 1;
    }

    auto availablePids = engine.GetCommandResponse(ObdCommandPid::S01P00);

    if (availablePids.m_dataType == DataType::bitset)
    {

    }
    else
    {
        std::cout << "Error while getting available parameters" << std::endl;
        return 1;
    }

        return testResult;
}