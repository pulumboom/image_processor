#pragma once

#include "base_filter.h"
#include "../image.h"

class EdgeDetection : public Filter {
public:
    EdgeDetection(double threshold);
    Image Transform(Image& img) override;

private:
    std::vector<double> matrix3x3_{0, -1, 0, -1, 4, -1, 0, -1, 0};
    double threshold_;
};

