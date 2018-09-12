//Pragma comments
#pragma once

//External incldues
#include <ft2build.h>
#include <freetype\freetype.h>
#include <glm\glm.hpp>
#include <map>

//Using directives
using namespace glm;
using std::map;
using std::pair;

//Character structure
struct Character
{
	//The characters texture sampler
	unsigned int textureSampler;

	//The scale of the character in pixels
	vec2 scale;

	//Offset from the baseline to the top left corner of the character
	vec2 bearing;

	//Offset to the next character
	vec2 advance;
};

//Singleton class for managing the applications font
class FontManager
{
public:
	//Initializes the FontManager
	static void Initialize();

	//Releases the FontManagers resources
	static void Shutdown();

	//Loads the specified font
	//fontFilepath - The location, name and file extension for the font file
	//fontSize - The size to set the font
	static void LoadFont(const string& fontFilepath, const unsigned int fontSize);

	//Returns the specified character
	static Character& GetCharacter(unsigned char character);

private:
	//Freetype library object
	static FT_Library m_freeTypeLibrary;

	//Container for storing the application loaded fonts characters
	static map<const unsigned char, Character> m_characterContainer;
};