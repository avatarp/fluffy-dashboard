#pragma once
#include "obd-access.h"

namespace Obd {

class BluetoothObdAccess : public ObdAccess
{
private:
    virtual bool Write(const std::string& command) override;
    virtual std::string Read() override;
    bool IsCommandSendOk(const std::string& command, int writeResult);
    void SetupDefaultTermios();
public:
    BluetoothObdAccess() = default;
    ~BluetoothObdAccess();
    virtual void SetDevice(Device device) override final;
    virtual bool Connect() override;
};
}
