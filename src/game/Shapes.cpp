//
// Created by kurbaniec on 06.06.2021.
//

#include "Shapes.h"
#include <random>

std::random_device Shapes::random_device;
std::mt19937 Shapes::engine(Shapes::random_device());

std::vector<std::vector<int>> Shapes::randomShape() {
    auto allShapes = shapes();
    std::uniform_int_distribution<> dist(0, int(allShapes.size() - 1));
    auto index = dist(engine);
    return allShapes[index];
}
