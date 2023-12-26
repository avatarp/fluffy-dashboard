#include "obd-serial-provider.hpp"
namespace Obd {

std::vector<Obd::Device> Obd::ObdSerialProvider::GetAvailableDevices()
{
    namespace fs = std::filesystem;

    std::vector<Obd::Device> devices;

    const fs::path serialDevicesPath("/dev/serial/by-id");
    try {
        if (!exists(serialDevicesPath)) {
            std::cout << serialDevicesPath.generic_string() << " does not exist\n";
            return devices;
        } else {
            for (auto devicePath : fs::directory_iterator(serialDevicesPath)) {
                if (is_symlink(devicePath.symlink_status())) {

                    std::string canonical_path = fs::canonical(
                        serialDevicesPath / read_symlink(devicePath))
                                                     .generic_string();

                    devices.push_back(Obd::Device(canonical_path,
                        Obd::ConnectionType::Serial,
                        devicePath.path().filename()));
                }
            }
        }
    } catch (const fs::filesystem_error& ex) {
        std::cout << ex.what() << '\n';
        return devices;
    }
    return devices;
}
} // namespace Obd
