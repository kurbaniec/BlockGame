//
// Created by kurbaniec on 05.06.2021.
//

#include "Block.h"
#include "Config.h"
#include "Board.h"
#include <GL/glut.h>

Block::Block() {
    // TODO generate random block element
    x = 1;
    y = 1;
    shape = std::vector<std::vector<int>> {
            {1, 0, 0},
            {1, 1, 1},
            {0, 1, 0}
    };
}

void Block::draw() {
    /*
     // Background with a 1:2 ratio
    auto bg = Config::backgroundPoints();
    glColor3f(1, 1, 1); // White
    glBegin(GL_QUADS);
    glVertex3f(bg[0][0], bg[0][1], bg[0][2]);
    glVertex3f(bg[1][0], bg[1][1], bg[1][2]);
    glVertex3f(bg[2][0], bg[2][1], bg[2][2]);
    glVertex3f(bg[3][0], bg[3][1], bg[3][2]);
    glEnd();
     */

    auto bg = Config::backgroundPoints();
    auto rows = Board::get().getRows();
    auto cols = Board::get().getCols();

    auto rectWidth = (bg[1][0] - bg[0][0]) / float(cols);
    auto rectHeight = (bg[3][1] - bg[0][1]) / float(rows);

    for (auto i=0; i < shape.size(); i++) {
        for (auto j=0; j < shape[i].size(); j++) {
            auto color = shape[i][j];
            if (color != Color::EMPTY) {
                // TODO set color
                glColor3f(0, 0, 1);

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

void Block::rotate() {

}


