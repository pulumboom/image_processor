#include "crystallize.h"

#include <random>
#include <vector>

namespace {

struct Cell {
    size_t x = 0;
    size_t y = 0;
};

std::vector<Cell> GenCentresCoordinates(size_t width, size_t height, size_t n) {
    std::vector<Cell> all_cells;

    for (size_t x = 0; x < width; ++x) {
        for (size_t y = 0; y < width; ++y) {
            all_cells.push_back(Cell{x, y});
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(all_cells.begin(), all_cells.end(), g);

    all_cells.resize(n);

    return all_cells;
}

size_t Diff(size_t a, size_t b) {
    size_t res = a - b;

    if (res > std::max(a, b)) {
        res = b - a;
    }

    return res;
}

}  // namespace

Crystallize::Crystallize(double centres) : centres_to_pixels_(centres / 3000) {
}

Image Crystallize::Transform(Image& img) {
    Image result(img.GetWidth(), img.GetHeight());

    int centres_cnt = img.GetWidth() * img.GetHeight() * centres_to_pixels_;
    auto centres_coordinates = GenCentresCoordinates(img.GetWidth(), img.GetHeight(), centres_cnt);

    for (int y = 0; y < img.GetHeight(); ++y) {
        for (int x = 0; x < img.GetWidth(); ++x) {
            auto dy = Diff(y, centres_coordinates[0].y);
            auto dx = Diff(x, centres_coordinates[0].x);


            auto dmin = dy * dy + dx * dx;
            size_t nearest_centre = 0;

            for (size_t i = 1; i < centres_coordinates.size(); ++i) {
                dy = Diff(y, centres_coordinates[i].y);
                dx = Diff(x, centres_coordinates[i].x);

                auto d = dy * dy + dx * dx;

                if (d < dmin) {
                    dmin = d;
                    nearest_centre = i;
                }
            }

            result.SetColor(img.GetColor(centres_coordinates[nearest_centre].x, centres_coordinates[nearest_centre].y),
                            x, y);
        }
    }

    return result;
}
