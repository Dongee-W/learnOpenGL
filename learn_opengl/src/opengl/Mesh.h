#pragma once
#include <vector>
#include "Vertex.h"
#include "VertexTexture.h"
#include "Shader.h"

class Mesh {
public:
	// mesh data
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<VertexTexture> textures;
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
		std::vector<VertexTexture> textures) {
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
		setupMesh();
	}

	void draw(Shader& shader);
private:
	// render data
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};