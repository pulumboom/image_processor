#include "grayscale.h"

namespace {

const double R_COEF = 0.299;
const double G_COEF = 0.587;
const double B_COEF = 0.114;

}

Image Grayscale::Transform(Image& img) {
    Image result(img.GetWidth(), img.GetHeight());

    for (size_t y = 0; y < img.GetHeight(); ++y) {
        for (size_t x = 0; x < img.GetWidth(); ++x) {
            double grayscale = R_COEF * img.GetColor(x, y).red +
                               G_COEF * img.GetColor(x, y).green +
                               B_COEF * img.GetColor(x, y).blue;

            Color cur_color;
            cur_color.red = grayscale;
            cur_color.green = grayscale;
            cur_color.blue = grayscale;

            result.SetColor(cur_color, x, y);
        }
    }

    return result;
}
