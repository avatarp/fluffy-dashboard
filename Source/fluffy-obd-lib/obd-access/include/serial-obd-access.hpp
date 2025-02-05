#ifndef SERIAL_OBD_ACCESS_HPP_
#define SERIAL_OBD_ACCESS_HPP_

#include "obd-access.hpp"

namespace Obd {

class UsbObdAccess : public ObdAccess {
private:
    bool ApplyDefaultConnectionSettings();

    /// @brief Read timeout in 0.1s
    static constexpr uint8_t timeout = 5;
    /// @brief Time Blocking read between characters in 0.1s
    static constexpr uint8_t readBlockingInterval = 3;

    virtual bool IsDeviceFileOk() override;
    virtual bool OpenConnection() override;

public:
    UsbObdAccess() = default;
    ~UsbObdAccess() = default;
    virtual void SetDevice(Device device) override final;
    virtual bool Connect() override;
    virtual bool Write(const std::string& command) override;
    virtual std::string Read() override;
};
}

#endif // SERIAL_OBD_ACCESS_HPP_
