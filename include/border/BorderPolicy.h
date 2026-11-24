/**
 * @copyright 2026 Zheyu Ji <https://github.com/FriedrichVan>
 * @brief abstract base class for the border dir. 
 */
#pragma once

#include <string>

namespace minicv{

// forward declaration: this header only needs the name Image, not its full definition.
class Image;

// @brief abstract base class
// @note the three concrete policies (zero / constant / clamp) differ only in fetch.
class BorderPolicy {
public: 
    // @brief virtual destructor. needed whenever a derived object is deleted through BorderPolicy*.
    virtual ~BorderPolicy() = default;

    // @brief the fetch method tests the coordinate and return the pixel according to a specific policy. 
    // @param img is the given Image as a 2D-space of Doubles. 
    // @param r is the row-index (y-coordinate), may lie outside [0, height)
    // @param c is the column-index (x-coordinate), may lie outside [0, width)
    // @return the pixel as a Double
    // @note const: fetching never modifies the image.
    [[nodiscard]] virtual double fetch(const Image& img, int r, int c) const = 0;
    
    // @brief returns the name of the Policy. 
    [[nodiscard]] virtual std::string getName() const = 0;
};

}
