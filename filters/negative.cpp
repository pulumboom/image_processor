#include "negative.h"

Image Negative::Transform(Image& img) {
    Image result(img.GetWidth(), img.GetHeight());

    for (size_t y = 0; y < img.GetHeight(); ++y) {
        for (size_t x = 0; x < img.GetWidth(); ++x) {
            Color cur_color;
            cur_color.red = 1 - img.GetColor(x, y).red;
            cur_color.green = 1 - img.GetColor(x, y).green;
            cur_color.blue = 1 - img.GetColor(x, y).blue;

            result.SetColor(cur_color, x, y);
        }
    }

    return result;
}
