#pragma once
#include <GLAD/glad.h>

/* Error Handling Mechanism */
#define ASSERT(x) if (!(x)) __debugbreak(); // Compiler dependent
#define glCall(x) glClearError();\
	x;\
	ASSERT(glLogCall(#x, __FILE__, __LINE__))

void glClearError();
bool glLogCall(const char* function, const char* file, int line);