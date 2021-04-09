#include <iostream>
#include <sstream>
#include "Exception.h"

/* Error Handling Mechanism */
void glClearError() {
	while (glGetError() != GL_NO_ERROR);
}


std::optional<std::string> glLogCall(const char* function, const char* file, int line) {
	int flag = 0;
	std::stringstream ss;
	while (GLenum error = glGetError()) {
		flag = 1;
		ss << "[OpengGL ERROR] (" << error << ") " <<
			function << " " << file << ":" << line << std::endl;
	}
	if (flag) {
		return std::optional<std::string>{ss.str()};
	} 
	else {
		return std::optional<std::string>{};
	}
	
}
void glThrowException(const std::optional<std::string>&  log) {
	if (log) throw OpenGLException(log.value());
}

OpenGLException::OpenGLException(const char* message)
	: std::runtime_error{ message }{}

OpenGLException::OpenGLException(const std::string& message) 
	: std::runtime_error{ message.c_str() } {}
