/**
 * @copyright 2026 Zheyu Ji <https://github.com/FriedrichVan>
 * @brief This is derived policy of BorderPolicy. It returns the pixel at border if a further pixel was fetched.
 */
#include "border/ZeroBorder.h"
#include "border/ClampBorder.h"
#include "core/Image.h"
#include <algorithm>

namespace minicv {

double ClampBorder::fetch(const Image& img, int r, int c) const{
    if (img.getHeight() <= 0 || img.getWidth() <= 0){
        return 0;
    }

    int clampedR = std::max(0, std::min(r, img.getHeight() - 1));
    int clampedC = std::max(0, std::min(c, img.getWidth() - 1));
    return img.at(clampedR, clampedC);
}

std::string ClampBorder::getName() const{
    return "clamp";
}

}