#pragma once
#include "../../../fluffy-obd-lib/obd-access/bluetooth-obd-access.hpp"
#include "../../../fluffy-obd-lib/obd-access/usb-obd-access.hpp"
#include "../../../fluffy-obd-lib/utils/system-calls.hpp"
#include <iostream>
#include <thread>

Obd::Device CreateUsbDevice()
{
    return Obd::Device("testenv",
        Obd::ConnectionType::Usb,
        "Mock usb device");
}

Obd::Device CreateBluetoothDevice()
{
    return Obd::Device("testenv",
        Obd::ConnectionType::Bluetooth,
        "Mock bluetooth device");
}