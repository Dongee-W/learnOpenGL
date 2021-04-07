#include "Texture.h"
#include "Exception.h"
#ifndef STB_IMAGE_IMPLEMENTATION_
#define STB_IMAGE_IMPLEMENTATION_
#include "stb_image.h"
#endif /* STB_IMAGE_IMPLEMENTATION_ */

Texture::Texture(const std::string& path) 
	: m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), 
	m_Width(0), m_Height(0), m_BPP(0) {
	glCall(glGenTextures(1, &m_RendererID));
	glCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

    stbi_set_flip_vertically_on_load(1);
    m_LocalBuffer = stbi_load(path.c_str() , &m_Width, &m_Height,
        &m_BPP, 0);
	// todo add read image exception
    if (!m_LocalBuffer) {
        throw std::exception("Failed to load texture.");
    }

    // set the texture wrapping/filtering options (on currently bound texture)
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB,
        GL_UNSIGNED_BYTE, m_LocalBuffer));

    glCall(glBindTexture(GL_TEXTURE_2D, 0));

    if (m_LocalBuffer)
        stbi_image_free(m_LocalBuffer);
}

Texture::~Texture() {
    glCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::bind(unsigned int slot) const {
    glCall(glActiveTexture(GL_TEXTURE0 + slot));
    glCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::unbind() {
    glCall(glBindTexture(GL_TEXTURE_2D, 0));
}
