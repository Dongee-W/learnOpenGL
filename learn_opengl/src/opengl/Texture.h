#pragma once
#include <string>

class Texture {
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int  m_Width, m_Height, m_BPP;
	bool flipVertically = true;
public:
	Texture(const std::string& path);
	Texture(const std::string& path, bool flipVertically);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unbind();

	inline int getWidth() const { return m_Width; }
	inline int getHeight() const { return m_Height; }
	inline int getID() const { return m_RendererID; }
 };