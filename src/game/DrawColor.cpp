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



void DrawColor::setColor(int color) {
    
    switch (color) {
        case Color::RED:
            //glColor3f(1, 0, 0);
            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
            glBindTexture(GL_TEXTURE_2D, MyTexture::bindTexture("myimages/RedNew.tga",1));

            break;
        case Color::BLUE:
            //glColor3f(0, 0, 1);           
            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
            glBindTexture(GL_TEXTURE_2D, MyTexture::bindTexture("myimages/BlueCyan.tga", 1));

            break;
        case Color::GREEN:
            //glColor3f(0, 1, 0);
            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
            glBindTexture(GL_TEXTURE_2D, MyTexture::bindTexture("myimages/GreenNew.tga", 1));
            break;
        case Color::ORANGE:
            //glColor3f(0, 1, 0);
            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
            glBindTexture(GL_TEXTURE_2D, MyTexture::bindTexture("myimages/OrangeNew.tga", 1));
            break;
        case Color::YELLOW:
            //glColor3f(0, 1, 0);
            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
            glBindTexture(GL_TEXTURE_2D, MyTexture::bindTexture("myimages/YellowNew.tga", 1));
            break;
        case Color::PURPLE:
            //glColor3f(0, 1, 0);
            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
            glBindTexture(GL_TEXTURE_2D, MyTexture::bindTexture("myimages/PurpleNew.tga", 1));
            break;
        case Color::DARKBLUE:
            //glColor3f(0, 1, 0);
            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
            glBindTexture(GL_TEXTURE_2D, MyTexture::bindTexture("myimages/BlueNew.tga", 1));
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
