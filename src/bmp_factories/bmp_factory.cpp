#include <bmp_factories/bmp_factory.hpp>

#include <iostream>
#include <memory>

#include <bmp.hpp>

namespace bmp {

std::unique_ptr<BMP> BmpFromCLIFactory::CreatePicture() const {
    std::cout << "From BmpFromCLIFactory, color = " << color_ << std::endl;
    return std::make_unique<BMP>();
}

std::unique_ptr<BMP> BmpFromFile::CreatePicture() const  {
    std::cout << "From BmpFromFile, file_path = " << file_path_ << std::endl;
    return std::make_unique<BMP>();
}

}
