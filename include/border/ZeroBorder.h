#pragma once
#include "border/BorderPolicy.h"

namespace minicv {

class ZeroBorder : public BorderPolicy{
public:
    ZeroBorder() = default;
    ~ZeroBorder() override = default;
    
    [[nodiscard]] double fetch(const Image& img, int r, int c) const override;
    [[nodiscard]] std::string getName() const override;
};

}