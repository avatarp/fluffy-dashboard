#include "bluetooth-provider.h"
namespace Obd {


BluetoothProvider::BluetoothProvider()
{
    this->discoveryAgent = new QBluetoothDeviceDiscoveryAgent();
}

BluetoothProvider::~BluetoothProvider()
{
    delete this->discoveryAgent;
}

bool BluetoothProvider::StartScan()
{
    if(localDevice.isValid())
    {
        this->discoveryAgent->start();
        return true;
    }
    else
        return false;
}

std::vector<QBluetoothDeviceInfo> BluetoothProvider::GetAvailableDevices()
{
    return std::vector<QBluetoothDeviceInfo>(
                discoveryAgent->discoveredDevices().toVector().toStdVector()
                );
}

bool BluetoothProvider::IsBluetoothAvailable()
{
    return localDevice.isValid();
}

bool BluetoothProvider::BindToRfcomm(const QBluetoothDeviceInfo &device)
{
    if(device.address().isNull())
        return false;

    //Check for root privilages
    //Check rfcomm device file
    //if (devicefile exists)
    //{
    //  if(devicefile adress!=device.adress())
    //  Exec unbind
    //  else
    //  return true;
    //}
    //TODO EXEC rfcomm bind with sudo promts like pkexec, gksu
    //
    //return result;
    return true;
}

Obd::Device BluetoothProvider::CreateDevice(const QBluetoothDeviceInfo &device)
{
    if(std::filesystem::exists(Obd::DefaultRfcommFile))
        BindToRfcomm(device);

    return Obd::Device(Obd::DefaultRfcommFile,
                       Obd::ConnectionType::Bluetooth,
                       device.name().toStdString());
}
}
