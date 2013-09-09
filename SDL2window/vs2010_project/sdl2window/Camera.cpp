#include "stdafx.h"
#include "Camera.h"
#include "Window.h"

Camera::Camera(GLuint _texture, CamMode _mode, float _x, float _y, float _w, float _h, Window* win){
	texture = _texture;
	mode = _mode;
	x = _x;
	y = _y;
	w = _w;
	h = _h;

	win->addCamera(this);
}

void Camera::render(){
	switch (mode){
	case Left:
		glDrawBuffer(GL_BACK_LEFT);
		break;
	case Right:
		glDrawBuffer(GL_BACK_RIGHT);
		break;
	case Both:
		glDrawBuffer(GL_BACK);
		break;
	}

	glClear(GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);
        glVertex2f(x, y);
        glTexCoord2f(1.0, 0.0);
        glVertex2f(x + w, y);
        glTexCoord2f(1.0, 1.0);
        glVertex2f(x + w, y + h);
        glTexCoord2f(0.0, 1.0);
        glVertex2f(x , y + h);
    glEnd();
}