#pragma once

#include "base_filter.h"

class Sharpening : public Filter {
public:
    Image Transform(Image& img) override;

private:
    std::vector<double> matrix3x3_{0, -1, 0, -1, 5, -1, 0, -1, 0};
};
