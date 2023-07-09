#include "bluetooth-provider.hpp"
namespace Obd {

BluetoothProvider::BluetoothProvider()
{
    this->discoveryAgent = std::make_shared<QBluetoothDeviceDiscoveryAgent>();
}

bool BluetoothProvider::StartScan()
{
    if (localDevice.isValid()) {
        this->discoveryAgent->start();
        return true;
    }
    return false;
}

void BluetoothProvider::StopScan()
{
    this->discoveryAgent->stop();
}

std::vector<QBluetoothDeviceInfo> BluetoothProvider::GetAvailableDevicesInfo()
{
    // NOLINTNEXTLINE
    auto devices { discoveryAgent->discoveredDevices() };
    return std::vector<QBluetoothDeviceInfo> { devices.begin(), devices.end() };
}

bool BluetoothProvider::IsBluetoothAvailable()
{
    return localDevice.isValid();
}

bool BluetoothProvider::BindToRfcomm(const QBluetoothDeviceInfo& device) // NOLINT
{
    if (device.address().isNull()) {
        return false; // NOLINT
    }
    // Check for root privilages
    // Check rfcomm device file
    // if (devicefile exists)
    //{
    //   if(devicefile adress!=device.adress())
    //   Exec unbind
    //   else
    //   return true;
    // }
    // TODO
    // EXEC rfcomm bind in a new process with pkexec/gksu/etc
    // return result;
    return true;
}

Obd::Device BluetoothProvider::CreateDevice(const QBluetoothDeviceInfo& device)
{
    if (std::filesystem::exists(Obd::DefaultRfcommFile)) {
        BindToRfcomm(device);
    }
    return Obd::Device { Obd::DefaultRfcommFile,
        Obd::ConnectionType::Bluetooth,
        device.name().toStdString() };
}
} // namespace Obd
