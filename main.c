#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

float playerPositionX;
float playerPositionY;

// Flags for movement direction
int moveLeft = 0;
int moveRight = 0;
int moveUp = 0;
int moveDown = 0;

void drawPlayer() {
    glColor3f(1, 1, 0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(playerPositionX, playerPositionY);
    glEnd();
}

void updatePosition() {
    if (moveLeft) {
        playerPositionX -= 5;
    }
    if (moveRight) {
        playerPositionX += 5;
    }
    if (moveUp) {
        playerPositionY -= 5;
    }
    if (moveDown) {
        playerPositionY += 5;
    }

    glutPostRedisplay();
}

void buttons(unsigned char key, int x, int y) {
    switch(key) {
        case 'a':
            moveLeft = 1;
            break;
        case 'd':
            moveRight = 1;
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
            moveLeft = 0;
            break;
        case 'd':
            moveRight = 0;
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
    drawPlayer();
    glutSwapBuffers();
}

void init() {
    glClearColor(0.3, 0.3, 0.3, 0);
    gluOrtho2D(0, 1920, 1080, 0);
    playerPositionX = 300;
    playerPositionY = 300;
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("OpenGL Raycaster");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(buttons);
    glutKeyboardUpFunc(keyUp);  // Register the key up function
    glutIdleFunc(updatePosition);  // Register the idle function to continuously update the position
    glutMainLoop();
}
