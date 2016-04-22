#include <GL/glut.h>
#include <cstdarg>
#include <cstdio>
#include "func.h"
#include "render.h"

const int SUBDIVISIONS = 200;
const float X_MIN = -3.14;
const float X_MAX = 3 * 3.14;
const float Y_MIN = -5.0;
const float Y_MAX = 5.0;
const float INTERVAL = (X_MAX - X_MIN) / SUBDIVISIONS;

void render_callback(void);
void print3D(float x, float y, char* format, ...);

void init(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("CS324 HW5 - fabe0940");

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glShadeModel(GL_FLAT);

    glutDisplayFunc(render_callback);

	return;
}

void render(void) {
    glutMainLoop();

	return;
}

void print3D(float x, float y, char* format, ...) {
	va_list args;
	char buffer[128];
	char* p;

	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	glPushMatrix();

	glTranslatef(x, y, 0.0);
	for (p = buffer; *p; p++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
	}

	glPopMatrix();

	return;
}

void render_callback(void) {
	int i;
	float x;
	float y;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();

	glBegin(GL_LINES);
	glVertex3f(X_MIN, 0.0, 0.0);
	glVertex3f(X_MAX, 0.0, 0.0);
	glVertex3f(0.0, Y_MIN, 0.0);
	glVertex3f(0.0, Y_MAX, 0.0);
	glEnd();

	print3D(X_MIN, 0.0, (char*) "-x");
	print3D(X_MAX, 0.0, (char*) "+x");
	print3D(0.0, Y_MIN, (char*) "-y");
	print3D(0.0, Y_MAX, (char*) "+y");

	glBegin(GL_POINTS);
	for (i = 0; i < SUBDIVISIONS; i++) {
		x = X_MIN + (INTERVAL * i);
		y = func(x);
		glVertex3f(x, y, 0.0);
	}
	glEnd();

    glPopMatrix();

    glutSwapBuffers();

    glutPostRedisplay();

	return;
}
