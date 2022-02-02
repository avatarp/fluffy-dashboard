#pragma once
#include <filesystem>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothLocalDevice>
#include "device.h"

namespace Obd {

const std::string DefaultRfcommFile = "/dev/rfcomm0";
class BluetoothProvider
{       
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QBluetoothLocalDevice localDevice;
public:
    BluetoothProvider();
    ~BluetoothProvider();
    BluetoothProvider(const BluetoothProvider& other) = delete;
    BluetoothProvider(BluetoothProvider&& other) = default;
    BluetoothProvider& operator=(const BluetoothProvider& other) = delete;
    BluetoothProvider& operator=(BluetoothProvider&& other) = default;

    bool StartScan();
    std::vector<QBluetoothDeviceInfo> GetAvailableDevices();
    bool IsBluetoothAvailable();
    bool BindToRfcomm(const QBluetoothDeviceInfo& device);
    Obd::Device CreateDevice(const QBluetoothDeviceInfo& device);
};

}
