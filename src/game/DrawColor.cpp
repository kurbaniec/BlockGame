//
// Created by kurbaniec on 06.06.2021.
//

#include <GL/glut.h>
#include "DrawColor.h"
#include <random>

std::random_device DrawColor::random_device;
std::mt19937 DrawColor::engine(DrawColor::random_device());

void DrawColor::setColor(int color) {
    switch (color) {
        case Color::RED:
            glColor3f(1, 0, 0);
            break;
        case Color::BLUE:
            glColor3f(0, 0, 1);
            break;
        default:
            glColor3f(1, 1, 1);
    }
}

int DrawColor::randomColor() {
    // Random with C++ 11
    // See: https://github.com/effolkronium/random
    // And: https://stackoverflow.com/q/32071721/12347616
    std::uniform_int_distribution<> dist(1, Color_Count);
    return dist(engine);
}
