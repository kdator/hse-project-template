#include "bmp.hpp"

class Filter {
public:
    virtual void Do(BMP* bmp) const = 0;
};

class MyFilter : public Filter {
public:
    void Do(BMP* bmp) const override {
        bmp->GetPixel(0, 1).green *= 10;
    }
};