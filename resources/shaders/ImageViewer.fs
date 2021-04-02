#version 460 core
out vec4 FragColor;

in vec2 TexCoord;
uniform sampler2D textureImage;

void main()
{
	FragColor = texture(textureImage, TexCoord);
}