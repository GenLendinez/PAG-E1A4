#include "PAGTexture.h"

PAGTexture::PAGTexture()
{
}

PAGTexture::~PAGTexture()
{

}

void PAGTexture::loadTexture(char * path_img, GLuint min_filter, GLuint mag_filter)
{
	int imgWidth, imgHeight;
	unsigned char *image;
	image = SOIL_load_image(path_img,
		&imgWidth,
		&imgHeight,
		0,
		SOIL_LOAD_RGBA);
	if (imgWidth == 0) {
		std::cout << "Failed to load image." << std::endl;
	}
	GLuint id_img;
	glGenTextures(1, &id_img);
	glBindTexture(GL_TEXTURE_2D, id_img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight,
		0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	ep = id_img;
	id_imgs.push_back(id_img);
	SOIL_free_image_data(image);
}

void PAGTexture::applyTexture(GLuint id, int pos)
{
	glActiveTexture(id);

	glBindTexture(GL_TEXTURE_2D, id_imgs.at(pos));

}
