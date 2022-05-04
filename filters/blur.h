#pragma once

#include "base_filter.h"

class Blur : public Filter {
public:
    Blur(double sigma);
    Image Transform(Image& img) override;

private:
    double sigma_;
    size_t kernel_radius_;
    std::vector<double> kernel_;
};

