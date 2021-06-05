//
// Created by kurbaniec on 05.06.2021.
//

#ifndef BLOCK_GAME_BOARD_H
#define BLOCK_GAME_BOARD_H


#include <vector>

class Board {
public:
    Board(int rows, int cols);
    int getRows();
    int getCols();
private:
    int cols;
    int rows;
    std::vector<std::vector<int>> board;
};


#endif //BLOCK_GAME_BOARD_H
