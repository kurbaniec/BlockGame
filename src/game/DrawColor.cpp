//
// Created by kurbaniec on 06.06.2021.
//

#include <GL/glut.h>
#include <GL/gl.h>  
#include <GL/glu.h> 
#include "DrawColor.h"
#include <random>
#include "../utils/tga.h"

std::random_device DrawColor::random_device;
std::mt19937 DrawColor::engine(DrawColor::random_device());
/*
unsigned int width, height;
unsigned char* data = loadBMPRaw("C:\\Users\\jb\\Desktop\\CGE_Projekt\\BlockGame\\src\\test.bmp", width, height);
// Create one OpenGL texture
GLuint textureID;
*/

GLuint texture;

void DrawColor::loadText(const char *filename) {
    GLsizei w, h;
    tgaInfo* info = 0;
    int mode;
    
    info = tgaLoad(filename);

    mode = info->pixelDepth / 8;  // will be 3 for rgb, 4 for rgba
    glGenTextures(1, &texture);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    // Upload the texture bitmap. 
    w = info->width;
    h = info->height;

    GLint format = (mode == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format,
        GL_UNSIGNED_BYTE, info->imageData);

    tgaDestroy(info);
}

void DrawColor::setColor(int color) {
    
    switch (color) {
        case Color::RED:
            //glColor3f(1, 0, 0);
            loadText("tile_red.tga");
            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
            glBindTexture(GL_TEXTURE_2D, texture);

            break;
        case Color::BLUE:
            //glColor3f(0, 0, 1);
            loadText("tile_blue.tga");           
            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
            glBindTexture(GL_TEXTURE_2D, texture);

            break;
        case Color::GREEN:
            //glColor3f(0, 1, 0);
            loadText("tile_green.tga");
            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
            glBindTexture(GL_TEXTURE_2D, texture);

            break;
        case Color::TEXTURE:
            /*
            glGenTextures(1, &textureID);
            // "Bind" the newly created texture : all future texture functions will modify this texture
            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 40, 40, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            */
            loadText("tile_orange.tga");
            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
            glBindTexture(GL_TEXTURE_2D, texture);

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
