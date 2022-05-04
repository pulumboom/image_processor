#pragma once

#include "image.h"

#include <vector>

Color ApplyMatrix(const Image& img, const std::vector<double>& matrix, size_t x, size_t y, size_t n = 1,
                  bool cells_out = true);
