#include <GL/glut.h>
#include "Mats_Light.h"


void Mats_Light::setlight(int light) {
    //here you set the lights and parameters, example with one light
    float LightAmbient[] = { 0.1f, 0.1f, 0.05f, 1.0f };
    float LightDiffuse[] = { 1.0f, 1.0f, 0.8f, 1.0f };
    float LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float LightDirection[] = { -0.5f, -0.5f, -0.5f };
    switch (light) {
    case Lights::AMBIENT:
        
        glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
        break;
    case Lights::DIFFUSE:
        
        glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
        break;
    case Lights::SPECULAR:
        
        glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
        break;
    case Lights::POSITION:
        
        glLightfv(GL_LIGHT0, GL_POSITION, LightDirection);
        break;
    }
    
    //float LightEmission[] = { 1.0f, 1.0f, 0.8f, 1.0f };
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}
void Mats_Light::setmats(int mats) {
    //here you set materials, you must declare each one of the colors global or locally like this:
    float MatAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    float MatDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float MatSpecular[] = { 0.1f, 0.1f, 0.0f, 0.1f };
    float MatShininess = 60;
    switch (mats) {
    case Mats::AMBIENTMAT:
        
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MatAmbient);
        break;
    case Mats::DIFFUSEMAT:
        
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MatDiffuse);
        break;
    case Mats::SPECULARMAT:
        
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpecular);
        break;
    case Mats::SHINMAT:
        
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess);
        break;
    }
    
    //float black[] = { 0.0f,0.0f,0.0f,1.0f };
    //glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
}