#include "crop.h"

#include "../color.h"

Crop::Crop(int w, int h) : width_(w), height_(h) {
}

Image Crop::Transform(Image& img) {
    if (width_ >= img.GetWidth() && height_ >= img.GetHeight()) {
        return img;
    }

    Image result(img, std::min(img.GetWidth(), width_), std::min(img.GetHeight(), height_));

    return result;
}
