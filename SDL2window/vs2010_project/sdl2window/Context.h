#pragma once

#include <Windows.h>

class Context {
private:
	HGLRC glContext;
	HDC glDeviceContext;
public:
	Context();
	void activate();
	void share(Context* other);
};