#pragma once

#include "base_filter.h"
#include "../image.h"

class Negative : public Filter {
public:
    Image Transform(Image& img) override;
};
