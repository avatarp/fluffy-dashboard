#pragma once
#include <filesystem>
#include <vector>
#include <string>
#include <regex>
#include "../utils/system-calls.h"
#include "device.h"

namespace Obd {

const std::string UsbSerialPrefix = "ttyUSB";
const std::string DeviceDir = "/dev/";
class UsbSerialProvider
{
    public:
    static std::vector<Device> GetAvailableDevices();
};

}
