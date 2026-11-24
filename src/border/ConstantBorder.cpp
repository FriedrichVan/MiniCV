#include "border/ConstantBorder.h"
#include "core/Image.h"
#include <algorithm>

namespace minicv {

ConstantBorder(double val) : fillValue_{val};

double fetch(const Image& img, int r, int c) const{
    if(r <= 0 || r >= img.getHeight() || c < 0 || c >= img.getWidth()){
        return fillValue_;
    }
    return img.at(r, c);
}

std::string getName() const{
    return "constant";
}

double getFillValue() const{
    return fillValue_;
}

}