#pragma once
#include <algorithm>
#include <vector>

namespace minicv{

// @brief dot product of two vectors: a[0]*b[0] + a[1]*b[1] + ...
// @param a first vector.
// @param b second vector, must have the same size as a.
// @return the scalar product of a and b.
// @throws std::invalid_argument if the two sizes differ.
[[nodiscard]] double dotProduct (const std::vector<double>& a, const std::vector<double>& b);

// @brief sum of every element.
// @param values the vector to add up.
// @return the total, 0.0 for an empty vector.
[[nodiscard]] double sum(const std::vector<double>& values);

// @brief force val into the closed range [minVal, maxVal].
// @param val the raw value, may be negative or too large.
// @param minVal lower bound, inclusive.
// @param maxVal upper bound, inclusive.
// @return minVal if val < minVal, maxVal if val > maxVal, otherwise val.
// @throws std::invalid_argument if minVal > maxVal.
[[nodiscard]] double clamp(double val, double minVal, double maxVal);

// @brief scale a vector so that its largest element becomes targetMax.
// @param input any numeric vector.
// @param targetMax the value the maximum element maps to (usually 255.0).
// @return a new vector<double> of the same size.
// @note empty input or max == 0 (all-black image) returns all zeros instead of dividing by zero.
template <typename T> [[nodiscard]] std::vector<double> normalize(const std::vector<T>& input, double targetMax) {
    // empty input: nothing to scale, and dereferencing max_element on it would be UB.
    if(input.empty()){
        return {};
    }
    // max_element returns an iterator, the '*' turns it into the value it points at.
    T maxVal = *std::max_element(input.begin(), input.end());
    // guard against division by zero: an all-zero vector stays all-zero.
    if(static_cast<double>(maxVal) == 0.0){
        return std::vector<double>(input.size(), 0.0);
    }
    std::vector<double> out;
    // reserve only reserves capacity, it does not create elements (that is why push_back is still needed).
    out.reserve(input.size());
    for(const T& x : input){
        // static_cast<double>: without it, int / int would be an integer division and lose the fraction.
        double newElement = (static_cast<double>(x) / static_cast<double>(maxVal)) * targetMax;
        out.push_back(newElement);
    }
    return out;
}

// @brief overload without targetMax: the maximum element maps to 1.0.
// @param input any numeric vector.
// @return the normalized vector, every element in [0, 1].
template <typename T> [[nodiscard]] std::vector<double> normalize(const std::vector<T>& input){
    return normalize(input, 1.0);
}

}
