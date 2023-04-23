#pragma once
#include <filesystem>
#include <vector>
#include <string>
#include <regex>
#include "../utils/system-calls.hpp"
#include "../obd-access/device.hpp"

namespace Obd {

class UsbSerialProvider
{
public:
    static std::vector<Device> GetAvailableDevices();
};

}
