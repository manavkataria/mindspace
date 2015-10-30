/*
	Kinect CLNUI Sample Code
	Alex Olwal, Jan 2011 (olwal@mit.edu)
*/

#include "kinect_gl.h"r
using namespace cv;

KinectGL kinect;

void display (void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);

	//RGB: kinect.renderRGB();
	//RGB: glTranslatef(KinectGL::WIDTH, 0, 0);
	kinect.renderZ();
	glPopMatrix();

	glutSwapBuffers();
	kinect.update();
}

void reshape(GLsizei w, GLsizei h)
{ glOrtho(0, w, 0, h, -100, 100); }

void idle () 
{ glutPostRedisplay(); }

void stop()
{
	kinect.stop();
	
	while (kinect.initialized)
		Sleep(5);

	Sleep(500);

	exit(0);
}

void keyboard_event(unsigned char key, int kx, int ky)
{
	switch (key)
	{
	case 27: stop(); break;
	}
}

int whKinect=0;

void initGLKinect()
{
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);	
	//RGB: glutInitWindowSize(1280, 480);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	whKinect = glutCreateWindow("Kinect Demo");
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//GL: glutIdleFunc(idle);
	glutKeyboardFunc(keyboard_event);
	
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_FRONT_AND_BACK);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_FLAT);
}

void mainKinect()
{
	cout<<"Kinect CLNUI Sample Code"<<endl;
	cout<<"Alex Olwal, Jan 2011 (olwal@mit.edu)"<<endl<<endl;;
	namedWindow("abc",1);
	//GL: 
	initGLKinect();

	if ( !kinect.init() ) 
		return;

	if ( !kinect.start() ) 
		return;
	
	//GL: glutMainLoop();
}