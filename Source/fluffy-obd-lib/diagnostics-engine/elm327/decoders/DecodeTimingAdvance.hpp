#ifndef DECODETIMINGADVANCE_HPP_
#define DECODETIMINGADVANCE_HPP_

#include "Decode.hpp"

// Decodes 0E Timing advance
//-> -64-63.5° (before Top Dead Centre)
class DecodeTimingAdvance : public DecodeFloat {
public:
    float decode(const std::string& text) const override
    {
        if (text.length() != 2)
            throw std::runtime_error("invalid input");

        std::string byteA { text[0], text[1] };
        return Utils::hexToDec(byteA) / 2.0 - 64;
    }
};

#endif // DECODETIMINGADVANCE_HPP_