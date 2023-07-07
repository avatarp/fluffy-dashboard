#pragma once
#include "obd-access.hpp"

namespace Obd
{

    class UsbObdAccess : public ObdAccess
    {
    private:
        virtual bool Write(const std::string &command) override;
        virtual std::string Read() override;
        void SetupDefaultTermios();

        /// @brief Read timeout in 0.1s
        static constexpr uint8_t timeout = 5;
        /// @brief Time Blocking read between characters in 0.1s
        static constexpr uint8_t readBlockingInterval = 3;

    public:
        UsbObdAccess() = default;
        ~UsbObdAccess() = default;
        virtual void SetDevice(Device device) override final;
        virtual bool Connect() override;
    };
}
