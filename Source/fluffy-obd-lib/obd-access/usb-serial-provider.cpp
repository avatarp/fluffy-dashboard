#include "usb-serial-provider.hpp"
namespace Obd {


std::vector<Obd::Device> Obd::UsbSerialProvider::GetAvailableDevices()
{
    std::vector<Obd::Device> DevicesFound;
    std::string response = SystemCallForResponse("ls /dev/serial/by-id");
    if(response.size()==0)
        return DevicesFound;

    std::vector<std::string> deviceFiles = std::vector<std::string>{};
    auto ss = std::stringstream{response};


    std::string getDeviceInfoCommand = "udevadm info /dev/serial/by-id/";

    for (std::string deviceFile; std::getline(ss, deviceFile, '\n');)
    {
        std::string deviceInfo = SystemCallForResponse((getDeviceInfoCommand+deviceFile).c_str());
        std::regex DeviceFilePathPattern("N: (.+)\n");
        std::smatch Match;
        if(std::regex_search(deviceInfo, Match, DeviceFilePathPattern))
        {
            std::string deviceFilePath = Match[1];

            std::regex DeviceVendorPattern("E: ID_VENDOR_FROM_DATABASE=(.+)\n");
            if(std::regex_search(deviceInfo, Match, DeviceVendorPattern))
            {
                std::string deviceVendor = Match[1];

                std::regex DeviceModelPattern("E: ID_MODEL_FROM_DATABASE=(.+)\n");
                if(std::regex_search(deviceInfo, Match, DeviceModelPattern))
                {
                    std::string deviceModel = Match[1];
                    std::string deviceName = deviceVendor + " " + deviceModel;
                    DevicesFound.push_back(Obd::Device(deviceFilePath,Obd::ConnectionType::Usb, deviceName));
                }
            }
        }
    }
    std::cout<<"Found "<<DevicesFound.size()<<" devices!"<<std::endl;
    return DevicesFound;
}
}
