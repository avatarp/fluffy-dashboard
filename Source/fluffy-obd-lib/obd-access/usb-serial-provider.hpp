#pragma once
#include "../obd-access/device.hpp"
#include "system-calls.hpp"
#include <filesystem>
#include <regex>
#include <string>
#include <vector>

namespace Obd {

class UsbSerialProvider {
public:
    static std::vector<Device> GetAvailableDevices();
};

}
