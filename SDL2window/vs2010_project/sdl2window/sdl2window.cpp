// sdl2window.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Window.h"
#include "Camera.h"

extern "C" __declspec(dllexport) Window* openWindow(int displayNum){
	return new Window(displayNum);
}

extern "C" __declspec(dllexport) void closeWindow(Window* win){
	delete win;
}

extern "C" __declspec(dllexport) int getWindowWidth(Window* win){
	return win->getWidth();
}

extern "C" __declspec(dllexport) int getWindowHeight(Window* win){
	return win->getHeight();
}

extern "C" __declspec(dllexport) void renderWindow(Window* win){
	win->render();
}

extern "C" __declspec(dllexport) void addCamera(GLuint texture, CamMode mode, float x, float y, float w, float h, Window* win){
	new Camera(texture, mode, x, y, w, h, win);
}