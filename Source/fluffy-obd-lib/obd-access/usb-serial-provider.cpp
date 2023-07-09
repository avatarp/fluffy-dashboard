#include "usb-serial-provider.hpp"
namespace Obd {

std::vector<Obd::Device> Obd::UsbSerialProvider::GetAvailableDevices()
{
    std::vector<Obd::Device> devicesFound;
    std::string response = SystemCallForResponse("ls /dev/serial/by-id");
    if (response.empty()) {
        return devicesFound;
    }
    std::vector<std::string> deviceFiles = std::vector<std::string> {};
    auto sstream = std::stringstream { response };

    std::string getDeviceInfoCommand = "udevadm info /dev/serial/by-id/";

    for (std::string deviceFile; std::getline(sstream, deviceFile, '\n');) {
        std::string deviceInfo = SystemCallForResponse((getDeviceInfoCommand + deviceFile).c_str());
        std::regex deviceFilePathPattern("N: (.+)\n");
        std::smatch match;
        if (std::regex_search(deviceInfo, match, deviceFilePathPattern)) {
            std::string deviceFilePath = match[1];

            std::regex deviceVendorPattern("E: ID_VENDOR_FROM_DATABASE=(.+)\n");
            if (std::regex_search(deviceInfo, match, deviceVendorPattern)) {
                std::string deviceVendor = match[1];

                std::regex deviceModelPattern("E: ID_MODEL_FROM_DATABASE=(.+)\n");
                if (std::regex_search(deviceInfo, match, deviceModelPattern)) {
                    std::string deviceModel = match[1];
                    std::string deviceName = deviceVendor.append(" ").append(deviceModel);
                    devicesFound.emplace_back(Obd::Device(deviceFilePath, Obd::ConnectionType::Usb, deviceName));
                }
            }
        }
    }
    std::cout << "Found " << devicesFound.size() << " devices!" << std::endl;
    return devicesFound;
}
} // namespace Obd
