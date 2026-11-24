#include "utils/PixelMath.h"
#include <cstddef>
#include <stdexcept>

namespace minicv{

double dotProduct(const std::vector<double>& a, const std::vector<double>& b){
    if (a.size() != b.size()) {
        throw std::invalid_argument("The given vectors have different sizes!");
    }

    double total = 0.0;
    for(int i=0; i<a.size(); i++){
        total += a[i] * b[i];
    }
    return total;
}

double sum(const std::vector<double>& values){
    double total = 0.0;
    for (int i=0; i<values.size(); i++){
        total += values[i];
    }
    return total;
}

double clamp(double val, double minVal, double maxVal){
    if(minVal > maxVal){
        throw std::invalid_argument("the given min- and maxvalues are illegal!");
    }

    if(val < minVal){
        return minVal;
    }
    if(val > maxVal){
        return maxVal;
    }
    return val;
}

}