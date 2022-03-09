#pragma once
#include <iostream>
#include <thread>
#include "../core/utils/system-calls.h"
#include "../core/obd-access/usb-obd-access.h"
#include "../core/obd-access/bluetooth-obd-access.h"

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

void CleanupEnvironment()
{
    //Cleanup pipe files
    system("find . -type p -delete");
}

void SetupLoopbackEnvironment()
{
    CleanupEnvironment();
    system("mkfifo testenv");
    system("echo 123 > testenv &");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    if(SystemCallForResponse(("cat testenv"))=="123\n")
        std::clog<<"setup success"<<std::endl;
}
