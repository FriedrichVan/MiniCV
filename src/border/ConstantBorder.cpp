#include "border/ConstantBorder.h"

#include "core/Image.h"

namespace minicv {

// @brief store the fill value before the body runs.
// @param val the constant returned for every pixel outside the image.
ConstantBorder::ConstantBorder(double val) : fillValue_{val} {
}

// @brief outside pixel -> fillValue_, inside pixel -> the real value.
// @param img source image, read only.
// @param r row index, may be negative or >= height.
// @param c column index, may be negative or >= width.
// @return the pixel of img if (r, c) is inside, otherwise fillValue_.
double ConstantBorder::fetch(const Image& img, int r, int c) const{
    // four conditions joined by ||: any single one means "outside".
    if(r < 0 || r >= img.getHeight() || c < 0 || c >= img.getWidth()){
        return fillValue_;
    }
    // inside: forward the real pixel.
    return img.at(r, c);
}

// @brief the name that identifies this policy.
std::string ConstantBorder::getName() const{
    return "constant";
}

// @brief read-only access to the configured fill value.
double ConstantBorder::getFillValue() const noexcept{
    return fillValue_;
}

}
