#include<iostream>
#include<GL/glut.h>
using namespace std;

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480);
}

void boundaryFill(float x, float y, float* b, float* n) {
    float color[3];
    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, color);
    if ((color[0] != b[0] || color[1] != b[1] || color[2] != b[2]) && (color[0] != n[0] || color[1] != n[1] || color[2] != n[2])) {
        glColor3f(n[0], n[1], n[2]);
        glBegin(GL_POINTS);
        glVertex2d(x, y);
        glEnd();
        glFlush();
        if (x + 1 < 640)
            boundaryFill(x + 1, y, b, n);
        if (x - 1 >= 0)
            boundaryFill(x - 1, y, b, n);
        if (y + 1 < 480)
            boundaryFill(x, y + 1, b, n);
        if (y - 1 >= 0)
            boundaryFill(x, y - 1, b, n);
    }
}

void floodFill(float x, float y, float* b, float* n) {
    float color[3];
    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, color);
    if (color[0] == b[0] && color[1] == b[1] && color[2] == b[2]) {
        glColor3f(n[0], n[1], n[2]);
        glBegin(GL_POINTS);
        glVertex2d(x, y);
        glEnd();
        glFlush();
        if (x + 1 < 640)
            floodFill(x + 1, y, b, n);
        if (x - 1 >= 0)
            floodFill(x - 1, y, b, n);
        if (y + 1 < 480)
            floodFill(x, y + 1, b, n);
        if (y - 1 >= 0)
            floodFill(x, y - 1, b, n);
    }
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLineWidth(3);
    glPointSize(2);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2d(40, 440);
    glVertex2d(600, 440);
    glVertex2d(600, 40);
    glVertex2d(40, 40);
    glEnd();
    glFlush();
}

void mouse(int btn, int state, int x, int y) {
    y = 480 - y;
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float b[] = {0, 0, 0};
        float n[] = {1, 0, 0};
        boundaryFill(x, y, b, n);
    } else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        float b[3];
        glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, b);
        float n[] = {1, 0, 0};
        floodFill(x, y, b, n);
    }
}

int main(int argc, char** argv) {
    cout << "Left Mouse Button: Boundary Fill Right Mouse Button: Flood Fill" << endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Filling");
    myInit();
    glutMouseFunc(mouse);
    glutDisplayFunc(myDisplay);
    glutMainLoop();
    return 0;
}
