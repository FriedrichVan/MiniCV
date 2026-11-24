#pragma once
#include <algorithm>
#include <vector>

namespace minicv{

[[nodiscard]] double dotProduct (const std::vector<double>& a, const std::vector<double>& b);
[[nodiscard]] double sum(const std::vector<double>& values);
[[nodiscard]] double clamp(double val, double minVal, double maxVal);

template <typename T> [[nodiscard]] std::vector<double> normalize(const std::vector<T>& input, double targetMax) {
    if(input.empty()){
        return {};
    }
    T maxVal = *std::max_element(input.begin(), input.end());
    if(static_cast<double>(maxVal) == 0.0){
        return std::vector<double>(input.size(), 0.0);
    }
    std::vector<double> out;
    out.reserve(input.size());
    for(const T& x : input){
        double newElement = (static_cast<double>(x) / static_cast<double>(maxVal)) * targetMax;
        out.push_back(newElement);
    }
    return out;
}

template <typename T> [[nodiscard]] std::vector<double> normalize(const std::vector<T>& input){
    return normalize(input, 1, 0);
}

}