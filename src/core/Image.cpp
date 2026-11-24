#include "core/Image.h"
#include "utils/PixelMath.h"
#include <cmath>
#include <cstdint>
#include <fstream>
#include <stdexcept>

namespace {

// @brief skip whitespace and every '#' comment line, so the next ">>" lands on a real token.
// @param file the input stream, its read cursor is advanced past the skipped characters.
// @note anonymous namespace: this helper is private to Image.cpp (internal linkage).
void skipWhitespaceAndComment(std::ifstream& file) {
    // eat all spaces / tabs / newlines before the next token.
    file >> std::ws;
    // peek() looks at the next char without consuming it.
    while (file.peek() == '#') {
        // a comment runs from '#' to the end of that line: read and throw the whole line away.
        std::string ignoredLine;
        std::getline(file, ignoredLine);
        // a newline or another comment may follow, so clean up again before looping.
        file >> std::ws;
    }
}

}

namespace minicv {

// @brief allocate width * height pixels, all set to initVal.
// @param width number of columns, must be positive.
// @param height number of rows, must be positive.
// @param initVal value written into every pixel.
Image::Image(int width, int height, double initVal) {
    // check BEFORE converting to size_t: a negative int would wrap into a huge size_t.
    if(width <= 0 || height <= 0){
        throw std::invalid_argument("width or height is illegal!");
    }
    width_ = width;
    height_ = height;
    const std::size_t total = static_cast<std::size_t>(width) * static_cast<std::size_t>(height);
    // assign: create exactly `total` elements, each equal to initVal.
    data_.assign(total, initVal);
}
// @brief wrap an existing flat buffer.
// @param width number of columns, must be positive.
// @param height number of rows, must be positive.
// @param flatData row-major pixels, length must be exactly width * height.
Image::Image(int width, int height, const std::vector<double>& flatData){
    if(width <= 0 || height <= 0){
        throw std::invalid_argument("width or height is illegal!");
    }
    const std::size_t total = static_cast<std::size_t>(width) * static_cast<std::size_t>(height);
    // a mismatched buffer would later cause out-of-bounds reads inside rawAt.
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

// @brief bounds-checked access, writable version (returned reference can be assigned).
double& Image::at(int r, int c){
    if(r < 0 || r >= height_ || c < 0 || c >= width_) {
        throw std::out_of_range("The given coordinate is illegal!");
    }
    // row-major mapping: skip r whole rows (each width_ pixels), then c steps to the right.
    return data_[static_cast<std::size_t>(r) * static_cast<std::size_t>(width_) + static_cast<std::size_t>(c)];
}
// @brief bounds-checked access, read-only version (the trailing const picks this overload).
const double& Image::at(int r, int c) const{
    if(r < 0 || r >= height_ || c < 0 || c >= width_) {
        throw std::out_of_range("The given coordinate is illegal!");
    }
    return data_[static_cast<std::size_t>(r) * static_cast<std::size_t>(width_) + static_cast<std::size_t>(c)];
}
// @brief unchecked access for hot loops, writable version.
double& Image::rawAt(int r, int c) noexcept {
    // no if check at all: the caller promises (r, c) is inside.
    return data_[static_cast<std::size_t>(r) * static_cast<std::size_t>(width_) + static_cast<std::size_t>(c)];
}
// @brief unchecked access for hot loops, read-only version.
const double& Image::rawAt(int r, int c) const noexcept {
    return data_[static_cast<std::size_t>(r) * static_cast<std::size_t>(width_) + static_cast<std::size_t>(c)];
}

// @brief parse a PGM file (P2 text or P5 binary) into an Image.
// @param filepath path of the .pgm file.
// @return the decoded image.
// @throws std::runtime_error on unreadable file, bad magic, bad header or truncated pixel data.
Image Image::loadPGM(const std::string& filepath){
    // binary mode: without it the OS may translate '\n' and silently corrupt P5 bytes.
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filepath);
    }

    // 1) magic number: "P2" = ASCII body, "P5" = raw byte body.
    // both conditions must hold, so they are joined by && (not ||).
    std::string tag;
    file >> tag;
    if(tag != "P2" && tag != "P5"){
        throw std::runtime_error("no valid tag! It should be P2 or P5!");
    }

    // 2) header numbers, each one may be preceded by a '#' comment.
    skipWhitespaceAndComment(file);
    int width = 0;
    file >> width;
    skipWhitespaceAndComment(file);
    int height = 0;
    file >> height;
    skipWhitespaceAndComment(file);
    int maxVal = 0;
    file >> maxVal;
    // a failed ">>" leaves the variable at 0, so !file catches garbage header text too.
    if (!file || width <= 0 || height <= 0 || maxVal <= 0 || maxVal > 255){
        throw std::runtime_error("illegal Picture!");
    }

    const std::size_t total = static_cast<std::size_t>(width) * static_cast<std::size_t>(height);
    std::vector<double> data;
    // reserve capacity only, push_back still creates the elements.
    data.reserve(total);

    if (tag == "P2") {
        // text body: whitespace separated decimal integers.
        for(std::size_t i = 0; i < total; ++i){
            int v = 0;
            // if the file ends early, ">>" fails: refuse to fill the rest with zeros silently.
            if (!(file >> v)) {
                throw std::runtime_error("truncated P2 pixel data: " + filepath);
            }
            data.push_back(static_cast<double>(v));
        }
    } else {
        // binary body: exactly one whitespace byte sits between maxVal and the first pixel.
        // get() eats that single byte; "file >> std::ws" is WRONG here, because a pixel
        // whose value is 10 or 32 would also be swallowed as a newline / space.
        file.get();

        std::vector<std::uint8_t> buf(total);
        // read() wants char*: reinterpret_cast only relabels the pointer, the bytes stay the same.
        file.read(reinterpret_cast<char*>(buf.data()), static_cast<std::streamsize>(total));
        // gcount() = number of bytes actually read: catches truncated files.
        if (file.gcount() != static_cast<std::streamsize>(total)) {
            throw std::runtime_error("truncated P5 pixel data: " + filepath);
        }
        for (std::uint8_t v : buf){
            data.push_back(static_cast<double>(v));
        }
    }
    return Image(width, height, data);
}

// @brief write this image as a P5 (binary) PGM file.
// @param filepath destination path.
// @throws std::invalid_argument if the image is empty, std::runtime_error on I/O failure.
void Image::savePGM(const std::string& filepath) const{
    // four conditions joined by ||: any single one aborts (a plain "width || height" would never work).
    if(width_ <= 0 || height_ <= 0){
        throw std::invalid_argument("width or height is illegal!");
    }

    std::ofstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + filepath);
    }

    // header: always P5, maxVal fixed to 255. the last '\n' separates header from body.
    file << "P5\n" << width_ << ' ' << height_ << "\n255\n";

    // body: one byte per pixel. reserve() only reserves capacity, it does not fill the buffer.
    std::vector<std::uint8_t> buf;
    buf.reserve(data_.size());
    for(const double v : data_){
        // three separate steps: clamp the range, round to nearest, then store as one byte.
        // each call RETURNS a new value, it does not modify v, so the result must be assigned.
        const double clamped = clamp(v, 0.0, 255.0);
        buf.push_back(static_cast<std::uint8_t>(std::lround(clamped)));
    }

    // one single write call: reinterpret_cast<char*> relabels the pointer, the bytes stay the same.
    file.write(reinterpret_cast<const char*>(buf.data()), static_cast<std::streamsize>(buf.size()));
    // a full disk or a closed stream would only show up here.
    if (!file) {
        throw std::runtime_error("failed to write PGM file: " + filepath);
    }
}


}
