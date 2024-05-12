#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

float playerPositionX;
float playerPositionY;

void drawPlayer() {
    glColor3f(1, 1, 0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(playerPositionX, playerPositionY);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawPlayer();
    glutSwapBuffers();
}

void init() {
    glClearColor(0.3, 0.3, 0.3, 0); //Background color
    gluOrtho2D(0,1920,1080,0); //Window size
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
    glutMainLoop();
}