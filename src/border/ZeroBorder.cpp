/**
 * @copyright 2026 Zheyu Ji <https://github.com/FriedrichVan>
 * @brief This is derived policy of BorderPolicy. It returns a 0.0 when the fetched pixel was out of boundry. 
 */
#include "border/BorderPolicy.h"
#include "ZeroBorder.h"
#include "core/Image.h"

namespace minicv {

double ZeroBorder::fetch(const Image& img, int r, int c) const{
    if(r < 0 || r >= img.getHeight() || c < 0 || c >= img.getWidth()){
        return 0.0;
    }
    return img.at(r, c);
}

std::string ZeroBorder::getName() const{
    return "zero";
}

}