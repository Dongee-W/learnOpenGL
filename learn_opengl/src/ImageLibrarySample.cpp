#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

int main() {
	int width, height, nrChannels;
	unsigned char* data = stbi_load("resources/rock_texture.jpg", &width, &height,
		&nrChannels, 0);

	std::cout << width << std::endl;
	std::cout << height << std::endl;
	std::cout << nrChannels << std::endl;

}