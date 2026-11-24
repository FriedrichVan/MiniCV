#include "core/Image.h"
#include "utils/PixelMath.h"
#include <cmath>
#include <cstdint>
#include <fstream>
#include <stdexcept>

namespace {

void skipWhitespaceAndComment(std::ifstream& file) {
    file >> std::ws;
    while (file.peek() == '#') {
        std::string ignoredLine;
        std::getline(file, ignoredLine);
        file >> std::ws;
    }
}

}

namespace minicv {

Image::Image(int width, int height, double initVal) {
    if(width <= 0 || height <= 0){
        throw std::invalid_argument("width or height is illegal!");
    }
    width_ = width;
    height_ = height;
    const std::size_t total = static_cast<std::size_t>(width) * static_cast<std::size_t>(height);
    data_.assign(total, initVal);
}
Image::Image(int width, int height, const std::vector<double>& flatData){
    if(width <= 0 || height <= 0){
        throw std::invalid_argument("width or height is illegal!");
    }
    const std::size_t total = static_cast<std::size_t>(width) * static_cast<std::size_t>(height);
    if(flatData.size() != total){
        throw std::invalid_argument("the size of the given data doesn't correspond to the width and height!");
    }
    width_ = width;
    height_ = height;
    data_ = flatData;
}

int Image::getWidth() const noexcept {
    return width_;
}
int Image::getHeight() const noexcept {
    return height_;
}
std::size_t Image::getSize() const noexcept {
    return data_.size();
}
const std::vector<double>& Image::getData() const noexcept{
    return data_;
}

double& Image::at(int r, int c){
    if(r < 0 || r >= height_ || c < 0 || c >= width_) {
        throw std::out_of_range("The given coordinate is illegal!");
    }
    return data_[static_cast<std::size_t>(r) * static_cast<std::size_t>(width_) + static_cast<std::size_t>(c)];
}
const double& Image::at(int r, int c) const{
    if(r < 0 || r >= height_ || c < 0 || c >= width_) {
        throw std::out_of_range("The given coordinate is illegal!");
    }
    return data_[static_cast<std::size_t>(r) * static_cast<std::size_t>(width_) + static_cast<std::size_t>(c)];
}
double& Image::rawAt(int r, int c) noexcept {
    return data_[static_cast<std::size_t>(r) * static_cast<std::size_t>(width_) + static_cast<std::size_t>(c)];
}
const double& Image::rawAt(int r, int c) const noexcept {
    return data_[static_cast<std::size_t>(r) * static_cast<std::size_t>(width_) + static_cast<std::size_t>(c)];
}

Image Image::loadPGM(const std::string& filepath){
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filepath);
    }
    std::string tag;
    file >> tag;
    if(tag != "p2" || "p5"){
        throw std::runtime_error("no valid tag! It should be P2 or P5!");
    }
    skipWhitespaceAndComment(file);
    int width = 0;
    file >> width;
    skipWhitespaceAndComment(file);
    int height = 0;
    file >> height;
    skipWhitespaceAndComment(file);
    int maxVal = 0;
    file >> maxVal;
    if (width <= 0 || height <= 0 || maxVal <= 0 || maxVal > 255){
        throw std::runtime_error("illegal Picture!");
    }
    std::vector<double> data ={};
    if (tag == "P2") {
        for(int i=0; i<width * height; i++){
            int v = 0;
            file >> v;
            data.push_back(static_cast<double>(v));
        }
    } else if (tag == "P5") {
        file.get();
        int total = width * height;
        std::vector<std::uint8_t> buf(total);
        file.read(reinterpret_cast<char*>(buf.data()),total);
        for (std::uint8_t v : buf){
            data.push_back(static_cast<double>(v));
        }
    }
    return Image(width, height, data);
}

void Image::savePGM(const std::string& filepath) const{
    int width = Image::getWidth();
    int height = Image::getHeight();
    if(width || height <= 0){
        throw std::invalid_argument("width or height is illegal!");
    }
    std::ofstream file(filepath, std::ios::binary);
    file << "P5\n" << width << ' ' << height << "\n255\n";
    std::vector<std::uint8_t> buf(getSize());
    for(double v: getData()){
        clamp(v, 0.0, 255.0);
        std::lround(v);
        static_cast<std::uint8_t>(v);
        buf.push_back(v);
    }
    file.write(reinterpret_cast<const char*>(buf.data()), static_cast<std::streamsize> (buf.size()));
}


}