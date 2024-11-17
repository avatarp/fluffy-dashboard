#ifndef DECODEFUELPRESSURE_HPP_
#define DECODEFUELPRESSURE_HPP_

#include "Decode.hpp"

// Decodes
// 0A Fuel pressure -> 0-765 kPa
class DecodeFuelPressure : public DecodeFloat {
public:
    const size_t expectedInputSize { 2 };

    float decode(const std::string& text) const override
    {
        if (text.length() != expectedInputSize)
            throw std::runtime_error("invalid input");

        std::string byteA { text[0], text[1] };
        float valA = static_cast<float>(Utils::hexToDec(byteA));
        return 3 * valA;
    }
};

#endif // DECODEFUELPRESSURE_HPP_