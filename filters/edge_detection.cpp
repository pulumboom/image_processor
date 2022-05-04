#include "edge_detection.h"
#include "grayscale.h"
#include "../matrix.h"

EdgeDetection::EdgeDetection(double threshold) : threshold_(threshold) {
}

Image EdgeDetection::Transform(Image& img) {
    Image result(img);

    Grayscale gr;
    result = gr.Transform(result);

    for (size_t y = 0; y < img.GetHeight(); ++y) {
        for (size_t x = 0; x < img.GetWidth(); ++x) {
            Color cur_color = ApplyMatrix(img, matrix3x3_, x, y);

            if (cur_color.red > threshold_) {
                cur_color = {1, 1, 1};
            } else {
                cur_color = {0, 0, 0};
            }

            result.SetColor(cur_color, x, y);
        }
    }

    return result;
}
