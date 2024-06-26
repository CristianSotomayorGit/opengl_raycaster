#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#define PI 3.1415
#define PI2 PI / 2
#define PI3 3 * PI / 2
// #define DR 0.0174533
// #define DR 0.00872665
#define DR 0.0043633

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
    
        playerDeltaX = cos(playerAngle) * 5;
        playerDeltaY = sin(playerAngle) * 5;
    }

    if (rotateRight) {
        playerAngle += 0.05;

        if (playerAngle > 2 * PI) {
            playerAngle -= 2 * PI;
        }
    
        playerDeltaX = cos(playerAngle) * 5;
        playerDeltaY = sin(playerAngle) * 5;
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

float dist(float ax, float ay, float bx, float by, float ang) {
    return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay))); //pythagorean theorem
}

void drawRays2D() {
    int r;
    int mx;
    int my;
    int mp;
    int dof;

    float rx;
    float ry;
    float ra;
    float xo;
    float yo;
    float distT;

    ra = playerAngle - DR * 120;

    if (ra < 0) {
        ra += 2 * PI; 
    }

    if (ra > 2 * PI) {
        ra -= 2 * PI;
    }

    for (r = 0; r < 240; r++) {
        
        dof = 0;

        float disH = 1000000;
        float hx = playerPositionX;
        float hy = playerPositionY;
        float aTan = -1/tan(ra);

        if (ra > PI) {
            ry = (((int)playerPositionY >> 6) <<6) - 0.0001;
            rx = (playerPositionY - ry) * aTan + playerPositionX;
            yo = -64;
            xo = -yo * aTan;
        }

        if (ra < PI) {
            ry = (((int)playerPositionY >> 6) <<6) + 64;
            rx = (playerPositionY - ry) * aTan + playerPositionX;
            yo = 64;
            xo = -yo * aTan;
        }

        if (ra == 0 || ra == PI) {
            rx = playerPositionX;
            ry = playerPositionY;
            dof = 20;
        }

        while (dof < 20) {
            mx = (int)(rx) >> 6;
            my = (int)(ry) >> 6;
            mp = my * mapX + mx;

            if (mp > 0 && mp < mapX * mapY && map[mp] == 1) {
                hx = rx;
                hy = ry;
                disH = dist(playerPositionX, playerPositionY, hx, hy, ra);
                dof = 20;
            }

            else {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }

        dof = 0;

        float disV = 1000000;
        float vx = playerPositionX;
        float vy = playerPositionY;
        float nTan= -tan(ra);
        
        if (ra > PI2 && ra < PI3) {
            rx = (((int)playerPositionX >>6) <<6) - 0.0001;
            ry = (playerPositionX - rx) * nTan + playerPositionY;
            xo = -64;
            yo = -xo * nTan;
        }

        if (ra < PI2 || ra > PI3) {
            rx = (((int)playerPositionX >>6) <<6) + 64;
            ry = (playerPositionX - rx) * nTan + playerPositionY;
            xo = 64;
            yo = -xo * nTan;
        }
        
        if (ra == 0 || ra == PI) {
            rx = playerPositionX;
            ry = playerPositionY;
            dof = 20;
        }
        
        while (dof < 20) {
            mx = (int)(rx) >> 6;
            my = (int)(ry) >> 6;
            mp = my * mapX + mx;

            if (mp > 0 && mp < mapX * mapY && map[mp] == 1) {
                vx = rx;
                vy = ry;
                disV = dist(playerPositionX, playerPositionY, vx, vy, ra);
                dof = 20;
            }
            else {
                rx += xo;
                ry += yo;
                dof += 1;
            } 
        }

        if (disV < disH) {
            rx = vx;
            ry = vy;
            distT = disV;
            glColor3f(1, 0, 0);
        }

        if (disH < disV) {
            rx = hx;
            ry = hy;
            distT = disH;
            glColor3f(0.5, 0, 0);
        }
        
        glLineWidth(1);
        glBegin(GL_LINES);
        glVertex2i(playerPositionX, playerPositionY);
        glVertex2i(rx,ry);
        glEnd();


        //Draw 3D Walls
        //Fix fisheye distortion
        float ca = playerAngle - ra;
        
        if (ca < 0) {
            ca += 2 * PI; 
        }

        if (ca > 2 * PI) {
            ca -= 2 * PI;
        }

        distT = distT * cos(ca);
        float lineH = (mapS * 1280) / distT;
        float lineO = 640 - lineH / 2;

        // if (lineH > 1280) {
        //     lineH = 1280;
        // }

        glLineWidth(6);
        glBegin(GL_LINES);
        glVertex2i(r * 5.333 + 1280, lineO);
        glVertex2i(r * 5.333 + 1280, lineH + lineO);
        glEnd();

        ra += DR;

        if (ra < 0) {
            ra += 2 * PI; 
        }

        if (ra > 2 * PI) {
            ra -= 2 * PI;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawMap2D();
    drawRays2D();
    drawPlayer();
    glutSwapBuffers();
}

void init() {
    glClearColor(0.3, 0.3, 0.3, 0);
    gluOrtho2D(0, 2560, 1280, 0);
    
    playerAngle = 1;
    playerPositionX = 300;
    playerPositionY = 300;
    playerDeltaX = cos(playerAngle) * 5;
    playerDeltaY = sin(playerAngle) * 5;
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(2560, 1280);
    glutCreateWindow("OpenGL Raycaster");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(buttons);
    glutKeyboardUpFunc(keyUp);  // Register the key up function
    glutIdleFunc(updatePosition);  // Register the idle function to continuously update the position
    glutMainLoop();
}
