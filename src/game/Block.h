//
// Created by kurbaniec on 05.06.2021.
//

#ifndef BLOCK_GAME_BLOCK_H
#define BLOCK_GAME_BLOCK_H

#include <vector>

class Block {
public:
    void draw();

    static auto& get() {
        static Block board;
        return board;
    }
    Block(const Block&) = delete;
    Block& operator=(const Block &) = delete;
    Block(Block &&) = delete;
    Block & operator=(Block &&) = delete;
private:
    Block();
    int x;
    int y;
    std::vector<std::vector<int>> shape;
};

#endif //BLOCK_GAME_BLOCK_H
