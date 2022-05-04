#pragma once

#include "color.h"

#include <string>
#include <vector>

class Image {
public:
    Image(size_t width, size_t height);
    Image(const std::string& img_path);
    Image(const Image& img, size_t width, size_t height);

    void Save(const std::string& saving_path);

    Color GetColor(size_t x, size_t y) const;
    void SetColor(const Color& color, size_t x, size_t y);

    size_t GetWidth() const;

    size_t GetHeight() const;

private:
    size_t width_;
    size_t height_;
    std::vector<Color> img_;
};
