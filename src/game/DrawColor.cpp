//
// Created by kurbaniec on 06.06.2021.
//

#include <GL/glut.h>
#include "DrawColor.h"

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
