#pragma once
#include <string>
#include <vector>

#include "Vertex.h"
#include "MeshTexture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
using namespace std;

class Mesh {
public:
    // mesh Data
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<MeshTexture> textures;
    //unsigned int VAO;
    shared_ptr<VertexArray> va = make_shared<VertexArray>();

    // constructor
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<MeshTexture> textures) {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;
        vb = make_shared<VertexBuffer>(vertices.data(), vertices.size() * sizeof(Vertex));
        ib = make_shared<IndexBuffer>(indices.data(), indices.size());

        // now that we have all the required data, set the vertex buffers and its attribute pointers.
        setupMesh();
    }

    Mesh(const Mesh& mesh){
        this->vertices = mesh.vertices;
        this->indices = mesh.indices;
        this->textures = mesh.textures;
        this->va = mesh.va;
        this->vb = mesh.vb;
        this->ib = mesh.ib;

    }

    Mesh& operator = (const Mesh& t)
    {
        cout << "Assignment operator called " << endl;
        return *this;
    }

    ~Mesh() {

    }

    // render the mesh
    void draw(Shader& shader)
    {
        // bind appropriate textures
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        unsigned int heightNr = 1;
        for (unsigned int i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
            // retrieve texture number (the N in diffuse_textureN)
            string number;
            string name = textures[i].type;
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++); // transfer unsigned int to stream
            else if (name == "texture_normal")
                number = std::to_string(normalNr++); // transfer unsigned int to stream
            else if (name == "texture_height")
                number = std::to_string(heightNr++); // transfer unsigned int to stream

            // now set the sampler to the correct texture unit
            glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
            // and finally bind the texture
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }

        // draw mesh
        //glCall(glBindVertexArray(VAO));
        //std::cout << "hello " << va.m_RendererID << std::endl;
        (*va).bind();
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // always good practice to set everything back to defaults once configured.
        glActiveTexture(GL_TEXTURE0);
    }

private:
    // render data 
    unsigned int VBO, EBO;
    
    shared_ptr<VertexBuffer> vb;
    shared_ptr<IndexBuffer> ib;

    // initializes all the buffer objects/arrays
    void setupMesh()
    {
        // create buffers/arrays
        //glGenVertexArrays(1, &VAO);
        //glGenBuffers(1, &VBO);
        //glGenBuffers(1, &EBO);

        //glBindVertexArray(VAO);
        //std::cout << "bind " << VAO << std::endl;
        (*va).bind();
        // load data into vertex buffers
        //glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // A great thing about structs is that their memory layout is sequential for all its items.
        // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
        // again translates to 3/2 floats which translates to a byte array.
        //glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
        (*vb).bind();
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // set the vertex attribute pointers
        // vertex Positions
        //glEnableVertexAttribArray(0);
        //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // vertex normals
        //glEnableVertexAttribArray(1);
        //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        // vertex texture coords
        //glEnableVertexAttribArray(2);
        //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
        
        VertexBufferLayout layout;
        layout.push<float>(3);
        layout.push<float>(3);
        layout.push<float>(2);
        (*va).addBuffer((*vb), layout);

        (*ib).bind();
        glBindVertexArray(0);
       // va.unbind();
    }
};