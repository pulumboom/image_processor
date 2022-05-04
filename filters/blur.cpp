#include "blur.h"

#include "../matrix.h"

#include <math.h>

namespace {

double Gaussian(double x, double dx, double sigma) {
    double a = (x - dx) / sigma;

    return std::exp(-0.5 * a * a);
}

}  // namespace

Blur::Blur(double sigma) : sigma_(sigma) {
    kernel_radius_ = sigma_ * 2;
    double sum = 0;

    kernel_ = std::vector<double>((2 * kernel_radius_ + 1) * (2 * kernel_radius_ + 1));

    for (size_t row = 0; row < 2 * kernel_radius_ + 1; ++row) {
        for (size_t col = 0; col < 2 * kernel_radius_ + 1; ++col) {
            double x = Gaussian(row, kernel_radius_, sigma_) * Gaussian(col, kernel_radius_, sigma_);
            kernel_[row * (2 * kernel_radius_ + 1) + col] = x;
            sum += x;
        }
    }

    for (size_t row = 0; row < 2 * kernel_radius_ + 1; ++row) {
        for (size_t col = 0; col < 2 * kernel_radius_ + 1; ++col) {
            kernel_[row * (2 * kernel_radius_ + 1) + col] /= sum;
        }
    }
}

Image Blur::Transform(Image& img) {
    Image result(img);

    for (size_t y = 0; y < img.GetHeight(); ++y) {
        for (size_t x = 0; x < img.GetWidth(); ++x) {
            result.SetColor(ApplyMatrix(img, kernel_, x, y, kernel_radius_, false), x, y);
        }
    }

    return result;
}
