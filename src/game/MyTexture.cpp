#include <GL/glut.h>
#include "MyTexture.h"
#include <iostream>
#include "../utils/tga.h"

GLuint MyTexture::bindOne(const char* filename)
{
    GLsizei w, h;
    GLuint texture;
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
    return texture;

}
