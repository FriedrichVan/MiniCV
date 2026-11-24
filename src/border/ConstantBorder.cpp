/**
 * @copyright 2026 Zheyu Ji <https://github.com/FriedrichVan>
 * @brief This is derived policy of BorderPolicy. It returns a specific value when the fetched pixel was out of boundry. 
 */
#include "border/ConstantBorder.h"
#include "ConstantBorder.h"
#include "core/Image.h"
#include <algorithm>

namespace minicv {

ConstantBorder::ConstantBorder(double val) : fillValue_{val} {}

double ConstantBorder::fetch(const Image& img, int r, int c) const{
    if(r < 0 || r >= img.getHeight() || c < 0 || c >= img.getWidth()){
        return fillValue_;
    }
    return img.at(r, c);
}

std::string ConstantBorder::getName() const{
    return "constant";
}

double ConstantBorder::getFillValue() const noexcept{
    return fillValue_;
}

}