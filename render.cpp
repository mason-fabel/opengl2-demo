#include <GL/glut.h>
#include <cstdarg>
#include <cstdio>
#include "func.h"
#include "render.h"

const int SUBDIVISIONS = 150;
const float X_MIN = -3.14;
const float X_MAX = 3 * 3.14;
const float Y_MIN = -3.0;
const float Y_MAX = 3.0;
const float INTERVAL = (X_MAX - X_MIN) / SUBDIVISIONS;
const float TEXT_SCALING = 400.0;

float width;
float height;

void render_callback(void);
void resize_callback(int w, int h);
void print3D(float x, float y, char* format, ...);

void init(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(200, 200);

    glutCreateWindow("CS324 HW5 - fabe0940");

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glShadeModel(GL_FLAT);

    glutDisplayFunc(render_callback);
    glutReshapeFunc(resize_callback);

	return;
}

void render(void) {
    glutMainLoop();

	return;
}

void resize_callback(int w, int h) {
	if (!h) return;

	width = w;
	height = h;

	glutPostRedisplay();
}

void render_callback(void) {
	int i;
	float x;
	float y;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0.0, 0.0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, width / height, 1, 10);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		X_MIN + ((X_MAX - X_MIN) / 2), Y_MIN + ((Y_MAX - Y_MIN) / 2), 5.0,
		X_MIN + ((X_MAX - X_MIN) / 2), Y_MIN + ((Y_MAX - Y_MIN) / 2), 0.0,
		0.0, 1.0, 0.0
	);

    glPushMatrix();

    glColor3f(1.0, 1.0, 1.0);
	print3D(X_MIN, Y_MAX - 0.0, "Mason Fabel");
	print3D(X_MIN, Y_MAX - 0.5, "CS324");
	print3D(X_MIN, Y_MAX - 1.0, "Assignment 5");

    glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_LINES);
	glVertex3f(X_MIN, 0.0, 0.0);
	glVertex3f(X_MAX, 0.0, 0.0);
	glVertex3f(0.0, Y_MIN, 0.0);
	glVertex3f(0.0, Y_MAX, 0.0);
	glEnd();

    glColor3f(1.0, 1.0, 1.0);
	print3D(X_MIN, 0.0, (char*) "-x");
	print3D(X_MAX, 0.0, (char*) "+x");
	print3D(0.0, Y_MIN, (char*) "-y");
	print3D(0.0, Y_MAX, (char*) "+y");

    glColor3f(1.0, 1.0, 1.0);
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

void print3D(float x, float y, char* format, ...) {
	va_list args;
	char buffer[128];
	char* p;

	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	glPushMatrix();

	glTranslatef(x, y, 0.0);
	glScalef(1.0 / TEXT_SCALING, 1.0 / TEXT_SCALING, 1.0 / TEXT_SCALING);
	for (p = buffer; *p; p++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
	}

	glPopMatrix();

	return;
}
