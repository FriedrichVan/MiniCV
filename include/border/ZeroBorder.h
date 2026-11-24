/**
 * @copyright 2026 Zheyu Ji <https://github.com/FriedrichVan>
 * @brief This is derived policy of BorderPolicy. It returns a 0.0 when the fetched pixel was out of boundry. 
 */
#pragma once
#include "border/BorderPolicy.h"

namespace minicv {

class ZeroBorder : public BorderPolicy{
public:
    ZeroBorder() = default;
    ~ZeroBorder() override = default;
    
    // @brief fetch the pixel according to zero-border-policy. returns 0.0 when out of boundry. 
    [[nodiscard]] double fetch(const Image& img, int r, int c) const override;
    [[nodiscard]] std::string getName() const override;
};

}