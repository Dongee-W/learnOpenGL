#pragma once

class VertexBuffer {
private:
	unsigned int m_RendererID;

public:
	VertexBuffer(const void* data, unsigned int ID);
	~VertexBuffer();

	void bind() const;
	void unbind() const;
		
};