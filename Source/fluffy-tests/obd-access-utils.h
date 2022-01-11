#pragma once
#include <iostream>
#include <thread>
#include "../core/obd-access/usb-obd-access.h"
#include "../core/obd-access/bluetooth-obd-access.h"

std::string ExecuteForResponse(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    std::clog<<"result was:" <<result<<std::endl;
    return result;
}

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
    system("find . -type p -delete");
}

void SetupLoopbackEnvironment()
{
    CleanupEnvironment();
    system("mkfifo testenv");
    system("echo 123 > testenv &");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    if(ExecuteForResponse(("cat testenv"))=="123\n")
        std::clog<<"setup success"<<std::endl;
}
