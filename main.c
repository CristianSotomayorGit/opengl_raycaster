#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#define PI 3.1415

float playerPositionX;
float playerPositionY;
float playerDeltaX;
float playerDeltaY;
float playerAngle;

// Flags for movement direction
int rotateLeft = 0;
int rotateRight = 0;
int moveUp = 0;
int moveDown = 0;

void drawPlayer() {
    glColor3f(1, 1, 0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(playerPositionX, playerPositionY);
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(playerPositionX, playerPositionY);
    glVertex2i(playerPositionX + playerDeltaX * 5, playerPositionY + playerDeltaY * 5);
    glEnd();
}

int mapX = 20;
int mapY = 20;
int mapS = 64;

int map[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

void drawMap2D() {
    int x;
    int y;
    int xo;
    int yo;

    for (y = 0; y < mapY; y++) {
        for (x = 0; x < mapX; x++) {

            if (map[y * mapX + x] == 1) {
                glColor3f(1, 1, 1);
            }
            
            else {
                glColor3f(0, 0, 0);
            }

            xo = x * mapS;
            yo = y * mapS;

            glBegin(GL_QUADS);
            glVertex2i(xo + 2, yo + 2);
            glVertex2i(xo + 2, yo + mapS - 2);
            glVertex2i(xo + mapS - 2, yo + mapS - 2);
            glVertex2i(xo + mapS - 2, yo + 2);
            glEnd();
        }
    }
}

void updatePosition() {
    
    if (rotateLeft) {
        playerAngle -= 0.05;

        if (playerAngle < 0) {
            playerAngle += 2 * PI;
        }
    
        playerDeltaX = cos(playerAngle) * 2.5;
        playerDeltaY = sin(playerAngle) * 2.5;
    }

    if (rotateRight) {
        playerAngle += 0.05;

        if (playerAngle > 0) {
            playerAngle -= 2 * PI;
        }
    
        playerDeltaX = cos(playerAngle) * 2.5;
        playerDeltaY = sin(playerAngle) * 2.5;
    }

    if (moveUp) {
        playerPositionX += playerDeltaX;
        playerPositionY += playerDeltaY;
    }

    if (moveDown) {
        playerPositionX -= playerDeltaX;
        playerPositionY -= playerDeltaY;    }

    glutPostRedisplay();
}

void buttons(unsigned char key, int x, int y) {
    switch(key) {
        case 'a':
            rotateLeft = 1;
            break;
        case 'd':
            rotateRight = 1;
            break;
        case 'w':
            moveUp = 1;
            break;
        case 's':
            moveDown = 1;
            break;
    }
}

void keyUp(unsigned char key, int x, int y) {
    switch(key) {
        case 'a':
            rotateLeft = 0;
            break;
        case 'd':
            rotateRight = 0;
            break;
        case 'w':
            moveUp = 0;
            break;
        case 's':
            moveDown = 0;
            break;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawMap2D();
    drawPlayer();
    glutSwapBuffers();
}

void init() {
    glClearColor(0.3, 0.3, 0.3, 0);
    gluOrtho2D(0, 1280, 1280, 0);
    
    playerPositionX = 300;
    playerPositionY = 300;
    playerDeltaX = cos(playerAngle) * 2.5;
    playerDeltaY = sin(playerAngle) * 2.5;
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1280, 1280);
    glutCreateWindow("OpenGL Raycaster");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(buttons);
    glutKeyboardUpFunc(keyUp);  // Register the key up function
    glutIdleFunc(updatePosition);  // Register the idle function to continuously update the position
    glutMainLoop();
}
