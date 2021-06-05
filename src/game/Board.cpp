//
// Created by kurbaniec on 05.06.2021.
//

#include <iostream>
#include "Board.h"

Board::Board(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;
    // Setup board
    this->board = std::vector<std::vector<int>>(this->rows);
    for (auto i = 0; i < this->rows; i++) {
        // Create vector with column size
        // See: https://stackoverflow.com/a/11457626/12347616
        //std::vector<int> col(cols);
        // Initialize with zeros
        // See: https://stackoverflow.com/a/8848612/12347616
        //std::fill(col.begin(), col.end(), 0);
        // Found easier way
        // See: https://www.geeksforgeeks.org/vector-assign-in-c-stl/
        std::vector<int> col;
        col.assign(this->cols, 0);
        this->board[i] = col;
    }
}

int Board::getRows() {
    return this->rows;
}

int Board::getCols() {
    return this->cols;
}




