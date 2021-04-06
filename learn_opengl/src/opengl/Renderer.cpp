#include <GLAD/glad.h>
#include <iostream>

#include "Renderer.h"
#include "Exception.h"



void Renderer::clear() const {
	glCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
	glCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::draw(const VertexArray& va,
	const IndexBuffer& ib, const Shader& shader) const {
	shader.use();
	va.bind();
	ib.bind();

	glCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, 0));

}
