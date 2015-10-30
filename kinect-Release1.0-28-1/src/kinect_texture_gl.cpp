/*
	Kinect CLNUI Sample Code
	Alex Olwal, Jan 2011 (olwal@mit.edu)
*/

#include "kinect_texture_gl.h"

void 
KinectTextureGL::render()
{
	glBindTexture( GL_TEXTURE_2D, texture );

	glBegin(GL_QUADS);
/*		glTexCoord2i(0, 0); glVertex2i(0, 0);
		glTexCoord2i(1, 0); glVertex2i(WIDTH, 0);
		glTexCoord2i(1, 1); glVertex2i(WIDTH, HEIGHT);
		glTexCoord2i(0, 1); glVertex2i(0, HEIGHT);
*/


		glTexCoord2i(0, 1); glVertex2i(0, 0);
		glTexCoord2i(1, 1); glVertex2i(WIDTH, 0);
		glTexCoord2i(1, 0); glVertex2i(WIDTH, HEIGHT);
		glTexCoord2i(0, 0); glVertex2i(0, HEIGHT);

	glEnd();
}

KinectTextureGL::KinectTextureGL(GLsizei w, GLsizei h, GLint internalFormat, GLenum format) : 
									WIDTH(w), HEIGHT(h), 
									INTERNAL_FORMAT(internalFormat), FORMAT(format)
{
	const GLsizei W = w;
	const GLsizei H = h;
	const GLsizei I = internalFormat;

	data = new GLubyte[W * H * I];

	generate();
}

KinectTextureGL::~KinectTextureGL()
{
	delete[] data;
	glDeleteTextures(1, &texture);
}

void 
KinectTextureGL::update()
{
	glTexImage2D(GL_TEXTURE_2D, 
		0, //level 
		INTERNAL_FORMAT, WIDTH, HEIGHT, 
		0, //border 
		FORMAT, 
		GL_UNSIGNED_BYTE, 
		data);
}

void 
KinectTextureGL::generate()
{
	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	update();
}