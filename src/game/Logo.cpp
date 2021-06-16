#include "Logo.h"
#include <GL/glut.h>
#include <GL/gl.h>  
#include <GL/glu.h> 
#include <vector>

void Logo::quadLogo(GLuint texture) {
    auto points = std::vector<std::vector<float>>{
        {3, 1, 0},
        { 5,  1, 0 },
        { 5,  3,  0 },
        { 3, 3,  0 }
    };

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(points[0][0], points[0][1], points[0][2]);  // Left bottom  glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(points[1][0], points[1][1], points[1][2]);  // Right bottom glVertex3f(1.0f, -1.0f, 1.0f); 
    glTexCoord2f(1.0f, 1.0f); glVertex3f(points[2][0], points[2][1], points[2][2]);  // Right Top    glVertex3f(1.0f, 1.0f, 1.0f);  
    glTexCoord2f(0.0f, 1.0f); glVertex3f(points[3][0], points[3][1], points[3][2]);  // Left Top     glVertex3f(-1.0f, 1.0f, 1.0f); 
    glEnd();
    glDisable(GL_TEXTURE_2D);
}