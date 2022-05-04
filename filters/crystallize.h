#pragma once

#include "base_filter.h"

class Crystallize : public Filter {
public:
    Crystallize(double centres);

    Image Transform(Image& img) override;
private:
    double centres_to_pixels_;
};
