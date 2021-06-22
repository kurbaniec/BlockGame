//
// Represents an active game piece on the board.
// A game piece is represented by coordinates on the game board (x, y)
// and a shape definition (2x2 - 4x4 matrix).
// Integer values higher than zero in the shape definition represent the actual
// "visible" game piece and are used for collision detection & drawing.
// 
// Created by kurbaniec on 05.06.2021.
//

#include "Block.h"
#include "Config.h"
#include "Board.h"
#include <GL/glut.h>
#include "../utils/MathUtils.h"
#include "DrawColor.h"
#include "Shapes.h"

Block::Block() { // NOLINT(cppcoreguidelines-pro-type-member-init)
	reset();
}

/**
 * Reset - Add new game piece
 */
void Block::reset() {
	x = 2;
	y = 0;
	shape = Shapes::randomShape();
	auto color = DrawColor::randomColor();
	shape = MathUtils::multiply(shape, color);
}

/**
 * Save game piece color code coordinates to board
 */
void Block::saveToBoard() {
	Board::get().saveToBoard(x, y, shape);
}

/**
 * Draw active game piece
 */
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

				// set a random Color for the Block. 
				DrawColor::setColor(color);

				auto rectX = bg[3][0] + (float(x + j) * rectWidth);
				auto rectY = bg[3][1] - (float(y + i) * rectHeight);

				glBegin(GL_QUADS);
				// glTexCoord2f is needed so that the Texture is visible
				glTexCoord2f(0.0f, 0.0f); glVertex3f(rectX, rectY - rectHeight, 0);                 // Left bottom
				glTexCoord2f(1.0f, 0.0f); glVertex3f(rectX + rectWidth, rectY - rectHeight, 0);  // Right bottom
				glTexCoord2f(1.0f, 1.0f); glVertex3f(rectX + rectWidth, rectY, 0);                  // Right Top
				glTexCoord2f(0.0f, 1.0f); glVertex3f(rectX, rectY, 0);                                 // Left Top

				glEnd();
				glDisable(GL_TEXTURE_2D);
			}
		}
	}
}

/**
 * Move game piece on the board
 */
void Block::move(int x_offset, int y_offset) {
	if (Board::get().valid(x + x_offset, y + y_offset, shape)) {
		x += x_offset;
		y += y_offset;
	}
}

/**
 * Move game piece to the left
 */
void Block::moveLeft() {
	move(-1, 0);
}

/**
 * Move game piece to the right
 */
void Block::moveRight() {
	move(1, 0);
}

/**
 * Move game piece down
 */
void Block::moveDown() {
	move(0, 1);
}

/**
 * Game piece Hard drop
 */
void Block::drop() {
	auto bottom = false;
	do {
		if (Board::get().valid(x, y + 1, shape)) {
			y += 1;
		}
		else {
			bottom = true;
		}
	} while (!bottom);
}

/**
 * Rotate game piece by 90 degrees clockweise
 */
void Block::rotate() {
	// Copy shape
	// See: https://stackoverflow.com/a/6435103/12347616
	std::vector<std::vector<int>> new_shape(shape);
	// Rotate shape clockwise
	// See: https://michael-karen.medium.com/learning-modern-javascript-with-tetris-92d532bcd057
	// First transpose matrix
	auto tp_matrix = MathUtils::transpose(new_shape);
	// Get permutation matrix for given shape size
	auto permut_matrix = MathUtils::permutationMatrix<int>(int(shape.size()));
	// Then multiply it with the defined rotation matrix
	new_shape = MathUtils::multiply(tp_matrix, permut_matrix);
	if (Board::get().valid(x, y, new_shape)) {
		shape = new_shape;
	}
}

/**
 * Check if game piece reached bottom
 */
bool Block::bottom() {
	return Board::get().bottom(x, y, shape);
}

/**
 * Check for game over
 */
bool Block::end() {
	if (!Board::get().valid(x, y, shape)) {
		shape = std::vector<std::vector<int>>{
				{0, 0, 0},
				{0, 0, 0},
				{0, 0, 0}
		};
		return true;
	}
	return false;
}


