#include "border/BorderPolicy.h"
#include "core/Image.h"

namespace minicv {

double fetch(const Image& img, int r, int c) const{
    if(r < 0 || r >= img.getHeight() || c < 0 || c >= img.getWidth()){
        return 0.0;
    }
    return img.at(r, c);
}

std::string getName() const{
    return "zero";
}

}