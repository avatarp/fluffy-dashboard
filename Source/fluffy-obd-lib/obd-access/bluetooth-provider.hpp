#pragma once
#include <filesystem>
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include <QtBluetooth/QBluetoothLocalDevice>
#include "../obd-access/device.hpp"

namespace Obd {

const std::string DefaultRfcommFile = "/dev/rfcomm0";
class BluetoothProvider
{       
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QBluetoothLocalDevice localDevice;
public:
    BluetoothProvider();
    ~BluetoothProvider() = default;
    BluetoothProvider(const BluetoothProvider& other) = delete;
    BluetoothProvider(BluetoothProvider&& other) = default;
    BluetoothProvider& operator=(const BluetoothProvider& other) = delete;
    BluetoothProvider& operator=(BluetoothProvider&& other) = default;

    bool StartScan();
    void StopScan();
    std::vector<QBluetoothDeviceInfo> GetAvailableDevicesInfo();
    bool IsBluetoothAvailable();
    bool BindToRfcomm(const QBluetoothDeviceInfo& device);
    Obd::Device CreateDevice(const QBluetoothDeviceInfo& device);
};

}
