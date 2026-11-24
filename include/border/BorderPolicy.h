/**
 * @copyright 2026 Zheyu Ji <https://github.com/FriedrichVan>
 * @brief abstract base class for the border dir. 
 */
#pragma once

#include <string>
#include "border/BorderPolicy.h"

namespace minicv{

class Image;

// @brief abstract base class
class BorderPolicy {
public: 
    virtual ~BorderPolicy() = default;
    // @brief the fetch method tests the coordinate and return the pixel according to a specific policy. 
    // @param img is the given Image as a 2D-space of Doubles. 
    // @param r is the x-coordinate
    // @param c is the y-coordinate
    // @return the pixel as a Double
    [[nodiscard]] virtual double fetch(const Image& img, int r, int c) const = 0;
    
    // @brief returns the name of the Policy. 
    [[nodiscard]] virtual std::string getName() const = 0;
};

}