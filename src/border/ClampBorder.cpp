#include "border/ClampBorder.h"

#include <algorithm>

#include "core/Image.h"

namespace minicv {

// @brief pull (r, c) back to the nearest edge, then read that pixel.
// @param img source image, read only.
// @param r row index, may be negative or >= height.
// @param c column index, may be negative or >= width.
// @return the pixel at the clamped coordinate.
double ClampBorder::fetch(const Image& img, int r, int c) const{
    // empty image guard: height - 1 would be -1 and max/min would get inverted bounds.
    if (img.getHeight() <= 0 || img.getWidth() <= 0){
        return 0;
    }

    // std::max(0, std::min(r, h-1)) == force r into [0, h-1], same as std::clamp(r, 0, h-1).
    int clampedR = std::max(0, std::min(r, img.getHeight() - 1));
    int clampedC = std::max(0, std::min(c, img.getWidth() - 1));
    // the clamped coordinate is always inside, so this can never throw.
    return img.at(clampedR, clampedC);
}

// @brief the name that identifies this policy.
std::string ClampBorder::getName() const{
    return "clamp";
}

}
