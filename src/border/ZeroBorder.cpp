#include "border/ZeroBorder.h"

#include "core/Image.h"

namespace minicv {

// @brief outside pixel -> 0.0 (black), inside pixel -> the real value.
// @param img source image, read only.
// @param r row index, may be negative or >= height.
// @param c column index, may be negative or >= width.
// @return the pixel of img if (r, c) is inside, otherwise 0.0.
double ZeroBorder::fetch(const Image& img, int r, int c) const{
    // four conditions joined by ||: any single one means "outside".
    if(r < 0 || r >= img.getHeight() || c < 0 || c >= img.getWidth()){
        return 0.0;
    }
    // inside: forward the real pixel, at() also re-checks the range for us.
    return img.at(r, c);
}

// @brief the name that identifies this policy.
std::string ZeroBorder::getName() const{
    return "zero";
}

}
