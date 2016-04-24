#include <GL/glut.h>
#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <unistd.h>

const int MODE_QUADS = 0;
const int MODE_TRIANGLES = 1;
const float TEXT_SCALING = 400.0;
const float X_MIN = -5.0;
const float X_MAX = 5.0;
const float Y_MIN = -5.0;
const float Y_MAX = 5.0;
const float Z_MIN = -5.0;
const float Z_MAX = 5.0;
int SUBDIVISIONS = 200;
int MODE = MODE_QUADS;
int WIREFRAME = 0;
float X_INTERVAL = (X_MAX - X_MIN) / SUBDIVISIONS;
float Y_INTERVAL = (Y_MAX - Y_MIN) / SUBDIVISIONS;
float WIDTH = 800;
float HEIGHT = 600;
float** z;

void init(int argc, char** argv);
void print3D(float x, float y, float z, char* format, ...);
void render(void);
void render_callback(void);
void resize_callback(int w, int h);
void colorAtZ(float z, float* r, float* g, float* b);
float funcAtXY(float x, float y);

int main(int argc, char** argv) {
	int i;
	int j;
	float x;
	float y;

	init(argc, argv);

	z = new float*[SUBDIVISIONS];
	for (i = 0; i < SUBDIVISIONS; i++) {
		z[i] = new float[SUBDIVISIONS];
	}

	for (i = 0; i < SUBDIVISIONS; i++) {
		x = X_MIN + X_INTERVAL * i;
		for (j = 0; j < SUBDIVISIONS; j++) {
			y = Y_MIN + Y_INTERVAL * j;
			z[i][j] = funcAtXY(x, y);
		}
	}

	render();

	for (i = 0; i < SUBDIVISIONS; i++) {
		delete z[i];
	}
	delete z;

	exit(0);
}

float funcAtXY(float x, float y) {
	float n;
	float z;

	n = 0.25;
	z = 5 * cos(2 * x + 3 * sin(2 * y)) * exp(-1 * n * (x * x + y * y));

	return z;
}

void colorAtZ(float z, float* r, float* g, float* b) {
	float frac;

	frac = (z - Z_MIN) / (Z_MAX - Z_MIN);
	*r = frac;
	*g = 0.0;
	*b = 1.0 - frac;

	return;
}

void init(int argc, char** argv) {
	char c;
	int val;

    glutInit(&argc, argv);

	while ((c = getopt(argc, argv, "w:h:d:m:o?")) != -1) {
		switch (c) {
			case 'w':
				val = atoi(optarg);
				if (val > 0) {
					WIDTH = atoi(optarg);
				} else {
					fprintf(stderr, "invalid width: %i\n", val);
					exit(1);
				}
				break;
			case 'h':
				val = atoi(optarg);
				if (val > 0) {
					HEIGHT = atoi(optarg);
				} else {
					fprintf(stderr, "invalid height: %i\n", val);
					exit(1);
				}
				break;
			case 'd':
				val = atoi(optarg);
				if (val > 0) {
					SUBDIVISIONS = atoi(optarg);
				} else {
					fprintf(stderr, "invalid division: %i\n", val);
					exit(1);
				}
				break;
			case 'm':
				if (!strcmp("quads", optarg)) {
					MODE = MODE_QUADS;
				} else if (!strcmp("triangles", optarg)) {
					MODE = MODE_TRIANGLES;
				} else {
					fprintf(stderr, "invalid mode: %s\n", optarg);
					exit(1);
				}
				break;
			case 'o':
				WIREFRAME = 1;
				break;
			case '?':
				fprintf(stdout, "Usage: %s [-w WIDTH] [-h HEIGHT]", argv[0]);
				fprintf(stdout, " [-d DIV] [-m MODE] [-o]\n");
				fprintf(stdout, "\n");
				fprintf(stdout, "  -d DIV    render in DIV intervals\n");
				fprintf(stdout, "  -w WIDTH  set window width to WIDTH\n");
				fprintf(stdout, "  -h HEIGHT set window height to HEIGHT\n");
				fprintf(stdout, "  -m MODE   set the render mode to MODE;");
				fprintf(stdout, " MODE is 'points' or 'lines'\n");
				fprintf(stdout, "  -o        enable outline mode\n");
				fprintf(stdout, "  -?        display help and exit\n");
				exit(0);
				break;
		}
	}

	X_INTERVAL = (X_MAX - X_MIN) / SUBDIVISIONS;
	Y_INTERVAL = (Y_MAX - Y_MIN) / SUBDIVISIONS;

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
	int i;
	int j;
	float r;
	float g;
	float b;
	float x1;
	float x2;
	float y1;
	float y2;

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
	print3D(X_MIN, Y_MAX - 1.0, 0.0, (char*) "Mason Fabel");
	print3D(X_MIN, Y_MAX - 1.5, 0.0, (char*) "CS324");
	print3D(X_MIN, Y_MAX - 2.0, 0.0, (char*) "Assignment 5");

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		5.0, 2.0, 10.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0
	);

    glPushMatrix();

	glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 1.0);
	glVertex3f(X_MIN, 0.0, 0.0);
	glVertex3f(X_MAX, 0.0, 0.0);
	glVertex3f(0.0, Y_MIN, 0.0);
	glVertex3f(0.0, Y_MAX, 0.0);
	glVertex3f(0.0, 0.0, Z_MIN);
	glVertex3f(0.0, 0.0, Z_MAX);
	glEnd();

	print3D(X_MIN - 1, 0.0, 0.0, (char*) "-x");
	print3D(X_MAX + 1, 0.0, 0.0, (char*) "+x");
	print3D(0.0, Z_MIN - 1, 0.0, (char*) "-y");
	print3D(0.0, Z_MAX + 1, 0.0, (char*) "+y");
	print3D(0.0, 0.0, Y_MIN - 1, (char*) "-z");
	print3D(0.0, 0.0, Y_MAX + 1, (char*) "+z");

    glColor3f(0.1, 0.1, 0.1);
	switch (MODE) {
		case MODE_QUADS:
			for (i = 0; i < SUBDIVISIONS - 1; i++) {
				x1 = X_MIN + X_INTERVAL * i;
				x2 = X_MIN + X_INTERVAL * (i + 1);
				for (j = 0; j < SUBDIVISIONS - 1; j++) {
					y1 = Y_MIN + Y_INTERVAL * j;
					y2 = Y_MIN + Y_INTERVAL * (j + 1);

					if (WIREFRAME) {
						glBegin(GL_LINE_LOOP);
					} else {
						glBegin(GL_QUADS);
					}
					colorAtZ(z[i][j], &r, &g, &b);
					glColor3f(r, g, b);
					glVertex3f(x1, z[i][j], y1);
					colorAtZ(z[i + 1][j], &r, &g, &b);
					glColor3f(r, g, b);
					glVertex3f(x2, z[i + 1][j], y1);
					colorAtZ(z[i + 1][j + 1], &r, &g, &b);
					glColor3f(r, g, b);
					glVertex3f(x2, z[i + 1][j + 1], y2);
					colorAtZ(z[i][j + 1], &r, &g, &b);
					glColor3f(r, g, b);
					glVertex3f(x1, z[i][j + 1], y2);
					glEnd();
				}
			}
			break;
		case MODE_TRIANGLES:
			for (i = 0; i < SUBDIVISIONS - 1; i++) {
				x1 = X_MIN + X_INTERVAL * i;
				x2 = X_MIN + X_INTERVAL * (i + 1);
				for (j = 0; j < SUBDIVISIONS - 1; j++) {
					y1 = Y_MIN + Y_INTERVAL * j;
					y2 = Y_MIN + Y_INTERVAL * (j + 1);

					if (WIREFRAME) {
						glBegin(GL_LINE_LOOP);
					} else {
						glBegin(GL_TRIANGLES);
					}
					colorAtZ(z[i][j], &r, &g, &b);
					glColor3f(r, g, b);
					glVertex3f(x1, z[i][j], y1);
					colorAtZ(z[i + 1][j], &r, &g, &b);
					glColor3f(r, g, b);
					glVertex3f(x2, z[i + 1][j], y1);
					colorAtZ(z[i][j + 1], &r, &g, &b);
					glColor3f(r, g, b);
					glVertex3f(x1, z[i][j + 1], y2);
					glEnd();

					if (WIREFRAME) {
						glBegin(GL_LINE_LOOP);
					} else {
						glBegin(GL_TRIANGLES);
					}
					colorAtZ(z[i + 1][j + 1], &r, &g, &b);
					glColor3f(r, g, b);
					glVertex3f(x2, z[i + 1][j + 1], y2);
					colorAtZ(z[i][j + 1], &r, &g, &b);
					glColor3f(r, g, b);
					glVertex3f(x1, z[i][j + 1], y2);
					colorAtZ(z[i + 1][j], &r, &g, &b);
					glColor3f(r, g, b);
					glVertex3f(x2, z[i + 1][j], y1);
					glEnd();
				}
			}
			break;
	}

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
