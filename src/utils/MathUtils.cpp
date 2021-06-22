//
// Created by kurbaniec on 05.06.2021.
//

#include "MathUtils.h"
#include <algorithm>

/**
 * Transpose matrix (switch columns and rows)
 * Source: https://stackoverflow.com/a/49445850/12347616
 */
template<typename T>
std::vector<std::vector<T>> MathUtils::transpose(std::vector<std::vector<T>>& b) {
	std::vector<std::vector<T> > tp_matrix(b[0].size(), std::vector<T>());

	for (auto& i : b) {
		for (int j = 0; j < i.size(); j++) {
			tp_matrix[j].push_back(i[j]);
		}
	}

	return tp_matrix;
}

/**
 * Multiply matrix
 * Source: https://stackoverflow.com/a/47277280/12347616
 */
template<typename T>
std::vector<std::vector<T>> MathUtils::multiply(std::vector<std::vector<T>>& a, std::vector<std::vector<T>>& b) {
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
/**
 * Multiply matrix with scalar
 */
template<typename T>
std::vector<std::vector<T>> MathUtils::multiply(std::vector<std::vector<T>>& a, int scalar) {
	// Multiply using std::transform
	// See: https://slaystudy.com/c-multiply-vector-by-scalar/
	std::vector<std::vector<T>> c(a);
	std::transform(c.begin(), c.end(), c.begin(), [scalar](std::vector<T> inner) {
		std::transform(inner.begin(), inner.end(), inner.begin(), [scalar](T value) {
			return value * scalar;
			});
		return inner;
		});
	return c;
}

/**
 * Get permutation matrix of given size
 * Multiplying with the transpose of a matrix creates a rotation by 90 degrees
 * Source: https://michael-karen.medium.com/learning-modern-javascript-with-tetris-92d532bcd057
 */
template<typename T>
std::vector<std::vector<T>> MathUtils::permutationMatrix(int size) {

	auto rot_matrix = std::vector<std::vector<T>>(size);
	for (auto i = 0; i < size; i++) {
		std::vector<T> col;
		col.assign(size, T(0));
		col[size - 1 - i] = T(1);
		rot_matrix[i] = col;
	}

	return rot_matrix;
}

// Template definitions
// See: https://stackoverflow.com/q/115703/12347616

template std::vector<std::vector<int>> MathUtils::transpose<int>(std::vector<std::vector<int>>& b);

template std::vector<std::vector<int>>
MathUtils::multiply(std::vector<std::vector<int>>& a, std::vector<std::vector<int>>& b);

template std::vector<std::vector<int>>
MathUtils::multiply(std::vector<std::vector<int>>& a, int scalar);

template std::vector<std::vector<int>>
MathUtils::permutationMatrix<int>(int size);
