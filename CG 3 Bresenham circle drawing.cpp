#include <GL/glut.h>
#include <stdio.h>

int r, xc, yc, x, y;

void putPixel(int px, int py) {
    glBegin(GL_POINTS);
    glVertex2f((float)px, (float)py);
    glEnd();
}


void plotPoints(int px, int py) {
    putPixel(xc + px, yc + py);
    putPixel(xc + px, yc - py);
    putPixel(xc - px, yc + py);
    putPixel(xc - px, yc - py);
    putPixel(xc + py, yc + px);
    putPixel(xc + py, yc - px);
    putPixel(xc - py, yc + px);
    putPixel(xc - py, yc - px);
}

void drawCircle() {
    glBegin(GL_LINES);
    glVertex2f(-640.0F, 0);
    glVertex2f(640.0F, 0);
    glVertex2f(0, -480.0F);
    glVertex2f(0, 480.0F);
    glEnd();

    int p = 1.25F * r - r;
    x = 0, y = r;
    while (x < y) {
        plotPoints(x, y);
        p += (x++ << 2) + 6;
        if (p >= 0)
            p += (1 - y--) << 2;
    }

    glFlush();
}

void init() {
    glColor3f(1.0F, 1.0F, 1.0F);
	glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
    glClear(GL_COLOR_BUFFER_BIT);
    glOrtho(-640.0, 640.0, -480.0, 480.0, -1.0, 1.0);
}

int main(int argc, char **argv) {
    printf("Enter radius: ");
    scanf("%d", &r);
    printf("Enter X coordinate of center: ");
    scanf("%d", &xc);
    printf("Enter Y coordinate of center: ");
    scanf("%d", &yc);
    r *= 16;
    xc *= 16;
    yc *= 16;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(400, 150);
    glutCreateWindow("Bresenham's Circle Drawing Algorithm");
    init();
    glutDisplayFunc(drawCircle);
    glutMainLoop();

    return 0;
}

