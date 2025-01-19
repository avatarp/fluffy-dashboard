#include "obd-serial-provider.hpp"
#include <filesystem>
#include <iostream>
#include <regex>
#include <string>

namespace Obd {

std::vector<Obd::Device> Obd::ObdSerialProvider::GetAvailableDevices()
{
    namespace fs = std::filesystem;

    std::vector<Obd::Device> devices;

    const fs::path serialDevicesPath("/dev/serial/by-id");
    try {
        if (!exists(serialDevicesPath)) {
            spdlog::error("No serial devices found at {}", serialDevicesPath.generic_string());
            return devices;
        }
        for (const auto& devicePath : fs::directory_iterator(serialDevicesPath)) {
            if (is_symlink(devicePath.symlink_status())) {

                std::string canonicalPath = fs::canonical(
                    serialDevicesPath / read_symlink(devicePath))
                                                .generic_string();

                devices.emplace_back(Obd::Device(canonicalPath,
                    Obd::ConnectionType::Serial,
                    devicePath.path().filename()));
            }
        }

    } catch (const fs::filesystem_error& ex) {
        spdlog::error("Error while getting serial devices: {}", ex.what());
        return devices;
    }
    return devices;
}
} // namespace Obd
