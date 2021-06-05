//
// Created by kurbaniec on 05.06.2021.
//

#ifndef BLOCK_GAME_BOARD_H
#define BLOCK_GAME_BOARD_H


#include <vector>

class Board {
public:

    void setup(int rows, int cols);
    void reset();

    int getRows();
    int getCols();
    std::vector<std::vector<float>> getBoard();

    // Singleton based on:
    // https://codereview.stackexchange.com/a/173935
    static auto& get() {
        static Board board;
        return board;
    }
    Board(const Board&) = delete;
    Board& operator=(const Board &) = delete;
    Board(Board &&) = delete;
    Board & operator=(Board &&) = delete;
private:
    Board();
    int cols;
    int rows;
    std::vector<std::vector<float>> board;
};


#endif //BLOCK_GAME_BOARD_H
