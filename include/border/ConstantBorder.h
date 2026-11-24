#pragma once
#include "border/BorderPolicy.h"

namespace minicv {

class ConstantBorder : public BorderPolicy{
public:
    explicit ConstantBorder(double val);
    ~ConstantBorder() override = default;
    
    [[nodiscard]] double fetch(const Image& img, int r, int c) const override;
    [[nodiscard]] std::string getName() const override;
    [[nodiscard]] double getFillValue() const noexcept;

private:
    double fillValue_;
};

}