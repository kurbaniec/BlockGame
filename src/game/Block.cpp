//
// Created by kurbaniec on 05.06.2021.
//

#include "Block.h"
#include "Config.h"
#include "Board.h"
#include <GL/glut.h>
#include "../utils/MathUtils.h"
#include "DrawColor.h"

Block::Block() { // NOLINT(cppcoreguidelines-pro-type-member-init)
    reset();
}

void Block::reset() {
    // TODO generate random block element
    x = 1;
    y = 0;
    shape = std::vector<std::vector<int>>{
            {1, 0, 0},
            {1, 1, 1},
            {0, 1, 0}
    };
}

void Block::saveToBoard() {
    Board::get().saveToBoard(x, y, shape);
}

void Block::draw() {
    auto bg = Config::backgroundPoints();
    auto rows = Board::get().getRows();
    auto cols = Board::get().getCols();

    auto rectWidth = (bg[1][0] - bg[0][0]) / float(cols);
    auto rectHeight = (bg[3][1] - bg[0][1]) / float(rows);

    for (auto i = 0; i < shape.size(); i++) {
        for (auto j = 0; j < shape[i].size(); j++) {
            auto color = shape[i][j];
            if (color != Color::EMPTY) {

                DrawColor::setColor(color);

                auto rectX = bg[3][0] + (float(x + j) * rectWidth);
                auto rectY = bg[3][1] - (float(y + i) * rectHeight);

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

void Block::move(int x_offset, int y_offset) {
    if (Board::get().valid(x + x_offset, y + y_offset, shape)) {
        x += x_offset;
        y += y_offset;
    }
}

void Block::moveLeft() {
    move(-1, 0);
}

void Block::moveRight() {
    move(1, 0);
}

void Block::moveDown() {
    move(0, 1);
}

/**
 * Hard drop
 */
void Block::drop() {
    auto bottom = false;
    do {
        if (Board::get().valid(x, y + 1, shape)) {
            y += 1;
        } else {
            bottom = true;
        }
    } while (!bottom);
}

void Block::rotate() {
    // Copy shape
    // See: https://stackoverflow.com/a/6435103/12347616
    std::vector<std::vector<int>> new_shape(shape);
    // Rotate shape clockwise
    // See: https://michael-karen.medium.com/learning-modern-javascript-with-tetris-92d532bcd057
    // First transpose matrix
    MathUtils::transpose(new_shape);
    std::vector<std::vector<int>> rot_matrix{
            {0, 0, 1},
            {0, 1, 0},
            {1, 0, 0}
    };
    // Then multiply it with the defined rotation matrix
    new_shape = MathUtils::multiply(new_shape, rot_matrix);
    if (Board::get().valid(x, y, new_shape)) {
        shape = new_shape;
    }
}

bool Block::bottom() {
    return Board::get().bottom(x, y, shape);
}


