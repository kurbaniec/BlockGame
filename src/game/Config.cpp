//
// Created by kurbaniec on 05.06.2021.
//

#include "Config.h"

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
