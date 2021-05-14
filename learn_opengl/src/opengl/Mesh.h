#pragma once
#include <vector>
#include <iostream>
#include "Vertex.h"
#include "VertexTexture.h"
#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"

class Mesh {
public:
	// mesh data
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<VertexTexture> textures;
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
		std::vector<VertexTexture> textures) : 
		vb(vertices.data(), vertices.size() * sizeof(Vertex)), ib(indices.data(), indices.size()) {
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
		setupMesh();
	}

	void draw(Shader& shader) {
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		/*
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); // activate texture unit first
			// retrieve texture number (the N in diffuse_textureN)
			std::string number;
			std::string name = textures[i].type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);
			shader.setFloat(("material." + name + number).c_str(), i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
		glActiveTexture(GL_TEXTURE0);*/
		// draw mesh
		shader.use();
		va.bind();
		ib.bind();

		glCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
		va.unbind();
	}
private:
	// render data
	//unsigned int VAO, VBO, EBO;
	VertexArray va;
	VertexBuffer vb;
	IndexBuffer ib;

	void setupMesh() {
		VertexBufferLayout layout;
		layout.push<float>(3);
		layout.push<float>(3);
		layout.push<float>(2);
		va.addBuffer(vb, layout);
	}
};