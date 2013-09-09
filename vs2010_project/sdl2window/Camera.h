#pragma once

#include <SDL_opengl.h>

class Window;
enum CamMode {Left = 0, Right = 1, Both = 2};

class Camera{
private:
	Camera();
	GLuint texture;
	CamMode mode;
	float x;
	float y;
	float w;
	float h;
public:
	Camera(GLuint _texture, CamMode _mode, float _x, float _y, float _w, float _h, Window* win);
	void render();
};