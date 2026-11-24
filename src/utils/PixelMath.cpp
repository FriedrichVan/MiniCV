#include "utils/PixelMath.h"
#include <cstddef>
#include <stdexcept>

namespace minicv{

// @brief dot product of two vectors of equal length.
// @param a first vector.
// @param b second vector.
// @return sum of a[i] * b[i].
// @throws std::invalid_argument if a.size() != b.size().
double dotProduct(const std::vector<double>& a, const std::vector<double>& b){
    // a dot product of two different lengths has no mathematical meaning.
    if (a.size() != b.size()) {
        throw std::invalid_argument("The given vectors have different sizes!");
    }

    // local variables are never auto-initialized in C++, always give them a value.
    double total = 0.0;
    // size_t, not int: size() is unsigned, mixing the two triggers -Wsign-compare.
    for(std::size_t i = 0; i < a.size(); ++i){
        total += a[i] * b[i];
    }
    return total;
}

// @brief sum of every element.
// @param values the vector to add up.
// @return the total, 0.0 for an empty vector (the loop simply never runs).
double sum(const std::vector<double>& values){
    double total = 0.0;
    for (std::size_t i = 0; i < values.size(); ++i){
        total += values[i];
    }
    return total;
}

// @brief force val into [minVal, maxVal].
// @param val the raw value.
// @param minVal lower bound, inclusive.
// @param maxVal upper bound, inclusive.
// @return the clamped value.
// @throws std::invalid_argument if minVal > maxVal.
double clamp(double val, double minVal, double maxVal){
    // inverted bounds are a caller bug, fail loudly instead of returning nonsense.
    if(minVal > maxVal){
        throw std::invalid_argument("the given min- and maxvalues are illegal!");
    }

    if(val < minVal){
        return minVal;
    }
    if(val > maxVal){
        return maxVal;
    }
    // already inside the range: return it untouched.
    return val;
}

}
