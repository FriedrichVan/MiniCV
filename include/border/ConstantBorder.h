#pragma once
#include "border/BorderPolicy.h"

namespace minicv {

// @brief everything outside the image counts as one fixed value given by the user.
class ConstantBorder : public BorderPolicy{
public:
    // @brief explicit: no silent conversion from double to ConstantBorder.
    explicit ConstantBorder(double val);
    ~ConstantBorder() override = default;
    
    // @brief returns fillValue_ outside the image, the real pixel inside.
    [[nodiscard]] double fetch(const Image& img, int r, int c) const override;
    // @brief name used for logging.
    [[nodiscard]] std::string getName() const override;
    // @brief read-only access to the configured fill value.
    [[nodiscard]] double getFillValue() const noexcept;

private:
    double fillValue_;          // the constant returned for every outside pixel
};

}
