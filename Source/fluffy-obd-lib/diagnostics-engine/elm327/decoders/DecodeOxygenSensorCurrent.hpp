#ifndef DECODEOXYGENSENSORCURRENT_HPP_
#define DECODEOXYGENSENSORCURRENT_HPP_

#include "Decode.hpp"

// Decodes 34-3B Oxygen sensor current (CD)
//-> -128-127.996 mA
class DecodeOxygenSensorCurrent : public DecodeFloat {
public:
    float decode(const std::string& text) const override
    {
        if (text.length() != 5)
            throw std::runtime_error("invalid input");

        std::string byteC { text[0], text[1] };
        float valC = static_cast<float>(Utils::hexToDec(byteC));
        std::string byteD { text[3], text[4] };
        float valD = static_cast<float>(Utils::hexToDec(byteD));
        return (256.0f * valC + valD) / 256.0f - 128.0f;
    }
};

#endif // DECODEOXYGENSENSORCURRENT_HPP_