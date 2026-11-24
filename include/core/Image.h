#pragma once
#include <cstddef>
#include <string>
#include <vector>

namespace minicv{

// @brief a grayscale image stored as one flat row-major vector of doubles.
// @note index of (r, c) is r * width + c, where r is the row and c is the column.
class Image{
public:
    // @brief empty image: width = 0, height = 0, no pixels.
    Image() = default;
    // @brief allocate width * height pixels, all set to initVal.
    // @throws std::invalid_argument if width <= 0 or height <= 0.
    Image(int width, int height, double initVal = 0.0);
    // @brief wrap an existing flat buffer.
    // @throws std::invalid_argument on bad size, or if flatData.size() != width * height.
    Image(int width, int height, const std::vector<double>& flatData);

    // @brief number of columns.
    [[nodiscard]] int getWidth() const noexcept;
    // @brief number of rows.
    [[nodiscard]] int getHeight() const noexcept;
    // @brief total pixel count, equals width * height.
    [[nodiscard]] std::size_t getSize() const noexcept;
    // @brief read-only access to the flat buffer (no copy, no bounds check).
    [[nodiscard]] const std::vector<double>& getData() const noexcept;

    // @brief bounds-checked pixel access, writable version.
    // @throws std::out_of_range if (r, c) is outside the image.
    [[nodiscard]] double& at(int r, int c);
    // @brief bounds-checked pixel access, read-only version (for const Image).
    [[nodiscard]] const double& at(int r, int c) const;
    // @brief unchecked pixel access for hot loops, writable version.
    [[nodiscard]] double& rawAt(int r, int c) noexcept;
    // @brief unchecked pixel access for hot loops, read-only version.
    [[nodiscard]] const double& rawAt(int r, int c) const noexcept;

    // @brief build an Image by parsing a P2 (text) or P5 (binary) PGM file.
    // @throws std::runtime_error on open failure, bad header, or truncated data.
    [[nodiscard]] static Image loadPGM(const std::string& filepath);
    // @brief write this image as a P5 (binary) PGM file, pixels clamped to [0, 255].
    // @throws std::invalid_argument if the image is empty, std::runtime_error on write failure.
    void savePGM(const std::string& filepath) const;

private:
    int width_{0};
    int height_{0};
    std::vector<double> data_;   // length == width_ * height_, row-major
};

}
