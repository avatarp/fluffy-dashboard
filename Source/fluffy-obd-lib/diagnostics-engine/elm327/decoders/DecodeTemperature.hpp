#ifndef DECODETEMPERATURE_HPP_
#define DECODETEMPERATURE_HPP_

#include "Decode.hpp"

// Returns -> -40-215°C
// Decodes:
// 05 Engine Coolant temperature
// 0F Air intake temperature
// 46 Ambient air temperature
// 5C Engine oil temperature
class DecodeTemperature : public DecodeFloat {
public:
    const size_t expectedInputSize { 2 };

    float decode(const std::string& text) const override
    {
        if (text.length() != expectedInputSize)
            throw std::runtime_error("invalid input");

        std::string byteA { text[0], text[1] };
        return static_cast<float>(Utils::hexToDec(byteA) - 40L);
    }
};

// Decodes:
// 3C-3F Catalyst temperature
//-> -40-6513.5°C
class DecodeCatalystTemperature : public DecodeFloat {
public:
    const size_t expectedInputSize { 4 };

    float decode(const std::string& text) const override
    {
        if (text.length() != expectedInputSize)
            throw std::runtime_error("invalid input");

        std::string byteA { text[0], text[1] };
        float valA = static_cast<float>(Utils::hexToDec(byteA));
        std::string byteB { text[2], text[3] };
        float valB = static_cast<float>(Utils::hexToDec(byteB));
        return (256.0f * valA + valB) / 10.0f - 40.0f;
    }
};

#endif // DECODETEMPERATURE_HPP_