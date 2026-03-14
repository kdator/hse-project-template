#pragma once

#include <vector>

class BMP {
public:
    struct BMPPixel {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    };

public:
    BMP() : width_(0), height_(0) {}

public:
    std::vector<BMP::BMPPixel>& GetPixels() noexcept { return pixels_; }

    BMPPixel& GetPixel(uint8_t x, uint8_t y) { return pixels_[width_ * x + y];} 

private:
    const size_t width_;
    const size_t height_;
    std::vector<BMP::BMPPixel> pixels_;
};
