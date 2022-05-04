#pragma once

#include "../image.h"

class Filter {
public:
    virtual Image Transform(Image& img) = 0;

    virtual ~Filter() = default;
};