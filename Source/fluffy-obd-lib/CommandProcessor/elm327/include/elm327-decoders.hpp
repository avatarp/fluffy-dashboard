#ifndef ELM327_DECODERS_HPP_
#define ELM327_DECODERS_HPP_

#include <bitset>
#include <sstream>

namespace elm327::utils {

inline long hexToDec(std::string& hex) { return strtol(hex.c_str(), nullptr, 16); }

inline uint32_t hexStringValue(std::string hex)
{
    std::stringstream converter(hex);
    uint32_t value;
    converter >> std::hex >> value;
    return value;
}

inline uint32_t hexStringValue(char hex)
{
    std::stringstream converter;
    converter << hex;

    uint32_t value;
    converter >> std::hex >> value;
    return value;
}

inline int32_t twoComplementaryHexToDec(std::string hexString)
{
    std::bitset<8> binary(hexStringValue(hexString));

    if (binary.test(7)) {
        binary.reset(7);
        int32_t temp = static_cast<int32_t>(binary.to_ulong());
        temp -= 128;
        return temp;
    }
    return static_cast<int32_t>(binary.to_ulong());
}

} // namespace Utils

namespace elm327::decoders {

// Decodes
// PIDs supported 00, 20, 40, 60, 80, A0, C0
// 12 Commanded secondary air status
// 13 Oxygen sensors present (in 2 banks)
// 1D Oxygen sensors present (in 4 banks)
// 1E Auxiliary input status
std::bitset<32> DecodeBitEncoded(const std::string& text)
{
    return std::bitset<32>(utils::hexStringValue(text));
}

std::string DecodeString(const std::string& text)
{
    std::string result;
    result.reserve(text.size() / 2);
    for (size_t i = 0; i < text.length(); i += 2) {
        std::string byte = text.substr(i, 2);
        result.push_back(static_cast<char>(strtol(byte.c_str(), nullptr, 16)));
    }

    return result;
}

// Decodes:
// 0D Speed -> 0-255km/h
// OB Intake manifold absolute pressure -> 0-255kPa
// 1C OBD standard -> 0-255 enum
// 30 Warm-ups since codes cleared -> 0-255 count
// 33 Absolute Barometric Pressure -> 0-255 kPa
float DecodeCountA(const std::string& text)
{
    std::string byteA { text[0], text[1] };
    return static_cast<float>(utils::hexToDec(byteA));
}

// Decodes:
// 22 Run time -> 0-65535 seconds
// 21 Distance with Malfunction Indicator Lamp on -> 0-65535 km
// 31 Distance since coded cleared -> 0-65535km
float DecodeCountAB(const std::string& text)
{
    std::string byteA { text[0], text[1] };
    float valA = static_cast<float>(utils::hexToDec(byteA));
    std::string byteB { text[2], text[3] };
    float valB = static_cast<float>(utils::hexToDec(byteB));
    return 256.0f * valA + valB;
}

std::string DecodeDTC(const std::string& text)
{
    const uint8_t byteAValue = static_cast<uint8_t>(utils::hexStringValue(text[0]));
    const uint8_t dtcLocation { static_cast<uint8_t>((byteAValue & 0b1100) >> 2) };
    std::string dtc;

    switch (dtcLocation) {
    // clang-format off
        case 0: dtc.push_back('P'); break;
        case 1: dtc.push_back('C'); break;
        case 2: dtc.push_back('B'); break;
        case 3: dtc.push_back('U'); break;
        default: break;
        }
    // clang-format on

    const uint8_t dtcFirstDigit = byteAValue & 0b0011;
    dtc += std::to_string(dtcFirstDigit);
    // insert rest of the dtc
    dtc += text.substr(1, 3);
    return dtc;
}

// Decodes 10 Mass Air Flow
//-> 0-655.35 gram/second
float DecodeAirFlow(const std::string& text)
{
    std::string byteA { text[0], text[1] };
    std::string byteB { text[2], text[3] };
    float valA = static_cast<float>(utils::hexToDec(byteA));
    float valB = static_cast<float>(utils::hexToDec(byteB));
    return (256 * valA + valB) / 100;
}

// Decodes:
// 24-2B,34-3B (AB) Air-Fuel Equivalence Ratio (lambda,λ)
//-> 0-2
float DecodeEquivalenceRatio(const std::string& text)
{
    std::string byteA { text[0], text[1] };
    std::string byteB { text[2], text[3] };
    float valA = static_cast<float>(utils::hexToDec(byteA));
    float valB = static_cast<float>(utils::hexToDec(byteB));
    return 2.0f / 65536.0f * (256.0f * valA + valB);
}

// Decodes
// 32 Evap. system Vapor pressure
//-> -8192-8191.75 Pa
float DecodeEvapPressure(const std::string& text)
{
    std::string byteA { text[0], text[1] };
    float valA = static_cast<float>(utils::twoComplementaryHexToDec(byteA));
    std::string byteB { text[2], text[3] };
    float valB = static_cast<float>(utils::hexToDec(byteB));
    return 0.25f * (256.0f * valA + valB);
}

// Decodes
// 0A Fuel pressure -> 0-765 kPa
float DecodeFuelPressure(const std::string& text)
{
    std::string byteA { text[0], text[1] };
    float valA = static_cast<float>(utils::hexToDec(byteA));
    return 3 * valA;
}

// Decodes:
// 22 Fuel Rail Pressure (relative to manifold vacuum)
//-> 0-5177.265 kPa
float DecodeFuelRailPressure(const std::string& text)
{
    std::string byteA { text[0], text[1] };
    float valA = static_cast<float>(utils::hexToDec(byteA));
    std::string byteB { text[2], text[3] };
    float valB = static_cast<float>(utils::hexToDec(byteB));
    return 0.079f * (256.0f * valA + valB);
}

// Decodes:
// 23 Fuel Rail Gauge pressure (diesel, or gasoline direct injection)
//-> 0-655350 kPa
float DecodeFuelRailGaugePressure(const std::string& text)
{
    std::string byteA { text[0], text[1] };
    float valA = static_cast<float>(utils::hexToDec(byteA));
    std::string byteB { text[2], text[3] };
    float valB = static_cast<float>(utils::hexToDec(byteB));
    return 10 * (256 * valA + valB);
}

// Decodes 34-3B Oxygen sensor current (CD)
//-> -128-127.996 mA
float DecodeOxygenSensorCurrent(const std::string& text)
{
    std::string byteC { text[0], text[1] };
    float valC = static_cast<float>(utils::hexToDec(byteC));
    std::string byteD { text[2], text[3] };
    float valD = static_cast<float>(utils::hexToDec(byteD));
    return (256.0f * valC + valD) / 256.0f - 128.0f;
}

// Decodes 14-1B Oxygen sensor voltage (A)
//-> -0-1.275 V
float DecodeOxygenSensorVoltage1(const std::string& text)
{
    std::string byteA { text[0], text[1] };
    return static_cast<float>(utils::hexToDec(byteA)) / 200.0f;
}

// Decodes 24-2B Oxygen sensor voltage (CD)
//-> 0-7.999 V
float DecodeOxygenSensorVoltage2(const std::string& text)
{
    std::string byteC { text[0], text[1] };
    std::string byteD { text[2], text[3] };
    float valC = static_cast<float>(utils::hexToDec(byteC));
    float valD = static_cast<float>(utils::hexToDec(byteD));
    return 8.0f / 65536.0f * (256.0f * valC + valD);
}

// Returns -> 0-100%
// Decodes:
// 04 Engine load
// 11 Throttle position
// 2C Commanded EGR
// 2E Commanded evaporative purge
// 2F Fuel tank level input

float DecodePercentage(const std::string& text)
{
    std::string byteA { text[0], text[1] };
    return static_cast<float>(utils::hexToDec(byteA)) / 2.55F;
}

// Returns -> -100-99.2%
// Decodes:
// 06-09 Short/long fuel trim (-100 too rich - 99.2 too lean)
// 14-1B Oxygen sensor short fuel trim (B)
// 2D EGR error
float DecodeSignedPercentage(const std::string& text)
{
    std::string byteA { text[0], text[1] };
    return static_cast<float>(utils::hexToDec(byteA)) / 1.28f - 100.f;
}

// Decodes
// 0C Engine RPM -> 0-16 383.75 RPM
float DecodeRPM(const std::string& text)
{
    std::string byteA { text[0], text[1] };
    std::string byteB { text[2], text[3] };
    float valA = static_cast<float>(utils::hexToDec(byteA));
    float valB = static_cast<float>(utils::hexToDec(byteB));
    return (256 * valA + valB) / 4;
}

// Returns -> -40-215°C
// Decodes:
// 05 Engine Coolant temperature
// 0F Air intake temperature
// 46 Ambient air temperature
// 5C Engine oil temperature
float DecodeTemperature(const std::string& text)
{
    std::string byteA { text[0], text[1] };
    return static_cast<float>(utils::hexToDec(byteA) - 40L);
}

// Decodes:
// 3C-3F Catalyst temperature
//-> -40-6513.5°C
float DecodeCatalystTemperature(const std::string& text)
{
    std::string byteA { text[0], text[1] };
    float valA = static_cast<float>(utils::hexToDec(byteA));
    std::string byteB { text[2], text[3] };
    float valB = static_cast<float>(utils::hexToDec(byteB));
    return (256.0f * valA + valB) / 10.0f - 40.0f;
}

// Decodes 0E Timing advance
//-> -64-63.5° (before Top Dead Centre)
float DecodeTimingAdvance(const std::string& text)
{
    std::string byteA { text[0], text[1] };
    return static_cast<float>(utils::hexToDec(byteA)) / 2.0f - 64.0f;
}

} // namespace decoders

#endif // ELM327_DECODERS_HPP_