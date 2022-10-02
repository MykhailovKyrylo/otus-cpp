#include <iostream>

#include "matrix.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    Matrix<2, int, 0> matrix;

    const auto size = 9;

    for (auto i = 0; i < size; i++) {
        matrix[i][i] = i;
        matrix[i][size - i - 1] = size - 1 - i;
    }

    const auto l = 0;
    const auto r = 9;
    for (auto i = l; i < r; i++) {
        for (auto j = l; j < r; j++) {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }

    std::cout << matrix.getSize() << '\n';
    for (auto [cell_idx, cell_value] : matrix) {
        const auto [x, y] = cell_idx;
        std::cout << x << ' ' << y << ' ' << cell_value << '\n';
    }
}
