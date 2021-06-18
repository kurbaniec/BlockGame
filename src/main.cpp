#include <iostream>

#include <GL/glut.h>
#include "utils/PrintUtils.h"
#include "game/Board.h"
#include "game/Config.h"
#include "game/Block.h"
#include "game/State.h"
#include "game/DrawColor.h"

// See: https://www.gamedev.net/forums/topic/392837-spacebar-key/392837/
#define GLUT_KEY_SPACEBAR 32
#define GLUT_KEY_P 112
#define GLUT_KEY_ESCAPE 27

int window;

// Game state
int state;
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
    // Events that apply to all game states
    switch (key) {
        case GLUT_KEY_ESCAPE:
            glutDestroyWindow(window);
            break;
        case GLUT_KEY_P:
            if (state == PLAY) {
                state = PAUSE;
                print("Paused");
            } else {
                state = PLAY;
                print("Continue");
            }
            break;
    }
    // Events that apply to only certain states
    switch (state) {
        case PLAY:
            switch (key) {
                case GLUT_KEY_SPACEBAR:
                    Block::get().rotate();
                    break;
            }
            break;
        case GAMEOVER:
            switch (key) {
                case GLUT_KEY_SPACEBAR:
                    // Restart game
                    Board::get().reset();
                    Block::get().reset();
                    state = PLAY;
                    break;
            }
            break;
    }
}

static void specialKeyPressed(int key, int x, int y) {
    if (state != State::PLAY) return;
    switch (key) {
        case GLUT_KEY_DOWN:
            // Block::get().moveDown();
            Block::get().drop();
            break;
        case GLUT_KEY_LEFT:
            Block::get().moveLeft();
            break;
        case GLUT_KEY_RIGHT:
            Block::get().moveRight();
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

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Push backgroundPoints away from camera
    glTranslatef(0.0, 0.0, -10.1);

    // Background with a 1:2 ratio
    auto bg = Config::backgroundPoints();
    //glColor3f(1, 1, 1); // White

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, DrawColor::loadText("BackgroundTextureGrey.tga"));
    
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(bg[0][0], bg[0][1], bg[0][2]);  // Left bottom
    glTexCoord2f(1.0f, 0.0f); glVertex3f(bg[1][0], bg[1][1], bg[1][2]);  // Right bottom
    glTexCoord2f(1.0f, 1.0f); glVertex3f(bg[2][0], bg[2][1], bg[2][2]);  // Right Top
    glTexCoord2f(0.0f, 1.0f); glVertex3f(bg[3][0], bg[3][1], bg[3][2]);  // Left Top
    glEnd();
    glDisable(GL_TEXTURE_2D);



    // Blocks should be positioned in front of the backgroundPoints
    glTranslatef(0.0, 0.0, 0.1);

    if (state == State::PLAY) {
        // Move Block down
        if (time_spent > Config::speed()) {
            Block::get().moveDown();
            time_spent = 0;
        }

        if (Block::get().bottom()) {
            Block::get().saveToBoard();
            Block::get().reset();
            // Print board
            print2dVec(Board::get().getBoard());
            // Check if game is over
            if (Block::get().end()) {
                state = GAMEOVER;
                print("Game Over");
                // TEXTURE GAME OVER

                glEnable(GL_TEXTURE_2D);
                glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
                glBindTexture(GL_TEXTURE_2D, DrawColor::loadText("gameover.tga"));

                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(bg[0][0], bg[0][1], bg[0][2]);  // Left bottom
                glTexCoord2f(1.0f, 0.0f); glVertex3f(bg[1][0], bg[1][1], bg[1][2]);  // Right bottom
                glTexCoord2f(1.0f, 1.0f); glVertex3f(bg[2][0], bg[2][1], bg[2][2]);  // Right Top
                glTexCoord2f(0.0f, 1.0f); glVertex3f(bg[3][0], bg[3][1], bg[3][2]);  // Left Top
                glEnd();
                glDisable(GL_TEXTURE_2D);

            }
        }

        // Clear full game block lines
        Board::get().lineClear();
    }

    // Draw active game block and board
    Block::get().draw();
    Board::get().draw();

    // Swap Buffers
    glutSwapBuffers();
}

void init(int width, int height) {
    // Setup game logic
    state = State::PLAY;
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
    // Do not fire continuously key event
    // See: https://stackoverflow.com/a/39562334/12347616
    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
    glutSpecialFunc(&specialKeyPressed);
    // glutKeyboardUpFunc(<some_func>);
    init(640, 480);
    glutMainLoop();
    return 0;
}



