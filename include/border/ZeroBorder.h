#pragma once
#include "border/BorderPolicy.h"

namespace minicv {

// @brief everything outside the image counts as 0.0 (black).
class ZeroBorder : public BorderPolicy{
public:
    // @brief stateless policy: default constructor and virtual destructor are enough.
    ZeroBorder() = default;
    ~ZeroBorder() override = default;
    
    // @brief returns 0.0 outside the image, the real pixel inside.
    [[nodiscard]] double fetch(const Image& img, int r, int c) const override;
    // @brief name used for logging.
    [[nodiscard]] std::string getName() const override;
};

}
