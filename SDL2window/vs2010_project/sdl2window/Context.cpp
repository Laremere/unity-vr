#include "stdafx.h"
#include "Context.h"

Context::Context(){
	glContext = wglGetCurrentContext();
	glDeviceContext = wglGetCurrentDC();
}


void Context::activate(){
	wglMakeCurrent(glDeviceContext, glContext);	
}


void Context::share(Context* other){
	wglShareLists(glContext, other->glContext);
}