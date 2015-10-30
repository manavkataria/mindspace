/*
	Kinect CLNUI Sample Code
	Alex Olwal, Jan 2011 (olwal@mit.edu)
*/

#pragma once

#include "kinect.h"
#include "kinect_texture_gl.h"
#include <cv.h>
#include <highgui.h>
#include <cxcore.h>
#include <GL/glut.h>
#include <BlobResult.h>
#include <math.h>

class KinectGL : public Kinect
{
public:
	static const int WIDTH;
	static const int HEIGHT;

	//RGB: KinectTextureGL * rgb;
	KinectTextureGL * z;

	void update();

	//RGB: void renderRGB();
	void renderZ();

	bool start();

	KinectGL();
	~KinectGL();
};