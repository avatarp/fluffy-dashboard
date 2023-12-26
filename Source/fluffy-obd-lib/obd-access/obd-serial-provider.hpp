#pragma once
#include "../obd-access/device.hpp"
#include "system-calls.hpp"
#include <filesystem>
#include <regex>
#include <string>
#include <vector>

namespace Obd {

class ObdSerialProvider {
public:
    static std::vector<Device> GetAvailableDevices();
    static std::vector<std::string> get_available_ports();
};

}
