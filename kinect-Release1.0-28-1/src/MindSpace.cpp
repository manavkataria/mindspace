#include <iostream>
#include <GL/glut.h>

extern int whKinect;
extern int whSnowman;
extern void idle();
extern void renderScene(void);

extern int mainSnowMan(int argc, char **argv);
extern void mainKinect();

using namespace std;

int main(int argc, char **argv){
	mainKinect();
	mainSnowMan(argc, argv);
	return 0;
}

//extern void moveMeFlaty(int i);		//?Rotate?
extern void moveMePan(int i);		//Translate
extern void moveMePanz(int i);		//?up/down?
extern void moveMeFlat(int i);		//Zoom

#define SNOWMAN_PAN_SCALE	30
#define SNOWMAN_ZOOM_SCALE	8

//#define SNOWMAN_PAN_SCALE	10
//#define SNOWMAN_ZOOM_SCALE	1

void kinect_GL_glue(int diffx, int diffy, int diffz)
{
	glutSetWindow(whSnowman);
	
	//Left Right Pan with Right Left Movement
	if (diffx > 0) {
		moveMePan(-SNOWMAN_PAN_SCALE);
	} else if (diffx < 0) {
		moveMePan(SNOWMAN_PAN_SCALE);
	} else {
	}

/*	// up/down
	if (diffy > 0) {
		moveMePanz(-SNOWMAN_ZOOM_SCALE);
	} else if (diffy < 0) {
		moveMePanz(SNOWMAN_ZOOM_SCALE);
	} else {
	}
*/

	// Zoom with Depth Values
	if (diffz > 0) {
		moveMeFlat(SNOWMAN_ZOOM_SCALE);
	} else if (diffz < 0) {
		moveMeFlat(-SNOWMAN_ZOOM_SCALE);
	} else {
	}

	// Zoom
/* 
	if (diffy > 0) {
		moveMeFlat(-SNOWMAN_ZOOM_SCALE);
	} else if (diffy < 0) {
		moveMeFlat(SNOWMAN_ZOOM_SCALE);
	} else {
	}
*/
}

void parentIdleFunction()
{
	//set kinect as active window
	glutSetWindow(whKinect);
	idle();

	//set snowman as active window
	glutSetWindow(whSnowman);
	renderScene();
}

