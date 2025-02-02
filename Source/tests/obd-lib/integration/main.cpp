#include "bluetoothDevice.hpp"
#include "serialDevice.hpp"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include <chrono>
#include <iomanip>

std::string getTimeStamp()
{
    auto time = std::time(nullptr);
    auto timeLocal = *std::localtime(&time);
    std::ostringstream oss;
    oss << std::put_time(&timeLocal, "%Y-%m-%d %H-%M-%S");
    return oss.str();
}

void setupLogging()
{
    std::vector<spdlog::sink_ptr> sinks {
        std::make_shared<spdlog::sinks::stdout_color_sink_mt>(),
        std::make_shared<spdlog::sinks::basic_file_sink_st>(getTimeStamp() + ".log", true)
    };

    constexpr auto logPattern = "[%H:%M:%S.%f] [%n] [%^%l%$] %v";
    for (auto sink : sinks) {
        sink->set_pattern(logPattern);
    }

    auto combined_logger = std::make_shared<spdlog::logger>(
        "integration_test", begin(sinks), end(sinks));

    spdlog::register_logger(combined_logger);
    spdlog::set_default_logger(combined_logger);
}

int main()
{
    setupLogging();

    TestResults results;

    spdlog::info("Starting Bluetooth device test\n");
    runBluetoothDeviceTestMain(results);
    spdlog::info("Starting Bluetooth finished\n");

    return verifyResults(results);
}