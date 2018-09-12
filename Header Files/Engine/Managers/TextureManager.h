//Pragma comments
#pragma once

//External includes
#include <map>
#include <string>

//Using directives
using std::map;
using std::pair;
using std::string;

//Singleton class providing various functions for manipulating the applications textures
class TextureManager
{
public:
	//Destroys all the applications textures
	static void DestroyAllTextures();

	//Loads the specified texture and returns a texture sampler to the texture
	//textureFilepath - The location, name and file extension for the texture file
	static const unsigned int LoadTexture(const string& textureFilepath);

private:
	//Container for storing the applications textures
	static map<const string, unsigned int> m_textureContainer;
};