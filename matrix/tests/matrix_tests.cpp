#include <gtest/gtest.h>

#include <vector>

#include "matrix.h"

TEST(matrix, basic_test) {
    Matrix<2, int, -1> matrix;

    ASSERT_EQ(matrix.getSize(), 0);

    const int a = matrix[0][0];
    ASSERT_EQ(a, -1);
    ASSERT_EQ(matrix.getSize(), 0);

    matrix[100][100] = 314;
    ASSERT_EQ(matrix[100][100], 314);
    ASSERT_EQ(matrix.getSize(), 1);

    std::ostringstream out;
    for (auto [cell_idx, cell_value] : matrix) {
        const auto [x, y] = cell_idx;
        out << x << y << cell_value;
    }

    ASSERT_EQ(out.str(), "100100314");
}
