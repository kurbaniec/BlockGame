#include <iostream>

#include <GL/glut.h>
#include <GL/gl.h>  
#include <GL/glu.h> 
#include <GL/freeglut.h>
#include "utils/PrintUtils.h"
#include "game/Board.h"
#include "game/Config.h"
#include "game/Block.h"
#include "game/State.h"

#include "game/MyTexture.h"
#include "game/Logo.h"
#include <GL/freeglut_ext.h>
#include <string>
#include <irrKlang.h>
// See: https://www.gamedev.net/forums/topic/392837-spacebar-key/392837/
#define GLUT_KEY_SPACEBAR 32
#define GLUT_KEY_P 112
#define GLUT_KEY_ESCAPE 27
#define GLUT_KEY_a 97
//irrKlang Libary for Audio
irrklang::ISoundEngine* SoundEngine = irrklang::createIrrKlangDevice();
irrklang::ISound* sound;

int window;
// Variables to attach the Textures
GLuint frontFace;
GLuint backFace;
GLuint backGroundTex;
GLuint gameOverTex;

float rotation_x, rotation_y, rotation_z;
bool animating = true;
// Game state
int state;
// Used for delta time
int old_t;
float time_spent;
//used for Gamescore calculation
int internScore = 0;



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
                animating = false;
                SoundEngine->setAllSoundsPaused();//pause soundtrack
                print("Paused");
            } else {
                state = PLAY;
                animating = true;
                SoundEngine->setAllSoundsPaused(false);//unpause soundtrack
                print("Continue");
            }
            break;
        case GLUT_KEY_a:
            if (state == PLAY) {
                if (animating) {
                    animating = false; //pause Logo animation
                }
                else {
                    animating = true; // continue Logo animation
                }
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
                    internScore = 0;
                   
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
void renderStrokeFontString(float x,float y,float z,void* font,char* string) {

    char* c;
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(1 / 250.38, 1 / 250.38, 1 / 250.38); //downscale text

    for (c = string; *c != '\0'; c++) {
        glutStrokeCharacter(font, *c);
    }

    glPopMatrix();
}

/*
* This Method is called when the User loses the Game (State is "GameOver")
*/
void gameoverDisplay() {

    
    glPushMatrix();

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    // Binding the Game Over Texture
    glBindTexture(GL_TEXTURE_2D, gameOverTex);

    glTranslatef(0, 0, 4);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, -2.0f, 2.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(2.0f, -2.0f, 2.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(2.0f, 2.0f, 2.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f, 2.0f, 2.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
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

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    // Binding the Background Texture
    glBindTexture(GL_TEXTURE_2D, backGroundTex);
    
    // glTexCoord2f is needed so that the Texture is visible
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

                
            }
        }

        // Clear full game block lines
        int counter = internScore;
        internScore += Board::get().lineClear();
        if (internScore > counter) {
            SoundEngine->play2D("audio/clear.wav"); //play sound when a line is cleared through increasing gamescore
        }
    }

    

    // Draw active game block and board
    Block::get().draw();
    Board::get().draw();

    // State -> Gamerover -> Show Gameover Texture
    if (state == State::GAMEOVER) {
        gameoverDisplay();
    }

    //Score
    //https://flex.phys.tohoku.ac.jp/texi/glut/glutStrokeCharacter.3xglut.html
    glColor3f(1, 0, 0);
    void* font = GLUT_STROKE_MONO_ROMAN;
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(5.0);
    renderStrokeFontString(2.7, -0.2, 0, font, (char*)"Score");
    std::string tmp = std::to_string(internScore);
    char const* num_char = tmp.c_str();
    glColor3f(0.8, 0, 0);
    renderStrokeFontString(3.5, -1, 0, font, (char*)num_char);

    //GameLogo Animation
    glTranslatef(3.8, 2.0, 0.2);
    glRotatef(rotation_x, 1, 0, 0); 
    glRotatef(rotation_y, 0, 1, 0);
    glRotatef(rotation_z, 0, 0, 1);
    Logo::quadLogo(frontFace, backFace);
    glDisable(GL_LIGHTING);
    if (animating) {
        rotation_y += 15 * dt;
    }
    glColor3f(0, 0, 0);
   
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

    //init Logo, BackgroundTexture and the Gameover Texture
    frontFace = MyTexture::bindTexture("myimages/Block_1_.tga", 1);
    backFace = MyTexture::bindTexture("myimages/Game_1_.tga", 1);
    backGroundTex = MyTexture::bindTexture("myimages/BackgroundTextureGrey.tga", 1);
    gameOverTex = MyTexture::bindTexture("myimages/gameoverwhite.tga", 1);

    sound = SoundEngine->play2D("audio/Theme1.mp3", true);
    rotation_x = rotation_y = rotation_z = 0.0;
   
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



