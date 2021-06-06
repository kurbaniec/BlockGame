//
// Created by kurbaniec on 06.06.2021.
//

#ifndef BLOCK_GAME_SHAPES_H
#define BLOCK_GAME_SHAPES_H


#include <vector>
#include <random>

class Shapes {
public:
    static std::vector<std::vector<std::vector<int>>> shapes() {
        // Static vector
        // See: https://stackoverflow.com/a/31608148/12347616
        static std::vector<std::vector<std::vector<int>>> shapes{
                {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
                {{1, 0, 0},    {1, 1, 1},    {0, 0, 0}},
                {{0, 0, 1},    {1, 1, 1},    {0, 0, 0}},
                {{1, 1},       {1, 1}},
                {{0, 1, 1},    {1, 1, 0},    {0, 0, 0}},
                {{0, 1, 0},    {1, 1, 1},    {0, 0, 0}},
                {{1, 1, 0},    {0, 1, 1},    {0, 0, 0}}
        };
        return shapes;
    };

    static std::vector<std::vector<int>> randomShape();

private:
    static std::random_device random_device;
    static std::mt19937 engine;
};


#endif //BLOCK_GAME_SHAPES_H
