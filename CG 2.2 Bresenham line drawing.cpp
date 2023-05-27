#include <GL/glut.h>
#include <iostream>
#include <math.h>
using namespace std;

int ch = 0;

void display(int x, int y){
    glColor3f(0,0,0);
    glPointSize(2);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void displaydotted(int x, int y){
    glColor3f(0,0,0);
    glPointSize(2);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void displaydashed(int x, int y){
    glColor3f(0,0,0);
    glPointSize(3);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void displaysolid(int x, int y){
    glColor3f(0,0,0);
    glPointSize(6);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void Bresenham_Line(int x1, int y1, int x2, int y2){
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int x = x1;
    int y = y1;
    int incrX = (x2 >= x1) ? 1 : -1;
    int incrY = (y2 >= y1) ? 1 : -1;

    int interchange = 0;
    if (dy > dx) {
        int temp = dx;
        dx = dy;
        dy = temp;
        interchange = 1;
    }

    int decision = 2 * dy - dx;

    for (int i = 0; i <= dx; i++) {
        switch (ch)
        {
            case 1:
                display(x, y);
                break;
            case 2:
                if (i % 6 == 0) {
                    displaydotted(x, y);
                }
                break;
            case 3:
                if (i % 8 > 4) {
                    displaydashed(x, y);
                }
                break;
            case 4:
                displaysolid(x, y);
                break;
            default:
                break;
        }

        while (decision >= 0) {
            if (interchange)
                x += incrX;
            else
                y += incrY;

            decision -= 2 * dx;
        }

        if (interchange)
            y += incrY;
        else
            x += incrX;

        decision += 2 * dy;
    }
    glFlush();
}

void mouse(int button, int state, int x, int y){
    static int x1, y1, pt = 0;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (pt == 0)
        {
            x1 = x;
            y1 = y;
            pt = pt + 1;
        }
        else
        {
            int x2 = x;
            int y2 = y;
            Bresenham_Line(x1, y1, x2, y2);
            x1 = x2;
            y1 = y2;
        }
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        pt = 0;
    }
    glFlush();
}

void keyboard(unsigned char key, int x, int y){
    switch (key)
    {
        case 's':
            ch = 1;
            cout << "Simple Line is opted" << endl;
            glutMouseFunc(mouse);
            break;
        case 'd':
            ch = 2;
            cout << "Dotted Line is opted" << endl;
            glutMouseFunc(mouse);
            break;
        case 'D':
            ch = 3;
            cout << "Dashed Line is opted" << endl;
            glutMouseFunc(mouse);
            break;
        case 'S':
            ch = 4;
            cout << "Solid Line is opted" << endl;
            glutMouseFunc(mouse);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void initialize(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0, 600, 600, 0);
}

void initialaxis(){
    glColor3f(0,0,0);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2i(300, 0);
    glVertex2i(300, 600);
    glVertex2i(0, 300);
    glVertex2i(600, 300);
    glEnd();
    glFlush();
    glutKeyboardFunc(keyboard);
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(800, 100);
    glutCreateWindow("Bresenham's Line Algorithm");
    initialize();
    cout << "Choose your Line type: " << endl;
    cout << "--------------------------------------------" << endl;
    cout << "s => Simple Line" << endl;
    cout << "d => Dotted Line" << endl;
    cout << "D => Dashed Line" << endl;
    cout << "S => Solid Line" << endl;
    cout << "--------------------------------------------" << endl;
    glutDisplayFunc(initialaxis);
    glutMainLoop();
    return 0;
}

