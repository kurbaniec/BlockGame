//
// Created by kurbaniec on 05.06.2021.
//

#ifndef BLOCK_GAME_BLOCK_H
#define BLOCK_GAME_BLOCK_H

#include <vector>

class Block {
public:
    void draw();

    void moveLeft();

    void moveRight();

    void moveDown();

    void drop();

    void rotate();

    bool bottom();

    void saveToBoard();

    void reset();

    bool end();

    static auto &get() {
        static Block board;
        return board;
    }

    Block(const Block &) = delete;

    Block &operator=(const Block &) = delete;

    Block(Block &&) = delete;

    Block &operator=(Block &&) = delete;

private:
    int x;
    int y;
    std::vector<std::vector<int>> shape;

    Block();

    void move(int x_offset, int y_offset);
};

#endif //BLOCK_GAME_BLOCK_H
