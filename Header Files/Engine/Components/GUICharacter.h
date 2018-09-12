//Pragma comments
#pragma once

//Internal includes
#include "Component.h"

//External includes
#include <glm\glm.hpp>

//Using directives
using namespace glm;

//Base object for building GUI strings from
class GUICharacter : public Component
{
public:
	//Creates and initializes a GUICharacter instance (Default constructor)
	GUICharacter();

	//Creates and initializes a GUICharacter instance using the specified character
	GUICharacter(const unsigned char character);

	//Releases GUICharacter resources
	~GUICharacter();

	//Returns the character the GUICharacter is using
	const unsigned char GetCharacter();

	//Returns the position of the GUICharacter in pixel-space
	vec2 GetPosition();

	//Returns the scale of the GUICharacter in pixel-space
	vec2 GetScale();

	//Returns the characters bearing
	vec2 GetBearing();

	//Returns the characters advance
	vec2 GetAdvance();

	//Returns the color of the GUICharacter
	vec4 GetColor();

	//Returns the texture map for the GUICharacter
	unsigned int GetTextureMap();

	//Sets the character for the GUICharacter to use
	void SetCharacter(const unsigned char character);

	//Sets the position of the GUICharacter in pixel-space
	void SetPosition(const vec2& position);

	//Sets the scale of the GUICharacter in pixel-space
	void SetScale(const vec2& scale);

	//Sets the bearing of the GUICharacter
	void SetBearing(const vec2& bearing);

	//Sets the advance of the GUICharacter
	void SetAdvance(const vec2& advance);

	//Sets the color of the GUICharacter
	void SetColor(const vec4& color);

	//Sets the texture map for the GUICharacter to the specified texture
	//textureFilepath - The location, name and file extension for the texture file
	void SetTextureMap(const string& textureFilepath);

	//Sets the texture map for the GUICharacter to the specified texture
	void SetTextureMap(const unsigned int textureSampler);

	//Renders the GUICharacter
	void Render();

private:
	//The character the GUICharacter is using
	unsigned char m_character;

	//The GUICharacter data
	float m_data[8];

	//The GUICharacters bearing
	vec2 m_bearing;

	//The GUICharacters advance
	vec2 m_advance;

	//The GUICharacter vertex array object
	unsigned int m_vao;

	//The GUICharacter vertex buffer object
	unsigned int m_vbo;

	//The GUICharacter texture map
	unsigned int m_textureMap;
};