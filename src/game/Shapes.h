//
// Created by kurbaniec on 06.06.2021.
//

#ifndef BLOCK_GAME_SHAPES_H
#define BLOCK_GAME_SHAPES_H


#include <vector>

class Shapes {
    static std::vector<std::vector<std::vector<int>>> shapes() {
        // Static vector
        // See: https://stackoverflow.com/a/31608148/12347616
        static std::vector<std::vector<std::vector<int>>> shapes {
                {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
                {{2, 0, 0}, {2, 2, 2}, {0, 0, 0}},
                {{0, 0, 3}, {3, 3, 3}, {0, 0, 0}},
                {{4, 4}, {4, 4}},
                {{0, 5, 5}, {5, 5, 0}, {0, 0, 0}},
                {{0, 6, 0}, {6, 6, 6}, {0, 0, 0}},
                {{7, 7, 0}, {0, 7, 7}, {0, 0, 0}}
        };
        return shapes;
    };
};


#endif //BLOCK_GAME_SHAPES_H
