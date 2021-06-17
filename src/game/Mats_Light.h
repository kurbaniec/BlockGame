#include <GL/glut.h>
#ifndef BLOCK_GAME_MATS_LIGHT_H
#define BLOCK_GAME_MATS_LIGHT_H



class Mats_Light {
public:
    static void setlight(int light);
    static void setmats(int mats);


    //static void sphereLogo();



};
enum Lights {
    AMBIENT = 0,
    DIFFUSE = 1,
    SPECULAR = 2,
    POSITION = 3,
}; 
enum Mats {
    AMBIENTMAT = 0,
    DIFFUSEMAT = 1,
    SPECULARMAT = 2,
    SHINMAT = 3,
};
#endif //MATS_LIGHT_H