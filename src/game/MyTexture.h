
#ifndef BLOCK_GAME_MYTEXTURE_H
#define BLOCK_GAME_MYTEXTURE_H
#include <GL/glut.h>

class MyTexture {
public:
    static GLuint bindTexture(const char* filename,int number);

};
#endif //BLOCK_GAME_GENTEXTURE_H