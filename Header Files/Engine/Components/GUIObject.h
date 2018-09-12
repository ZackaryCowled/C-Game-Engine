//Pragma comments
#pragma once

//Internal includes
#include "Component.h"

//External includes
#include <string>

//Using directives
using std::string;

//Base object for building GUI components from
class GUIObject : public Component
{
public:
	//Creates and initializes a GUIObject instance (Default constructor)
	GUIObject();

	//Creates and initializes a GUIObject with the specified position and scale in pixel-space
	GUIObject(const vec2& position, const vec2& scale);

	//Releases the GUIObjects resources
	~GUIObject();

	//Fades in the GUI object
	//Function returns true when the GUI object is fully faded in
	const bool FadeIn(const float fadeSpeed);

	//Fades out the GUI object
	//Function returns true when the GUI object is fully faded out
	const bool FadeOut(const float fadeSpeed);

	//Returns the position of the GUIObject in pixel-space
	vec2 GetPosition();

	//Returns the scale of the GUIObject in pixel-space
	vec2 GetScale();

	//Returns the color of the GUIObject
	vec4 GetColor();

	//Returns the texture offset for the GUIObject
	vec2 GetTextureOffset();

	//Returns the texture map for the GUIObject
	unsigned int GetTextureMap();

	//Sets the position of the GUIObject in pixel-space
	void SetPosition(const vec2& position);

	//Sets the scale of the GUIObject in pixel-space
	void SetScale(const vec2& scale);
	
	//Sets the color of the GUIObject
	void SetColor(const vec4& color);

	//Sets ther texture offset for the GUIObject
	void SetTextureOffset(const vec2& textureOffset);

	//Sets the texture map for the GUIObject to the specified texture
	//textureFilepath - The location, name and file extension for the texture file
	void SetTextureMap(const string& textureFilepath);

	//Sets the texture map for the GUIObject to the specified texture
	void SetTextureMap(const unsigned int textureSampler);

	//Moves the GUI object by the specified translation
	void Translate(const vec2& translation);

	//Renders the GUIObject
	void Render();

private:
	//The GUIObjects data
	float m_data[10];

	//The GUIObjects vertex array object
	unsigned int m_vao;

	//The GUIObjects vertex buffer object
	unsigned int m_vbo;

	//The GUIObjects texture map
	unsigned int m_textureMap;
};