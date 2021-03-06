#include <sstream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#include "Texture.h"
#include "Exception.h"
#ifndef STB_IMAGE_IMPLEMENTATION_
#define STB_IMAGE_IMPLEMENTATION_
#include "stb_image.h"
#endif /* STB_IMAGE_IMPLEMENTATION_ */

Texture::Texture(const std::string& path) : 
    Texture::Texture(path, true) {}

Texture::Texture(const std::string& path, bool flipVertically) 
	: m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), 
	m_Width(0), m_Height(0), m_BPP(0) {
	glCall(glGenTextures(1, &m_RendererID));
	glCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

    //if (flipVertically)
    //    stbi_set_flip_vertically_on_load(1);
    //m_LocalBuffer = stbi_load(path.c_str() , &m_Width, &m_Height,
    //    &m_BPP, 0);
    cv::Mat image = cv::imread(path);

    if (image.empty()) {
        std::stringstream ss;
        ss << "Failed to load texture at: " << path;
        throw std::runtime_error(ss.str().c_str());
    }

    m_LocalBuffer = image.data;
    m_Width = image.size().width;
    m_Height = image.size().height;
    m_BPP = image.elemSize();
    cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
    if (flipVertically)
        // 0: flip around x-axis, positive value: flip around y-axis, 
        // negative value both axes.
        cv::flip(image, image, 0);




    // set the texture wrapping/filtering options (on currently bound texture)
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    glPixelStorei(GL_UNPACK_ALIGNMENT, (image.step & 3) ? 1 : 4);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, image.step / image.elemSize());

    glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB,
        GL_UNSIGNED_BYTE, m_LocalBuffer));

    glCall(glBindTexture(GL_TEXTURE_2D, 0));

    if (m_LocalBuffer)
        //stbi_image_free(m_LocalBuffer);
        image.release();
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
