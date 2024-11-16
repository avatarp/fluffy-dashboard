#ifndef OBD_ACCESS_UTILS_H_
#define OBD_ACCESS_UTILS_H_

#include "bluetooth-obd-access.hpp"
#include "serial-obd-access.hpp"
#include <iostream>
#include <thread>

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

#endif // OBD_ACCESS_UTILS_H_