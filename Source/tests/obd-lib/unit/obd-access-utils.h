#pragma once

#include <iostream>
#include <thread>
#include "bluetooth-obd-access.hpp"
#include "serial-obd-access.hpp"

Obd::Device CreateUsbDevice()
{
    return Obd::Device("testenv",
        Obd::ConnectionType::Serial,
        "Mock usb device");
}

Obd::Device CreateBluetoothDevice()
{
    return Obd::Device("testenv",
        Obd::ConnectionType::Bluetooth,
        "Mock bluetooth device");
}