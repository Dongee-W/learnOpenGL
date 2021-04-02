#ifndef STB_IMAGE_IMPLEMENTATION_
#define STB_IMAGE_IMPLEMENTATION_
#include "stb_image.h"
#endif /* STB_IMAGE_IMPLEMENTATION_ */
#include <iostream>

int demoImageLoading() {
	int width, height, nrChannels;
	unsigned char* data = stbi_load("../resources/rock_texture.jpg", &width, &height,
		&nrChannels, 0);

	std::cout << width << std::endl;
	std::cout << height << std::endl;
	std::cout << nrChannels << std::endl;
	
	return 0;
}