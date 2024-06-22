#ifndef DECODECOUNTA_HPP_
#define DECODECOUNTA_HPP_

#include "Decode.hpp"

// Decodes:
// 0D Speed -> 0-255km/h
// OB Intake manifold absolute pressure -> 0-255kPa
// 1C OBD standard -> 0-255 enum
// 30 Warm-ups since codes cleared -> 0-255 count
// 33 Absolute Barometric Pressure -> 0-255 kPa
class DecodeSimpleA : public DecodeFloat {
public:
    float decode(const std::string& text) const override
    {
        if (text.length() != 2)
            throw std::runtime_error("invalid input");

        std::string byteA { text[0], text[1] };
        return static_cast<float>(Utils::hexToDec(byteA));
    }
};

#endif // DECODECOUNTA_HPP_