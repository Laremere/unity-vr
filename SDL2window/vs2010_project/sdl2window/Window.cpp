#include "stdafx.h"
#include "Window.h"
#include <SDL.h>
#include <SDL_opengl.h>

int NumberOfWindows = 0;

Window::Window(int displayNum){
	Context* otherContext = new Context();

	if (NumberOfWindows == 0){
		SDL_Init(SDL_INIT_VIDEO);
		SDL_GL_SetAttribute(SDL_GL_STEREO, 1);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	}
	NumberOfWindows++;

	SDL_GetDisplayBounds(displayNum, &bounds);
	//win = SDL_CreateWindow("SDL2window", bounds.x, bounds.y, bounds.w, bounds.h, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);
	win = SDL_CreateWindow("SDL2window", bounds.x, bounds.y, bounds.w, bounds.h, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_SHOWN);

	glContext = SDL_GL_CreateContext(win);

	myContext = new Context();
	otherContext -> share(myContext);
	
	glClearDepth(1.0f);
    glViewport(0, 0, bounds.w, bounds.h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_2D);
    glLoadIdentity();

	otherContext->activate();
	delete otherContext;
}

Window::~Window(){
	delete myContext;

	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(win);

	NumberOfWindows--;
	if (NumberOfWindows == 0){
		SDL_Quit();
	}
}


void Window::render(){
	Context* otherContext = new Context();
	myContext->activate();
	SDL_GL_MakeCurrent(win, glContext);

    glLoadIdentity();
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);

	for(unsigned int i = 0; i < cameras.size(); i++){
		cameras.at(i)->render();
	}

	SDL_GL_SwapWindow(win);

	otherContext->activate();
	delete otherContext;
}

void Window::addCamera(Camera* cam){
	cameras.push_back(cam);
}