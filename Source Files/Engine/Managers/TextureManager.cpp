//Internal includes
#include "Application.h"

//External includes
#include <GL\glew.h>
#include <SOIL.h>

//Initialize static texture manager attributes
map<const string, unsigned int> TextureManager::m_textureContainer = map<const string, unsigned int>();

//Destroys all the applications textures
void TextureManager::DestroyAllTextures()
{
	//Create texture iterator
	map<const string, unsigned int>::iterator textureIterator = m_textureContainer.begin();

	//While the texture iterator is not at the end of the texture container
	while (textureIterator != m_textureContainer.end())
	{
		//Delete the texture from GPU memory
		glDeleteTextures(1, &textureIterator->second);

		//Erase the texture from the applications texture container
		m_textureContainer.erase(textureIterator);

		//Set the texture iterator to the first element in the texture container
		textureIterator = m_textureContainer.begin();
	}
}

//Loads the specified texture and returns a texture sampler to the texture
//textureFilepath - The location, name and file extension for the texture file
const unsigned int TextureManager::LoadTexture(const string& textureFilepath)
{
	//If no texture with the specified filepath has already been loaded
	if (m_textureContainer.find(textureFilepath) == m_textureContainer.end())
	{
		//Create temporary attributes for loading the texture
		unsigned int textureSampler = 0;
		int textureWidth = 0;
		int textureHeight = 0;

		//Load texture file into CPU memory
		unsigned char* textureFile = SOIL_load_image(textureFilepath.c_str(), &textureWidth, &textureHeight, 0, SOIL_LOAD_RGBA);

		//Load texture file into GPU memory
		glGenTextures(1, &textureSampler);
		glBindTexture(GL_TEXTURE_2D, textureSampler);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureFile);

		//Configure texture
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		//Release the texture from CPU memory
		SOIL_free_image_data(textureFile);

		//Unbind texture
		glBindTexture(GL_TEXTURE_2D, 0);

		//Add texture to the applications texture container
		m_textureContainer.insert(pair<const string, unsigned int>(textureFilepath, textureSampler));
	}

	//Return the texture
	return m_textureContainer[textureFilepath];
}