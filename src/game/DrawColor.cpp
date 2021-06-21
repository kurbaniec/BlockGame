//
// Created by kurbaniec on 06.06.2021.
//

#include <GL/glut.h>
#include <GL/gl.h>  
#include <GL/glu.h> 
#include "DrawColor.h"
#include <random>
#include "../utils/tga.h"
#include "MyTexture.h"

std::random_device DrawColor::random_device;
std::mt19937 DrawColor::engine(DrawColor::random_device());


// this boolean is needed so we can check if the textures are already initialized
bool initTexture = false;

GLuint red;
GLuint blue;
GLuint green;
GLuint orange;
GLuint yellow;
GLuint purple;
GLuint darkblue;

/*
* This method is needed so that the textures are initialized only once. If this is not considered,
* the textures are constantly reinitialized and the program crashes.
*/
void initColor() {
   
    red = MyTexture::bindTexture("myimages/RedNew.tga", 1);
    blue = MyTexture::bindTexture("myimages/BlueCyan.tga", 1);
    green = MyTexture::bindTexture("myimages/GreenNew.tga", 1);
    orange = MyTexture::bindTexture("myimages/OrangeNew.tga", 1);
    yellow = MyTexture::bindTexture("myimages/YellowNew.tga", 1);
    purple = MyTexture::bindTexture("myimages/PurpleNew.tga", 1);
    darkblue = MyTexture::bindTexture("myimages/BlueNew.tga", 1);
    initTexture = true;
    
}


/*
* Binding the Texture to the Blocks.
*/
void DrawColor::setColor(int color) {
    if (initTexture == false) {
        initColor();
    }
    switch (color) {
        case Color::RED:
            //glColor3f(1, 0, 0);
            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
            glBindTexture(GL_TEXTURE_2D, red);

            break;
        case Color::BLUE:
            //glColor3f(0, 0, 1);           
            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
            glBindTexture(GL_TEXTURE_2D, blue);

            break;
        case Color::GREEN:
            //glColor3f(0, 1, 0);
            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
            glBindTexture(GL_TEXTURE_2D, green);
            break;
        case Color::ORANGE:
            //glColor3f(0, 1, 0);
            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
            glBindTexture(GL_TEXTURE_2D, orange);
            break;
        case Color::YELLOW:
            //glColor3f(0, 1, 0);
            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
            glBindTexture(GL_TEXTURE_2D, yellow);
            break;
        case Color::PURPLE:
            //glColor3f(0, 1, 0);
            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
            glBindTexture(GL_TEXTURE_2D, purple);
            break;
        case Color::DARKBLUE:
            //glColor3f(0, 1, 0);
            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
            glBindTexture(GL_TEXTURE_2D, darkblue);
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
