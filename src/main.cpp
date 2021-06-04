#include <iostream>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "utils/PrintUtils.h"

int window;

float hour = 0.0;
float day = 0.0;
float inc = 1.00;

void resize(int width, int height)
{
    // prevent division by zero
    if (height == 0) { height=1; }

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)width/(float)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void keyPressed(unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
            glutDestroyWindow(window);
            exit(0);
            break;
    }
}

static void specialKeyPressed(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_UP:
            inc *= 1.5;
            break;
        case GLUT_KEY_DOWN:
            inc *= 0.75;
            break;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    hour += inc;
    day += inc/24.0;
    hour = hour - ((int)(hour/24))*24;
    day = day - ((int)(day/365))*365;

    glTranslatef (0.0, 0.0, -8.0);

    glRotatef(360*day/365.0, 0.0, 1.0, 0.0);

    // ecliptic
    glRotatef(15.0, 1.0, 0.0, 0.0);

    // sun
    glColor3f(1.0, 1.0, 0.0);
    glutWireSphere(1.0, 15, 15);

    // earth
    // position around the sun
    glRotatef(360.0*day/365.0, 0.0, 1.0, 0.0);
    glTranslatef(4.0, 0.0, 0.0);

    glPushMatrix();
    // rotate the earth on its axis
    glRotatef(360.0*hour/24.0, 0.0, 1.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glutWireSphere(0.4, 10, 10);
    glPopMatrix();

    // moon
    glRotatef(360.0*4*day/365.0, 0.0, 1.0, 0.0);
    glTranslatef(0.7f, 0.0f, 0.0f);
    glColor3f(0.3f, 0.7f, 0.3f);
    glutWireSphere(0.1f, 10, 10);

    glutSwapBuffers();
}

void init(int width, int height)
{
    print("Number ", 1, " and more...");
    print("Hey");
    print("Number ", 1);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    resize(width, height);
}

/**
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}*/


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    window = glutCreateWindow("Block Game");
    glutDisplayFunc(&display);
    glutIdleFunc(&display);
    glutReshapeFunc(&resize);
    glutKeyboardFunc(&keyPressed);
    glutSpecialFunc(&specialKeyPressed);
    init(640, 480);
    glutMainLoop();
    return 0;
}



