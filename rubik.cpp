#include <GL/glut.h>
#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <unistd.h>

const float TEXT_SCALING = 400.0;
int WIREFRAME = 0;
float WIDTH = 800;
float HEIGHT = 600;
float GAP = 0.1;

void init(int argc, char** argv);
void print3D(float x, float y, float z, char* format, ...);
void render(void);
void render_callback(void);
void resize_callback(int w, int h);
void drawRubik(float x, float y, float z, float dim, float off);
void drawFace(float dim, float off);
void drawSquare(float dim);

int main(int argc, char** argv) {
	init(argc, argv);

	render();

	exit(0);
}

void drawRubik(float x, float y, float z, float dim, float off) {
	glTranslatef(x, y, z);

	glPushMatrix();
	glRotatef(180.0, 0.0, 1.0, 0.0);
	glColor3f(1.0, 0.5, 0.0);
	drawFace(dim, off);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	drawFace(dim, off);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	drawFace(dim, off);
	glPopMatrix();

	glPushMatrix();
	glRotatef(270.0, 0.0, 1.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	drawFace(dim, off);
	glPopMatrix();

	glPushMatrix();
	glRotatef(270.0, 1.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	drawFace(dim, off);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	drawFace(dim, off);
	glPopMatrix();

	return;
}

void drawFace(float dim, float off) {
	int i;
	int j;


	for (i = -1; i <= 1; i++) {
		for (j = -1; j <= 1; j++) {
			glPushMatrix();
			glTranslatef(i * (dim + off), j * (dim + off), 1.5 * dim + 2.0 * off);
			drawSquare(dim);
			glPopMatrix();
		}
	}


	return;
}

void drawSquare(float dim) {
	if (WIREFRAME) {
		glBegin(GL_LINE_LOOP);
	} else {
		glBegin(GL_QUADS);
	}
	glVertex3f(-0.5 * dim, -0.5 * dim, 0.0);
	glVertex3f( 0.5 * dim, -0.5 * dim, 0.0);
	glVertex3f( 0.5 * dim,  0.5 * dim, 0.0);
	glVertex3f(-0.5 * dim,  0.5 * dim, 0.0);
	glEnd();

	return;
}

void init(int argc, char** argv) {
	char c;
	int i;
	float f;

    glutInit(&argc, argv);

	while ((c = getopt(argc, argv, "?h:w:g:o")) != -1) {
		switch (c) {
			case 'h':
				i = atoi(optarg);
				if (i > 0) {
					HEIGHT = atoi(optarg);
				} else {
					fprintf(stderr, "invalid height: %i\n", i);
					exit(1);
				}
				break;
			case 'w':
				i = atoi(optarg);
				if (i > 0) {
					WIDTH = atoi(optarg);
				} else {
					fprintf(stderr, "invalid width: %i\n", i);
					exit(1);
				}
				break;
			case 'g':
				f = strtof(optarg, NULL);
				if (f >= 0.0) {
					GAP = f;
				} else {
					fprintf(stderr, "invalid gap: %f\n", f);
					exit(1);
				}
				break;
			case 'o':
				WIREFRAME = 1;
				break;
			case '?':
				fprintf(stdout, "Usage: %s [-w WIDTH] [-h HEIGHT]", argv[0]);
				fprintf(stdout, " [-g GAP] [-o]\n");
				fprintf(stdout, "\n");
				fprintf(stdout, "  -w WIDTH  set window width to WIDTH\n");
				fprintf(stdout, "  -h HEIGHT set window height to HEIGHT\n");
				fprintf(stdout, "  -g GAP    set gap to GAP\n");
				fprintf(stdout, "  -o        enable outline mode\n");
				fprintf(stdout, "  -?        display help and exit\n");
				exit(0);
				break;
		}
	}

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(WIDTH, HEIGHT);
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

	WIDTH = w;
	HEIGHT = h;

	glutPostRedisplay();
}

void render_callback(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0.0, 0.0, WIDTH, HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, WIDTH / HEIGHT, 1, 20);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		0.0, 0.0, 5.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0
	);

    glColor3f(1.0, 1.0, 1.0);
	print3D(-5.0, 4.0, 0.0, (char*) "Mason Fabel");
	print3D(-5.0, 3.5, 0.0, (char*) "CS324");
	print3D(-5.0, 3.0, 0.0, (char*) "Assignment 5");

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		1.0, 4.0, 8.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0
	);

    glPushMatrix();

	drawRubik(0.0, 0.0, 0.0, 1.0, GAP);

    glPopMatrix();

    glutSwapBuffers();

    glutPostRedisplay();

	return;
}

void print3D(float x, float y, float z, char* format, ...) {
	va_list args;
	char buffer[128];
	char* p;

	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	glPushMatrix();

	glTranslatef(x, y, z);
	glScalef(1.0 / TEXT_SCALING, 1.0 / TEXT_SCALING, 1.0 / TEXT_SCALING);
	for (p = buffer; *p; p++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
	}

	glPopMatrix();

	return;
}
