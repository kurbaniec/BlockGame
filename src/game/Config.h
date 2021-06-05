//
// Created by kurbaniec on 05.06.2021.
//

#ifndef BLOCK_GAME_CONFIG_H
#define BLOCK_GAME_CONFIG_H


#include <vector>

class Config {
public:
    static std::vector<std::vector<float>> backgroundPoints();
    static float speed();
    static float cameraVisibleRange();
};

enum Color {
    EMPTY = 0,
    RED = 1,
};


#endif //BLOCK_GAME_CONFIG_H
