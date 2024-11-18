#ifndef DECODEOXYGENSENSORVOLTAGE_HPP_
#define DECODEOXYGENSENSORVOLTAGE_HPP_

#include "Decode.hpp"

// Decodes 14-1B Oxygen sensor voltage (A)
//-> -0-1.275 V
class DecodeOxygenSensorVoltage1 : public DecodeFloat {
public:
    const size_t expectedInputSize { 2 };

    float decode(const std::string& text) const override
    {
        if (text.length() != expectedInputSize)
            throw std::runtime_error("invalid input");

        std::string byteA { text[0], text[1] };
        return static_cast<float>(Utils::hexToDec(byteA)) / 200.0f;
    }
};

// Decodes 24-2B Oxygen sensor voltage (CD)
//-> 0-7.999 V
class DecodeOxygenSensorVoltage2 : public DecodeFloat {
public:
    const size_t expectedInputSize { 4 };

    float decode(const std::string& text) const override
    {
        if (text.length() != expectedInputSize)
            throw std::runtime_error("invalid input");

        std::string byteC { text[0], text[1] };
        std::string byteD { text[2], text[3] };
        float valC = static_cast<float>(Utils::hexToDec(byteC));
        float valD = static_cast<float>(Utils::hexToDec(byteD));
        return 8.0f / 65536.0f * (256.0f * valC + valD);
    }
};

#endif // DECODEOXYGENSENSORVOLTAGE_HPP_