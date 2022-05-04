#include "sharpening.h"

#include "../matrix.h"

Image Sharpening::Transform(Image& img) {
    Image result(img);

    for (size_t y = 0; y < img.GetHeight(); ++y) {
        for (size_t x = 0; x < img.GetWidth(); ++x) {
            result.SetColor(ApplyMatrix(img, matrix3x3_, x, y), x, y);
        }
    }

    return result;
}
