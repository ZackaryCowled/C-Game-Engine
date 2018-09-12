//Internal includes
#include "Application.h"

//External includes
#include <GL\glew.h>

//Creates and initializes a GUICharacter instance (Default constructor)
GUICharacter::GUICharacter()
{
	//Initialize character
	m_character = ' ';
	m_data[0] = 0.0f;
	m_data[1] = 0.0f;
	m_data[2] = 0.0f;
	m_data[3] = 0.0f;
	m_data[4] = 1.0f;
	m_data[5] = 1.0f;
	m_data[6] = 1.0f;
	m_data[7] = 1.0f;
	m_bearing = vec2(0.0f);
	m_advance = vec2(0.0f);
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), m_data, GL_STREAM_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 2));
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 4));
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	SetCharacter(m_character);
	SetType(COMPONENT_TYPE_GUI_CHARACTER);
}

//Creates and initializes a GUICharacter instance using the specified character
GUICharacter::GUICharacter(const unsigned char character)
{
	//Initialize character
	m_character = character;
	m_data[0] = 0.0f;
	m_data[1] = 0.0f;
	m_data[2] = 0.0f;
	m_data[3] = 0.0f;
	m_data[4] = 1.0f;
	m_data[5] = 1.0f;
	m_data[6] = 1.0f;
	m_data[7] = 1.0f;
	m_bearing = vec2(0.0f);
	m_advance = vec2(0.0f);
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), m_data, GL_STREAM_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 2));
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 4));
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	SetCharacter(m_character);
	SetType(COMPONENT_TYPE_GUI_CHARACTER);
}

//Releases GUICharacter resources
GUICharacter::~GUICharacter()
{
	//If the GUICharacter is valid
	if (m_vao)
	{
		//Delete GPU resources
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_vbo);
	}
}

//Returns the character the GUICharacter is using
const unsigned char GUICharacter::GetCharacter()
{
	//Return the character the GUICharacter is using
	return m_character;
}

//Returns the position of the GUICharacter in pixel-space
vec2 GUICharacter::GetPosition()
{
	//Return the GUICharacters position
	return vec2(m_data[0], m_data[1]);
}

//Returns the scale of the GUICharacter in pixel-space
vec2 GUICharacter::GetScale()
{
	//Return the GUICharacters scale
	return vec2(m_data[2], m_data[3]);
}

//Returns the characters bearing
vec2 GUICharacter::GetBearing()
{
	//Return the characters bearing
	return m_bearing;
}

//Returns the characters advance
vec2 GUICharacter::GetAdvance()
{
	//Return the characters advance
	return m_advance;
}

//Returns the color of the GUICharacter
vec4 GUICharacter::GetColor()
{
	//Return the GUICharacters color
	return vec4(m_data[4], m_data[5], m_data[6], m_data[7]);
}

//Returns the texture map for the GUICharacter
unsigned int GUICharacter::GetTextureMap()
{
	//Return the GUICharacters texture map
	return m_textureMap;
}

//Sets the character for the GUICharacter to use
void GUICharacter::SetCharacter(const unsigned char character)
{
	//Set the GUICharacters character
	m_character = character;
	Character& tempCharacter = FontManager::GetCharacter(m_character);
	SetScale(tempCharacter.scale);
	SetBearing(tempCharacter.bearing);
	SetAdvance(tempCharacter.advance);
	SetTextureMap(tempCharacter.textureSampler);

	//Update GPU data
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, m_data, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Sets the position of the GUICharacter in pixel-space
void GUICharacter::SetPosition(const vec2& position)
{
	//Set the position of the GUICharacter to the specified position
	m_data[0] = position.x;
	m_data[1] = position.y;

	//Update GPU data
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, m_data, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Sets the scale of the GUICharacter in pixel-space
void GUICharacter::SetScale(const vec2& scale)
{
	//Set the scale of the GUICharacter to the specified scale
	m_data[2] = scale.x;
	m_data[3] = scale.y;

	//Update GPU data
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, m_data, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Sets the bearing of the GUICharacter
void GUICharacter::SetBearing(const vec2& bearing)
{
	//Set the bearing of the GUICharacter to the specified bearing
	m_bearing = bearing;
}

//Sets the advance of the GUICharacter
void GUICharacter::SetAdvance(const vec2& advance)
{
	//Set the advance of the GUICharacter to the specified advance
	m_advance = advance;
}

//Sets the color of the GUICharacter
void GUICharacter::SetColor(const vec4& color)
{
	//Set the color of the GUICharacter to the specified color
	m_data[4] = color.x;
	m_data[5] = color.y;
	m_data[6] = color.z;
	m_data[7] = color.w;

	//Update GPU data
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, m_data, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Sets the texture map for the GUICharacter to the specified texture
//textureFilepath - The location, name and file extension for the texture file
void GUICharacter::SetTextureMap(const string& textureFilepath)
{
	//Load the specified texture
	m_textureMap = TextureManager::LoadTexture(textureFilepath);
}

//Sets the texture map for the GUICharacter to the specified texture
void GUICharacter::SetTextureMap(const unsigned int textureSampler)
{
	//Load the specified texture
	m_textureMap = textureSampler;
}

//Renders the GUICharacter
void GUICharacter::Render()
{
	//Bind the GUICharacter vertex array object
	glBindVertexArray(m_vao);

	//Draw the GUICharacter
	glDrawArrays(GL_POINTS, 0, 1);

	//Unbind the GUICharacters vertex array object
	glBindVertexArray(0);
}