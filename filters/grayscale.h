#pragma once

#include "base_filter.h"
#include "../image.h"

class Grayscale : public Filter {
public:
    Image Transform(Image& img) override;
};
