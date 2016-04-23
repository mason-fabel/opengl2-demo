#include <GL/glut.h>
#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <unistd.h>

const int MODE_POINTS = 0;
const int MODE_LINES = 1;
const float TEXT_SCALING = 400.0;
const float X_MIN = -3.14;
const float X_MAX = 3 * 3.14;
const float Y_MIN = -3.0;
const float Y_MAX = 3.0;
int SUBDIVISIONS = 100;
int MODE = MODE_POINTS;
float INTERVAL = (X_MAX - X_MIN) / SUBDIVISIONS;
float WIDTH = 800;
float HEIGHT = 600;

void init(int argc, char** argv);
void print3D(float x, float y, char* format, ...);
void render(void);
void render_callback(void);
void resize_callback(int w, int h);
float funcAtX(float x);

int main(int argc, char** argv) {
	init(argc, argv);

	render();

	exit(0);
}

float funcAtX(float x) {
	float y;

	y = exp(-0.2 * x) * sin(3.0 * x);

	return y;
}


void init(int argc, char** argv) {
	char c;
	int val;

    glutInit(&argc, argv);

	while ((c = getopt(argc, argv, "?d:h:m:w:")) != -1) {
		switch (c) {
			case 'd':
				val = atoi(optarg);
				if (val > 0) {
					SUBDIVISIONS = atoi(optarg);
				} else {
					fprintf(stderr, "invalid division: %i\n", val);
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
			case 'w':
				val = atoi(optarg);
				if (val > 0) {
					WIDTH = atoi(optarg);
				} else {
					fprintf(stderr, "invalid width: %i\n", val);
					exit(1);
				}
				break;
			case 'm':
				if (!strcmp("points", optarg)) {
					MODE = MODE_POINTS;
				} else if (!strcmp("lines", optarg)) {
					MODE = MODE_LINES;
				} else {
					fprintf(stderr, "invalid mode: %s\n", optarg);
					exit(1);
				}
				break;
			case '?':
				fprintf(stdout, "Usage: %s [-d DIV] [-w WIDTH]", argv[0]);
				fprintf(stdout, " [-h HEIGHT] [-m MODE]\n");
				fprintf(stdout, "\n");
				fprintf(stdout, "  -d DIV    render in DIV intervals\n");
				fprintf(stdout, "  -w WIDTH  set window width to WIDTH\n");
				fprintf(stdout, "  -h HEIGHT set window height to HEIGHT\n");
				fprintf(stdout, "  -m MODE   set the render mode to MODE;");
				fprintf(stdout, " MODE is 'points' or 'lines'\n");
				fprintf(stdout, "  -?        display help and exit\n");
				exit(0);
				break;
		}
	}

	INTERVAL = (X_MAX - X_MIN) / SUBDIVISIONS;

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
	float x;
	float y;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0.0, 0.0, WIDTH, HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, WIDTH / HEIGHT, 1, 10);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		X_MIN + ((X_MAX - X_MIN) / 2), Y_MIN + ((Y_MAX - Y_MIN) / 2), 5.0,
		X_MIN + ((X_MAX - X_MIN) / 2), Y_MIN + ((Y_MAX - Y_MIN) / 2), 0.0,
		0.0, 1.0, 0.0
	);

    glPushMatrix();

    glColor3f(1.0, 1.0, 1.0);
	print3D(X_MIN, Y_MAX - 0.0, (char*) "Mason Fabel");
	print3D(X_MIN, Y_MAX - 0.5, (char*) "CS324");
	print3D(X_MIN, Y_MAX - 1.0, (char*) "Assignment 5");

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
	switch (MODE) {
		case MODE_LINES:
			glBegin(GL_LINES);
			for (i = 0; i < SUBDIVISIONS - 1; i++) {
				x = X_MIN + (INTERVAL * i);
				y = funcAtX(x);
				glVertex3f(x, y, 0.0);
				x = X_MIN + (INTERVAL * (i + 1));
				y = funcAtX(x);
				glVertex3f(x, y, 0.0);
			}
			glEnd();
			break;
		case MODE_POINTS:
		default:
			glBegin(GL_POINTS);
			for (i = 0; i < SUBDIVISIONS; i++) {
				x = X_MIN + (INTERVAL * i);
				y = funcAtX(x);
				glVertex3f(x, y, 0.0);
			}
			glEnd();
	}

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
