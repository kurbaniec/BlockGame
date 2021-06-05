#include <iostream>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "utils/PrintUtils.h"
#include "game/Board.h"
#include "game/Config.h"
#include "game/Block.h"
#include <vector>

int window;

float hour = 0.0;
float day = 0.0;
float inc = 1.00;
// Used for delta time
int old_t;
float time_spent;

void resize(int width, int height) {
    // prevent division by zero
    if (height == 0) { height = 1; }

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Setup orthographic camera
    // See: https://gamedev.stackexchange.com/a/49698
    //gluPerspective(45.0f, (float) width / (float) height, 0.1f, 100.0f);
    //gluOrtho2D(0, width, height, 0);
    //glOrtho(0, width, height, 0, 0.1f, 100.0f);
    float aspect = float(width) / float(height);
    float visible = Config::cameraVisibleRange();
    glOrtho(-visible * aspect, visible * aspect, -visible, visible, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void keyPressed(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            glutDestroyWindow(window);
            //exit(0);
            break;
    }
}

static void specialKeyPressed(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            inc *= 1.5;
            break;
        case GLUT_KEY_DOWN:
            inc *= 0.75;
            break;
    }
}

float getDeltaTime() {
    // Get delta time
    // See: https://stackoverflow.com/a/36100951/12347616
    auto t = glutGet(GLUT_ELAPSED_TIME);
    auto dt = float(t - old_t) / float(1000.0);
    old_t = t;
    return dt;
}

void display() {
    auto dt = getDeltaTime();
    time_spent += dt;
    // print(dt);

    // print("Board: ", Board::get().getRows() , "X", Board::get().getCols());

    // Some small testing
    // See: https://stackoverflow.com/a/17663236/12347616
    // std::vector<std::vector<int>> test {{3, 1}, {1, 2}};
    // print(test[0][0]);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Push backgroundPoints away from camera
    glTranslatef(0.0, 0.0, -10.1);

    // Background with a 1:2 ratio
    auto bg = Config::backgroundPoints();
    glColor3f(1, 1, 1); // White
    glBegin(GL_QUADS);
    glVertex3f(bg[0][0], bg[0][1], bg[0][2]);  // Left bottom
    glVertex3f(bg[1][0], bg[1][1], bg[1][2]);  // Right bottom
    glVertex3f(bg[2][0], bg[2][1], bg[2][2]);  // Right Top
    glVertex3f(bg[3][0], bg[3][1], bg[3][2]);  // Left Top
    glEnd();

    // Blocks should be positioned in front of the backgroundPoints
    glTranslatef(0.0, 0.0, 0.1);

    // Move Block down
    if (time_spent > Config::speed()) {



        time_spent = 0;
    }

    Block::get().draw();

    /*
    // Block items
    glColor3f(0, 0, 0); // Black
    glBegin(GL_QUADS);
    glVertex3f(-2, -3, 0);
    glVertex3f(-1, -3, 0);
    glVertex3f(-1, -2, 0);
    glVertex3f(-2, -2, 0);
    glEnd();*/

    /**
    hour += inc;
    day += inc / 24.0;
    hour = hour - ((int) (hour / 24)) * 24;
    day = day - ((int) (day / 365)) * 365;

    glTranslatef(0.0, 0.0, -8.0);

    glRotatef(360 * day / 365.0, 0.0, 1.0, 0.0);

    // ecliptic
    glRotatef(15.0, 1.0, 0.0, 0.0);

    // sun
    glColor3f(1.0, 1.0, 0.0);
    glutWireSphere(1.0, 15, 15);

    // earth
    // position around the sun
    glRotatef(360.0 * day / 365.0, 0.0, 1.0, 0.0);
    glTranslatef(4.0, 0.0, 0.0);

    glPushMatrix();
    // rotate the earth on its axis
    glRotatef(360.0 * hour / 24.0, 0.0, 1.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glutWireSphere(0.4, 10, 10);
    glPopMatrix();

    // moon
    glRotatef(360.0 * 4 * day / 365.0, 0.0, 1.0, 0.0);
    glTranslatef(0.7f, 0.0f, 0.0f);
    glColor3f(0.3f, 0.7f, 0.3f);
    glutWireSphere(0.1f, 10, 10);*/

    glutSwapBuffers();
}

void init(int width, int height) {
    // Setup game logic
    Board::get().setup(20, 10);
    print("Board: ", Board::get().getRows(), "X", Board::get().getCols());
    // Print game board
    print2dVec(Board::get().getBoard());
    // Setup delta time
    old_t = glutGet(GLUT_ELAPSED_TIME);
    time_spent = 0;
    // OpenGL configuration
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    resize(width, height);
}


int main(int argc, char **argv) {
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



