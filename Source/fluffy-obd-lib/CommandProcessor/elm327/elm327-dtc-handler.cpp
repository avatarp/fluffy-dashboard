#include "elm327-dtc-handler.hpp"

#include "elm327-decoders.hpp"

#include "spdlog/spdlog.h"

#include <string>

std::vector<std::string> Elm327DtcHandler::ParseDtcResponse(Response& dtcResponse)
{
    spdlog::info("Parsing DTC response: {}", dtcResponse.raw.data);

    constexpr size_t dtcLength { 4 };
    constexpr size_t dtcCountLength { 2 };
    const size_t dtcCount = static_cast<size_t>(std::stoi(dtcResponse.raw.data.substr(0, 2), nullptr, 16));
    const size_t expectedLength = dtcCount * dtcLength + dtcCountLength;

    if (expectedLength != dtcResponse.raw.data.length()) {
        throw(std::runtime_error { "DTC count does not match data length: "
            + std::to_string(expectedLength) + " != " + std::to_string(dtcResponse.raw.data.length()) });
    }

    std::vector<std::string> dtcCodes;

    for (size_t i = 0; i < dtcCount; ++i) {
        const size_t startIndex = dtcCountLength + i * dtcLength;
        const std::string dtcCode = dtcResponse.raw.data.substr(startIndex, dtcLength);
        dtcCodes.push_back(elm327::decoders::DecodeDTC(dtcCode));
    }

    if (dtcCodes.empty()) {
        spdlog::info("No DTC codes found in response: {}", dtcResponse.raw.data);
    }

    return dtcCodes;
}

void Elm327DtcHandler::ParseStoredDtc(Response& dtcResponse)
{
    if (dtcResponse.raw.commandId != "03") {
        throw(std::runtime_error { "Invalid command ID for stored DTCs: " + dtcResponse.raw.commandId });
    }
    m_retrievedDtc.storedDtcCodes = this->ParseDtcResponse(dtcResponse);
}

void Elm327DtcHandler::ParsePendingDtc(Response& dtcResponse)
{
    if (dtcResponse.raw.commandId != "07") {
        throw(std::runtime_error { "Invalid command ID for pending DTCs: " + dtcResponse.raw.commandId });
    }
    m_retrievedDtc.pendingDtcCodes = this->ParseDtcResponse(dtcResponse);
}

void Elm327DtcHandler::ParsePermanentDtc(Response& dtcResponse)
{
    if (dtcResponse.raw.commandId != "0A") {
        throw(std::runtime_error { "Invalid command ID for permanent DTCs: " + dtcResponse.raw.commandId });
    }
    m_retrievedDtc.permanentDtcCodes = this->ParseDtcResponse(dtcResponse);
}