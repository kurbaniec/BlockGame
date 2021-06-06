//
// Created by kurbaniec on 05.06.2021.
//

#include "MathUtils.h"

/**
 * Transpose matrix (switch columns and rows)
 * Source: https://stackoverflow.com/a/49445850/12347616
 */
template<typename T>
void MathUtils::transpose(std::vector<std::vector<T>> &b) {
    if (b.empty())
        return;

    std::vector<std::vector<T> > trans_vec(b[0].size(), std::vector<T>());

    for (auto &i : b) {
        for (int j = 0; j < i.size(); j++) {
            trans_vec[j].push_back(i[j]);
        }
    }

    b = trans_vec;
}

/**
 * Multiply matrix
 * Source: https://stackoverflow.com/a/47277280/12347616
 */
template<typename T>
std::vector<std::vector<T>> MathUtils::multiply(std::vector<std::vector<T>> &a, std::vector<std::vector<T>> &b) {
    const int n = a.size();     // a rows
    const int m = a[0].size();  // a cols
    const int p = b[0].size();  // b cols

    std::vector<std::vector<T>> c(n, std::vector<T>(p, 0));
    for (auto j = 0; j < p; ++j) {
        for (auto k = 0; k < m; ++k) {
            for (auto i = 0; i < n; ++i) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

template<typename T>
std::vector<std::vector<T>> MathUtils::rotationMatrix(int size) {

    auto rotMatrix = std::vector<std::vector<T>>(size);
    for (auto i = 0; i < size; i++) {
        std::vector<T> col;
        col.assign(size, T(0));
        col[size-1-i] = T(1);
        rotMatrix[i] = col;
    }

    return rotMatrix;
}


// Template definitions
// See: https://stackoverflow.com/q/115703/12347616

template void MathUtils::transpose<int>(std::vector<std::vector<int>> &b);

template std::vector<std::vector<int>>
MathUtils::multiply(std::vector<std::vector<int>> &a, std::vector<std::vector<int>> &b);

template std::vector<std::vector<int>>
MathUtils::rotationMatrix<int>(int size);
