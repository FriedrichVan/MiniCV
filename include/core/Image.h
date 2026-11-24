#pragma once
#include <cstddef>
#include <string>
#include <vector>

namespace minicv{

class Image{
public:
    Image() = default;
    Image(int width, int height, double initVal = 0.0);
    Image(int width, int height, const std::vector<double>& flatData);

    [[nodiscard]] int getWidth() const noexcept;
    [[nodiscard]] int getHeight() const noexcept;
    [[nodiscard]] std::size_t getSize() const noexcept;
    [[nodiscard]] const std::vector<double>& getData() const noexcept;

    [[nodiscard]] double& at(int r, int c);
    [[nodiscard]] const double& at(int r, int c) const;
    [[nodiscard]] double& rawAt(int r, int c) noexcept;
    [[nodiscard]] const double& rawAt(int r, int c) const noexcept;

    [[nodiscard]] static Image loadPGM(const std::string& filepath);
    void savePGM(const std::string& filepath) const;

private:
    int width_{0};
    int height_{0};
    std::vector<double> data_;
};

}