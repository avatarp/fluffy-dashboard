#pragma once
#include <vector>
#include <../core/obd-access/device.h>
#include <../core/obd-access/bluetooth-obd-access.h>
#include <../core/obd-access/usb-obd-access.h>
#include <../core/parameters-engine/bluetooth-provider.h>
#include <../core/parameters-engine/usb-serial-provider.h>


class DiagnosticManager
{
public:
    DiagnosticManager();
    std::vector<Obd::Device> GetAvailableDevices();

};

