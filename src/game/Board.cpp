//
// Created by kurbaniec on 05.06.2021.
//

#include <iostream>
#include "Board.h"
#include "Config.h"
#include "DrawColor.h"
#include <GL/glut.h>

Board::Board() {
    rows = 0;
    cols = 0;
    board = std::vector<std::vector<int>>();
}

void Board::setup(int row_count, int col_count) {
    rows = row_count;
    cols = col_count;
    // Setup board
    board = std::vector<std::vector<int>>(rows);
    for (auto i = 0; i < rows; i++) {
        // Create vector with column size
        // See: https://stackoverflow.com/a/11457626/12347616
        //std::vector<int> col(cols);
        // Initialize with zeros
        // See: https://stackoverflow.com/a/8848612/12347616
        //std::fill(col.begin(), col.end(), 0);
        // Found easier way
        // See: https://www.geeksforgeeks.org/vector-assign-in-c-stl/
        std::vector<int> col;
        col.assign(cols, 0);
        board[i] = col;
    }
}

void Board::reset() {
    for (auto i = 0; i < rows; i++) {
        std::vector<int> col;
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

std::vector<std::vector<int>> Board::getBoard() {
    return board;
}

bool Board::valid(int new_x, int new_y, const std::vector<std::vector<int>> &shape) {
    if (new_x+shape.size() <= 0 || new_y < 0 || (new_y + 1) >= rows) {
        return false;
    }

    for (auto i = 0; i < shape.size(); i++) {
        for (auto j = 0; j < shape[i].size(); j++) {
            // If the coordinate is empty (no color) skip it
            if (shape[i][j] == Color::EMPTY) continue;
            // Check if left / right / bottom border
            if (new_x + j < 0 || new_x + j >= cols || new_y + i >= rows) {
                return false;
            }
            // If there is already a game piece on the board on the position
            // then the movement of the active game piece is invalid
            if (board[new_y + i][new_x + j] != Color::EMPTY) {
                return false;
            }
        }
    }

    return true;
}

bool Board::bottom(int x, int y, const std::vector<std::vector<int>> &shape) {
    if ((y + 1) >= rows) {
        return true;
    }

    for (auto i = 0; i < shape.size(); i++) {
        for (auto j = 0; j < shape[i].size(); j++) {
            if (shape[i][j] == Color::EMPTY) continue;
            if (y + i + 1>= rows) {
                return true;
            }
            if (board[y + i + 1][x + j] != Color::EMPTY) {
                return true;
            }
        }
    }

    return false;
}

void Board::saveToBoard(int x, int y, const std::vector<std::vector<int>> &shape) {
    for (auto i = 0; i < shape.size(); i++) {
        for (auto j = 0; j < shape[i].size(); j++) {
            if (shape[i][j] == Color::EMPTY) continue;
            board[y + i][x + j] = shape[i][j];
        }
    }
}

void Board::draw() {
    auto bg = Config::backgroundPoints();

    auto rectWidth = (bg[1][0] - bg[0][0]) / float(cols);
    auto rectHeight = (bg[3][1] - bg[0][1]) / float(rows);

    for (auto i=0; i < board.size(); i++) {
        for (auto j=0; j < board[i].size(); j++) {
            auto color = board[i][j];
            if (color != Color::EMPTY) {
                // TODO filter board by callers to mitigate setColor calls
                // Set draw color
                DrawColor::setColor(color);

                auto rectX = bg[3][0] + (float(j) * rectWidth);
                auto rectY = bg[3][1] - (float(i) * rectHeight);

                glBegin(GL_QUADS);
                glVertex3f(rectX, rectY - rectHeight, 0);                 // Left bottom
                glVertex3f(rectX + rectWidth, rectY - rectHeight, 0);  // Right bottom
                glVertex3f(rectX + rectWidth, rectY, 0);                  // Right Top
                glVertex3f(rectX, rectY, 0);                                 // Left Top
                glEnd();
            }
        }
    }
}








