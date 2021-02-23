#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
const double TWO_PI = 6.2831853;
GLsizei winWidth = 1280, winHeight = 720; // Initial display window size.
GLuint regPolygon;

float frameTimeElapsed;
float old_t;

class ScrPt {
public:
	GLfloat x, y;
	ScrPt(GLfloat a, GLfloat b) {
		x = a;
		b = y;
	}
};

static float lerp(float, float, float);
static void registerPolygons(ScrPt[], ScrPt[]);

static void init(void)
{
	ScrPt poly1[4] = { ScrPt(20, 30), ScrPt(50, 60) , ScrPt(-10, -40) , ScrPt(40, -60) };
	ScrPt poly2[4] = { ScrPt(20, 30), ScrPt(50, 60) , ScrPt(-10, -40) , ScrPt(40, -60) };

	registerPolygons(poly1, poly2);

	old_t = glutGet(GLUT_ELAPSED_TIME);
}

static void registerPolygons(ScrPt poly1[], ScrPt poly2[]) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	regPolygon = glGenLists(1);
	glNewList(regPolygon, GL_COMPILE);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	GLint k;
	int length = sizeof(poly1) / sizeof(poly1[0]);
	for (k = 0; k < length; k++) {
		glVertex2f(poly1[k].x, poly1[k].y);
	}
	glEnd();
	glEndList();
}

void displayAll(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glCallList(regPolygon);
	glPopMatrix();
	glutSwapBuffers();
	glFlush();
}
void updateKeyFrame(float dt)
{
	frameTimeElapsed += dt;

	if (frameTimeElapsed > 1.0f) {
		
	}
}

static float lerp(float a, float b, float t) {
	return a + t * (b - a);
}

void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, (GLsizei)newWidth, (GLsizei)newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-(GLfloat)newWidth/2, (GLfloat)newWidth / 2, -(GLfloat)newHeight/2, (GLfloat)newHeight/2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
}

void idle(void) {
	int t;
	/* Delta time in seconds. */
	float dt;
	t = glutGet(GLUT_ELAPSED_TIME);
	dt = ((float)t - (float)old_t) / 1000.0f;
	old_t = t;

	updateKeyFrame(dt);

	glutPostRedisplay();
}

void mouseFcn(GLint button, GLint action, GLint x, GLint y)
{
	switch (button) {
	case GLUT_MIDDLE_BUTTON: // Start the rotation.
		if (action == GLUT_DOWN)
			glutIdleFunc(idle);
		break;
	case GLUT_RIGHT_BUTTON: // Stop the rotation.
		if (action == GLUT_DOWN)
			glutIdleFunc(NULL);
		break;
	default:
		break;
	}
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Morph Example");
	init();
	glutDisplayFunc(displayAll);
	glutReshapeFunc(winReshapeFcn);
	glutMouseFunc(mouseFcn);
	glutMainLoop();
}