#version 460 core
out vec4 FragColor;

in vec2 TexCoord;
uniform sampler2D u_Texture;

void main()
{
	FragColor = vec4(0.2, 0.2, 0.2, 1.0);
}