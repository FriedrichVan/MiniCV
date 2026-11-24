#pragma once
#include "border/BorderPolicy.h"

namespace minicv {

// @brief coordinates outside the image are pulled back to the nearest edge pixel.
class ClampBorder : public BorderPolicy{
public:
    // @brief stateless policy: default constructor and virtual destructor are enough.
    ClampBorder() = default;
    ~ClampBorder() override = default;
    
    // @brief clamps (r, c) into range first, then reads that pixel.
    [[nodiscard]] double fetch(const Image& img, int r, int c) const override;
    // @brief name used for logging.
    [[nodiscard]] std::string getName() const override;
};

}
