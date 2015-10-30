/*
	Kinect CLNUI Sample Code
	Alex Olwal, Jan 2011 (olwal@mit.edu)
*/

#pragma once

#include <GL/glut.h>

class KinectTextureGL
{
public:
	int WIDTH;
	int HEIGHT;
	int INTERNAL_FORMAT;
	int FORMAT;

	GLubyte * data;
	GLuint texture;

	void update();

	void generate();

	void render();

	KinectTextureGL(GLsizei w, GLsizei h, GLint internalFormat, GLenum format);
	~KinectTextureGL();
};