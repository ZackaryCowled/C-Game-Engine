//Internal includes
#include "Application.h"

//External includes
#include <GL\glew.h>

//Initialize static FontManager attributes
FT_Library FontManager::m_freeTypeLibrary = nullptr;
map<const unsigned char, Character> FontManager::m_characterContainer = map<const unsigned char, Character>();

//Initializes the FontManager
void FontManager::Initialize()
{
	//Initialize freetype
	if (FT_Init_FreeType(&m_freeTypeLibrary))
	{
		//Display error message window - Free type failed to initialize!
		ErrorMessageWindow("FreeType Error", "ERROR: FreeType failed to initialize!");

		//Quit the application
		Application::Quit();
	}
}

//Releases the FontManagers resources
void FontManager::Shutdown()
{
	//Release the free type library
	FT_Done_FreeType(m_freeTypeLibrary);
}

//Loads the specified font
//fontFilepath - The location, name and file extension for the font file
//fontSize - The size to set the font
void FontManager::LoadFont(const string& fontFilepath, const unsigned int fontSize)
{
	//Clear the applications character container
	m_characterContainer.clear();

	//Create attributes for loading the font
	FT_Face face;

	//Load the specified font
	if (FT_New_Face(m_freeTypeLibrary, fontFilepath.c_str(), 0, &face))
	{
		//Display error message window - [font filepath] failed to import!
		ErrorMessageWindow("Font import error", "ERROR, " + fontFilepath + " failed to import!");

		//Quit the application
		Application::Quit();
	}

	//Set the fonts size to the specified font size
	FT_Set_Pixel_Sizes(face, 0, fontSize);

	//Disable byte alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//For 128 ASCII characters
	for (unsigned char character = 0; character < 128; ++character)
	{
		//Load character glyph
		if (FT_Load_Char(face, character, FT_LOAD_RENDER))
		{
			//Display error message window - character failed to import
			ErrorMessageWindow("Character import error", "ERROR: character failed to import!");

			//Quit the application
			Application::Quit();
		}

		//Generate and bind texture
		unsigned int texture = 0;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		//Set the textures data
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//Store character attributes in a character structure
		Character tempCharacter =
		{
			texture,
			vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			vec2(face->glyph->bitmap_left, fontSize - face->glyph->bitmap_top),
			vec2(face->glyph->advance.x / 64.0f, face->glyph->advance.y / 64.0f)
		};

		//Add the character to the applications character container
		m_characterContainer.insert(pair<const unsigned char, Character>(character, tempCharacter));
	}

	//Enable byte alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	//Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	//Release font
	FT_Done_Face(face);
}

//Returns the specified character
Character& FontManager::GetCharacter(unsigned char character)
{
	//Return the specified character
	return m_characterContainer[character];
}