#pragma once
#include <iostream>
#include <thread>
#include "../../../fluffy-obd-lib/utils/system-calls.hpp"
#include "../../../fluffy-obd-lib/obd-access/usb-obd-access.hpp"
#include "../../../fluffy-obd-lib/obd-access/bluetooth-obd-access.hpp"

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

class PipesEnv
{
    const std::string pipename{"testenv"};
public:
    PipesEnv(){
        system((std::string("mkfifo ") + pipename).c_str());
    }
    ~PipesEnv(){
        system("find . -type p -delete");
    }

    std::string drainData(){
        return SystemCallForResponse(
                    (std::string("timeout --foreground 1 cat ")
                     + pipename).c_str());
    }
    void feedData(std::string data){
        system((std::string("echo ")
                    + data
                    + std::string(" > ")
                    + pipename
                    + std::string(" &")).c_str());
        }

};
