//
// Created by kurbaniec on 05.06.2021.
//

#include <iostream>
#include "Board.h"

Board::Board() {
    rows = 0;
    cols = 0;
    board = std::vector<std::vector<float>>();
}

void Board::setup(int row_count, int col_count) {
    rows = row_count;
    cols = col_count;
    // Setup board
    board = std::vector<std::vector<float>>(rows);
    for (auto i = 0; i < rows; i++) {
        // Create vector with column size
        // See: https://stackoverflow.com/a/11457626/12347616
        //std::vector<int> col(cols);
        // Initialize with zeros
        // See: https://stackoverflow.com/a/8848612/12347616
        //std::fill(col.begin(), col.end(), 0);
        // Found easier way
        // See: https://www.geeksforgeeks.org/vector-assign-in-c-stl/
        std::vector<float> col;
        col.assign(cols, 0);
        board[i] = col;
    }
}

void Board::reset() {
    for (auto i = 0; i < rows; i++) {
        std::vector<float> col;
        col.assign(cols, 0);
        board[i] = col;
    }
}

int Board::getRows() {
    return rows;
}

int Board::getCols() {
    return cols;
}

std::vector<std::vector<float>> Board::getBoard() {
    return board;
}








