#pragma once

#include <memory>

#include "bmp.hpp"

namespace bmp {

class BmpFactory {
public:
    virtual ~BmpFactory() = default;
    BmpFactory() = default;

    BmpFactory(BmpFactory&&) = default;
    BmpFactory& operator=(BmpFactory&&) = default;
    
    virtual std::unique_ptr<BMP> CreatePicture() const = 0;
};

class BmpFromCLIFactory : public BmpFactory {
public:
    BmpFromCLIFactory() = default;

    BmpFromCLIFactory(int color) : color_(color) { }

    std::unique_ptr<BMP> CreatePicture() const override {
        std::cout << "From BmpFromCLIFactory, color = " << color_ << std::endl;
        return std::make_unique<BMP>();
    } 

private:
    int color_;
};

class BmpFromFile : public BmpFactory {
public:
    BmpFromFile() = default;

    BmpFromFile(std::string file_path) : file_path_(file_path) { }

    std::unique_ptr<BMP> CreatePicture() const override {
        std::cout << "From BmpFromFile, file_path = " << file_path_ << std::endl;
        return std::make_unique<BMP>();
    } 

private:
    std::string file_path_;
};

}
