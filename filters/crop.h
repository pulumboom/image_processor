#pragma once

#include "base_filter.h"
#include "../image.h"

class Crop : public Filter {
public:
    Crop(int w, int h);

    Image Transform(Image& img) override;

private:
    size_t width_;
    size_t height_;
};

