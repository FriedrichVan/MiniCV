/**
 * @copyright 2026 Zheyu Ji <https://github.com/FriedrichVan>
 * @brief This is derived policy of BorderPolicy. It returns the pixel at border if a further pixel was fetched.
 */
#pragma once
#include "border/BorderPolicy.h"

namespace minicv {

class ClampBorder : public BorderPolicy{
public:
    ClampBorder() = default;
    ~ClampBorder() override = default;
    
    [[nodiscard]] double fetch(const Image& img, int r, int c) const override;
    [[nodiscard]] std::string getName() const override;
};

}