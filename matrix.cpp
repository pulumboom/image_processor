#include "matrix.h"

namespace {

struct Cell {
    size_t x;
    size_t y;
};

std::vector<Cell> GetCellNeighbors(const Image& img, size_t x, size_t y, size_t n = 3, bool cells_out = true) {
    std::vector<Cell> cell_neighbors;
    int df = n / 2;

    if (cells_out) {
        for (int dy = -df; dy <= df; ++dy) {
            for (int dx = -df; dx <= df; ++dx) {
                size_t ny = std::clamp<int>(static_cast<int>(y) + dy, 0, img.GetHeight() - 1);
                size_t nx = std::clamp<int>(static_cast<int>(x) + dx, 0, img.GetWidth() - 1);
                if (ny < img.GetHeight() && nx < img.GetWidth()) {
                    cell_neighbors.push_back(Cell{nx, ny});
                } else if (ny >= img.GetHeight() && nx >= img.GetWidth()) {
                    cell_neighbors.push_back(Cell{x, y});
                } else if (ny >= img.GetHeight()) {
                    cell_neighbors.push_back(Cell{nx, y});
                } else {
                    cell_neighbors.push_back(Cell{x, ny});
                }
            }
        }
    } else {
        for (int dy = -df; dy <= df; ++dy) {
            for (int dx = -df; dx <= df; ++dx) {
                size_t ny = y + dy, nx = x + dx;
                if (ny < img.GetHeight() && nx < img.GetWidth()) {
                    cell_neighbors.push_back(Cell{nx, ny});
                }
            }
        }
    }

    return cell_neighbors;
}

}  // namespace

Color ApplyMatrix(const Image& img, const std::vector<double>& matrix, size_t x, size_t y, size_t n, bool cells_out) {
    double red = 0;
    double green = 0;
    double blue = 0;

    auto cell_neighbors = GetCellNeighbors(img, x, y, (n + n + 1) * (n + n + 1), cells_out);

    for (int i = 0; i < (n + n + 1) * (n + n + 1); ++i) {
        red += img.GetColor(cell_neighbors[i].x, cell_neighbors[i].y).red * matrix[i];
        green += img.GetColor(cell_neighbors[i].x, cell_neighbors[i].y).green * matrix[i];
        blue += img.GetColor(cell_neighbors[i].x, cell_neighbors[i].y).blue * matrix[i];
    }

    red = std::clamp(red, 0.0, 1.0);
    green = std::clamp(green, 0.0, 1.0);
    blue = std::clamp(blue, 0.0, 1.0);

    return Color(red, green, blue);
}