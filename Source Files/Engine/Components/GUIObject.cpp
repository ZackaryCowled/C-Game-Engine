//Internal includes
#include "Application.h"

//External includes
#include <GL\glew.h>

//Creates and initializes a GUIObject instance (Default constructor)
GUIObject::GUIObject()
{
	//Initialize GUIObject instance
	m_data[0] = 0.0f;
	m_data[1] = 0.0f;
	m_data[2] = 0.0f;
	m_data[3] = 0.0f;
	m_data[4] = 1.0f;
	m_data[5] = 1.0f;
	m_data[6] = 1.0f;
	m_data[7] = 1.0f;
	m_data[8] = 0.0f;
	m_data[9] = 0.0f;
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, 10 * sizeof(float), m_data, GL_STREAM_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 10, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (void*)(sizeof(float) * 2));
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (void*)(sizeof(float) * 4));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (void*)(sizeof(float) * 8));
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	SetTextureMap("Textures/Button.png");
	SetType(COMPONENT_TYPE_GUI_OBJECT);
	GUIManager::RegisterGUIObject(this);
}

//Creates and initializes a GUIObject with the specified position and scale in pixel-space
GUIObject::GUIObject(const vec2& position, const vec2& scale)
{
	//Initialize GUIObject instance
	m_data[0] = position.x;
	m_data[1] = position.y;
	m_data[2] = scale.x;
	m_data[3] = scale.y;
	m_data[4] = 1.0f;
	m_data[5] = 1.0f;
	m_data[6] = 1.0f;
	m_data[7] = 1.0f;
	m_data[8] = 0.0f;
	m_data[9] = 0.0f;
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, 10 * sizeof(float), m_data, GL_STREAM_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 10, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (void*)(sizeof(float) * 2));
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (void*)(sizeof(float) * 4));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (void*)(sizeof(float) * 8));
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	SetTextureMap("Textures/Button.png");
	SetType(COMPONENT_TYPE_GUI_OBJECT);
	GUIManager::RegisterGUIObject(this);
}

//Releases the GUIObjects resources
GUIObject::~GUIObject()
{
	//If the GUIObject is valid
	if (m_vao)
	{
		//Delete GPU resources
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_vbo);
		glDeleteTextures(1, &m_textureMap);

		//Unregister GUIObject
		GUIManager::UnregisterGUIObject(this);
	}
}

//Fades in the GUI object
//Function returns true when the GUI object is fully faded in
const bool GUIObject::FadeIn(const float fadeSpeed)
{
	//Flag representing whether the GUI object is fully faded in
	bool fadeStatus = false;

	//Fade in GUI object
	m_data[7] += fadeSpeed;

	//If the GUI object is fully faded in
	if (m_data[7] >= 1.0f)
	{
		//Clamp the GUI objects alpha channel to 1
		m_data[7] = 1.0f;

		//Set the fade status flag
		fadeStatus = true;
	}

	//Update GPU data
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 10, m_data, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Return the fade status
	return fadeStatus;
}

//Fades out the GUI object
//Function returns true when the GUI object is fully faded out
const bool GUIObject::FadeOut(const float fadeSpeed)
{
	//Flag representing whether the GUI object is fully faded out
	bool fadeStatus = false;

	//Fade out GUI object
	m_data[7] -= fadeSpeed;

	//If the GUI object is fully faded out
	if (m_data[7] <= 0.0f)
	{
		//Clamp the GUI objects alpha channel to 0
		m_data[7] = 0.0f;

		//Set the fade status flag
		fadeStatus = true;
	}

	//Update GPU data
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 10, m_data, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Return the fade status
	return fadeStatus;
}

//Returns the position of the GUIObject in pixel-space
vec2 GUIObject::GetPosition()
{
	//Return the GUIObjects position
	return vec2(m_data[0], m_data[1]);
}

//Returns the scale of the GUIObject in pixel-space
vec2 GUIObject::GetScale()
{
	//Return the GUIObjects scale
	return vec2(m_data[2], m_data[3]);
}

//Returns the color of the GUIObject
vec4 GUIObject::GetColor()
{
	//Return the GUIObject color
	return vec4(m_data[4], m_data[5], m_data[6], m_data[7]);
}

//Returns the texture offset for the GUIObject
vec2 GUIObject::GetTextureOffset()
{
	//Return the GUIObject texture offset
	return vec2(m_data[8], m_data[9]);
}

//Returns the texture map for the GUIObject
unsigned int GUIObject::GetTextureMap()
{
	//Return the GUIObjects texture map
	return m_textureMap;
}

//Sets the position of the GUIObject in pixel-space
void GUIObject::SetPosition(const vec2& position)
{
	//Set the position of the GUIObject to the specified position
	m_data[0] = position.x;
	m_data[1] = position.y;

	//Update GPU data
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 10, m_data, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Sets the scale of the GUIObject in pixel-space
void GUIObject::SetScale(const vec2& scale)
{
	//Set the scale of the GUIObject to the specified scale
	m_data[2] = scale.x;
	m_data[3] = scale.y;

	//Update GPU data
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 10, m_data, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Sets the color of the GUIObject
void GUIObject::SetColor(const vec4& color)
{
	//Set the color of the GUIObject to the specified color
	m_data[4] = color.x;
	m_data[5] = color.y;
	m_data[6] = color.z;
	m_data[7] = color.w;

	//Update GPU data
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 10, m_data, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Sets ther texture offset for the GUIObject
void GUIObject::SetTextureOffset(const vec2& textureOffset)
{
	//Set the texture offset of the GUIObject to the specified texture offset
	m_data[8] = textureOffset.x;
	m_data[9] = textureOffset.y;

	//Update GPU data
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 10, m_data, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Sets the texture map for the GUIObject to the specified texture
//textureFilepath - The location, name and file extension for the texture file
void GUIObject::SetTextureMap(const string& textureFilepath)
{
	//Load the specified texture
	m_textureMap = TextureManager::LoadTexture(textureFilepath);
}

//Sets the texture map for the GUIObject to the specified texture
void GUIObject::SetTextureMap(const unsigned int textureSampler)
{
	//Load the specified texture
	m_textureMap = textureSampler;
}

//Moves the GUI object by the specified translation
void GUIObject::Translate(const vec2& translation)
{
	//Translate the position of the GUIObject to the specified translation
	m_data[0] += translation.x;
	m_data[1] += translation.y;

	//Update GPU data
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 10, m_data, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Renders the GUIObject
void GUIObject::Render()
{
	//Bind the GUIObjects vertex array object
	glBindVertexArray(m_vao);

	//Draw the GUIObject
	glDrawArrays(GL_POINTS, 0, 1);

	//Unbind the GUIObjects vertex array object
	glBindVertexArray(0);
}