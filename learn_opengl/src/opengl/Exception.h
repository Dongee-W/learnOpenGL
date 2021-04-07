#pragma once
#include <glad/glad.h>
#include <optional>
#include <stdexcept>

/* Error Handling Mechanism */
#define ASSERT(expression, throwable) if (!(expression)) throw throwable
#define glCall(expression) glClearError();\
	expression;\
	glThrowException(glLogCall(#expression, __FILE__, __LINE__))

void glClearError();
std::optional<std::string> glLogCall(const char* function, const char* file, int line);
void glThrowException(const std::optional<std::string>&);

class OpenGLException : public std::runtime_error {
public:
	explicit OpenGLException(const char* message);
	explicit OpenGLException(const std::string& message);
};