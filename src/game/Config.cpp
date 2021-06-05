//
// Created by kurbaniec on 05.06.2021.
//

#include "Config.h"
#include <cstdlib>

std::vector<std::vector<float>> Config::backgroundPoints() {

    /*
    glVertex3f(-2, -4, 0);  // Left bottom
    glVertex3f(2, -4, 0);   // Right bottom
    glVertex3f(2, 4, 0);    // Right Top
    glVertex3f(-2, 4, 0);   // Left Top
     */

    // Left bottom - right bottom - right top - left top
    return std::vector<std::vector<float>> {
            {-2, -4, 0}, {2, -4, 0},
            {2, 4, 0}, {-2, 4, 0}
    };
}

float Config::speed() {
    // 1 = 0.166 * 60
    return 1;
}

float Config::cameraVisibleRange() {
    // Idea is that the camera should render a bit more than the game background
    // So we take the height from `backgroundPoints` and add a little bit to it
    // Why the height? Because the game background is higher than wider
    //  (wider coordinate distribution)
    // https://gamedev.stackexchange.com/a/49698
    auto bg = backgroundPoints();
    auto margin = 0.2;
    return float(abs(bg[0][1]) + margin);
}
