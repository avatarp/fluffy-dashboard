#ifndef DECODETIMINGADVANCE_HPP_
#define DECODETIMINGADVANCE_HPP_

#include "Decode.hpp"

// Decodes 0E Timing advance
//-> -64-63.5° (before Top Dead Centre)
class DecodeTimingAdvance : public DecodeFloat {
public:
    const size_t expectedInputSize { 2 };

    float decode(const std::string& text) const override
    {
        if (text.length() != expectedInputSize)
            throw std::runtime_error("invalid input");

        std::string byteA { text[0], text[1] };
        return static_cast<float>(Utils::hexToDec(byteA)) / 2.0f - 64.0f;
    }
};

#endif // DECODETIMINGADVANCE_HPP_