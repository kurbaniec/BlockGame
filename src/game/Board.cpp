//
// Represents the game board.
// The game board is a matrix defined by row & column count filled with zeroes.
// When game pieces reach the bottom they are persisted onto the board through
// integer values higher than zero.
// Values higher than zero are used for collision detection & drawing.
// 
// Created by kurbaniec on 05.06.2021.
//

#include <iostream>
#include "Board.h"
#include "Config.h"
#include "DrawColor.h"
#include <GL/glut.h>
#include "algorithm"

Board::Board() {
	rows = 0;
	cols = 0;
	board = std::vector<std::vector<int>>();
}

/**
 * Initialize game board
 * Creates a matrix defined by row & column count filled with zeroes
 */
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

/**
 * Reset and clear game board
 */
void Board::reset() {
	for (auto i = 0; i < rows; i++) {
		std::vector<int> col;
		col.assign(cols, 0);
		board[i] = col;
	}
}

/**
 * Get row count
 */
int Board::getRows() {
	return rows;
}

/**
 * Get column count
 */
int Board::getCols() {
	return cols;
}

/**
 * Get game board matrix
 */
std::vector<std::vector<int>> Board::getBoard() {
	return board;
}

/**
 * Check if given game piece is valid on the game board
 */
bool Board::valid(int new_x, int new_y, const std::vector<std::vector<int>>& shape) {
	if (new_x + shape.size() <= 0 || new_y + shape.size() <= 0 || (new_y + 1) >= rows) {
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

/**
 * Check if given game piece reached bottom on the game board
 */
bool Board::bottom(int x, int y, const std::vector<std::vector<int>>& shape) {
	if ((y + 1) >= rows) {
		return true;
	}

	for (auto i = 0; i < shape.size(); i++) {
		for (auto j = 0; j < shape[i].size(); j++) {
			if (shape[i][j] == Color::EMPTY) continue;
			if (y + i + 1 >= rows) {
				return true;
			}
			if (board[y + i + 1][x + j] != Color::EMPTY) {
				return true;
			}
		}
	}

	return false;
}

/**
 * Save game piece to game board matrix structure
 */
void Board::saveToBoard(int x, int y, const std::vector<std::vector<int>>& shape) {
	for (auto i = 0; i < shape.size(); i++) {
		for (auto j = 0; j < shape[i].size(); j++) {
			if (shape[i][j] == Color::EMPTY) continue;
			board[y + i][x + j] = shape[i][j];
		}
	}
}

/**
 * Draw game board (consisting of game pieces that already reached bottom)
 */
void Board::draw() {
	auto bg = Config::backgroundPoints();

	auto rectWidth = (bg[1][0] - bg[0][0]) / float(cols);
	auto rectHeight = (bg[3][1] - bg[0][1]) / float(rows);

	// Draw board game blocks color after color
	// This approach mitigates `setColor` calls
	for (auto c = 1; c <= Color_Count; c++) {
		// Set draw color
		// set the Color for the Block. 

		DrawColor::setColor(c);
		for (auto i = 0; i < board.size(); i++) {
			for (auto j = 0; j < board[i].size(); j++) {
				auto color = board[i][j];
				if (color == c) {

					auto rectX = bg[3][0] + (float(j) * rectWidth);
					auto rectY = bg[3][1] - (float(i) * rectHeight);

					glBegin(GL_QUADS);
					// glTexCoord2f is needed so that the Texture is visible
					glTexCoord2f(0.0f, 0.0f); glVertex3f(rectX, rectY - rectHeight, 0);              // Left bottom
					glTexCoord2f(1.0f, 0.0f); glVertex3f(rectX + rectWidth, rectY - rectHeight, 0);  // Right bottom
					glTexCoord2f(1.0f, 1.0f); glVertex3f(rectX + rectWidth, rectY, 0);               // Right Top
					glTexCoord2f(0.0f, 1.0f); glVertex3f(rectX, rectY, 0);                           // Left Top
					glEnd();
				}
			}
		}
	}
}

/**
 * Clear full lines on the game board
 */
int Board::lineClear() {
	// Remove element while iterating
	// See: https://stackoverflow.com/a/13102374/12347616
	auto it = board.begin();
	int inserts = 0;
	while (it != board.end()) {
		// Check if row has one or more zeroes
		// See: https://stackoverflow.com/a/3246912/12347616
		if (std::find((*it).begin(), (*it).end(), 0) != (*it).end()) {
			// If yes, continue
			++it;
		}
		else {
			// If no, remove line
			it = board.erase(it);
			// Increment inserts
			inserts++;

		}
	}

	// Add new empty lines on top
	// See: https://stackoverflow.com/a/48251347/12347616
	for (auto i = 0; i < inserts; i++) {
		std::vector<int> col;
		col.assign(cols, 0);
		board.insert(board.begin(), col);
	}
	return inserts;
}








