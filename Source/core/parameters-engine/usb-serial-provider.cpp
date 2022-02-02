#include "usb-serial-provider.h"
namespace Obd {


std::vector<Obd::Device> Obd::UsbSerialProvider::GetAvailableDevices()
{
    std::vector<Obd::Device> DevicesFound;
    std::string response = SystemCallForResponse("ls -l /dev/serial/by-id");
    if(response.size()==0)
        return DevicesFound;

    std::regex DevicePattern(" [^ ]+ -> ../../ttyUSB[0-9]+");
    std::smatch Match;
    bool res = std::regex_search(response,Match,DevicePattern);
        std::clog<<"Matched! "<<Match[0];

    return DevicesFound;
}
}
