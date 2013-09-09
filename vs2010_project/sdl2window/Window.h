#pragma once
#include <SDL.h>
#include "Camera.h"
#include <vector>
#include "Context.h"

class Window {
private:
	SDL_Window *win;
	SDL_GLContext glContext;
	SDL_Rect bounds;
	std::vector<Camera*> cameras;
	Context* myContext;

	Window();
public:
	Window(int displayNum);
	~Window();

	void render();
	int getWidth(){return bounds.w;}
	int getHeight(){return bounds.h;}
	void addCamera(Camera* cam);
};