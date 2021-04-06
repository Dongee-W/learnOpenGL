#include "Exception.h"
#include <iostream>

/* Error Handling Mechanism */
void glClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool glLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		//throw std::exception("[OpenGL Error]");
		std::cout << "[OpengGL ERROR] (" << error << ") " <<
			function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}