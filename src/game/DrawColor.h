//
// Created by kurbaniec on 06.06.2021.
//

#ifndef BLOCK_GAME_DRAWCOLOR_H
#define BLOCK_GAME_DRAWCOLOR_H

#include <random>
#include <GL/glut.h>
#include <GL/gl.h>  
#include <GL/glu.h> 

class DrawColor {
public:
    static void setColor(int color);
    static GLuint loadText(const char *filename);

    static int randomColor();

private:
    static std::random_device random_device;
    static std::mt19937 engine;
};

enum Color {
    EMPTY = 0,
    RED = 1,
    BLUE = 2,
    GREEN = 3,
    ORANGE = 4
};


// Empty is not considered a Color
const int Color_Count = 4;


#endif //BLOCK_GAME_DRAWCOLOR_H
