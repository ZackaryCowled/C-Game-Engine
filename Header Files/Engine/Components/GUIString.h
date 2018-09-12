//Pragma comments
#pragma once

//Internal includes
#include "Component.h"
#include "GUICharacter.h"

//External includes
#include <glm\glm.hpp>
#include <memory>
#include <string>
#include <vector>

//Using directives
using namespace glm;
using std::shared_ptr;
using std::string;
using std::vector;

//Class encapsulating any number of GUI Characters as a line of text
class GUIString : public Component
{
public:
	//Creates and initializes a GUIString instance (Default constructor)
	GUIString();

	//Creates and initializes a GUIString instance with the specified text
	GUIString(const string& text);

	//Releases the GUIStrings resources
	~GUIString();

	//Returns a pointer to the GUICharacter at the specified index in the GUIStrings character container
	GUICharacter* GetCharacterAt(const unsigned int index);

	//Returns the number of characters in the GUIString
	const unsigned int GetCharacterCount();

	//Returns the GUIStrings text
	string GetText();

	//Returns the GUIStrings position
	vec2 GetPosition();

	//Returns the GUIStrings color
	vec4 GetColor();

	//Sets the GUIStrings text to the specified text
	void SetText(const string& text);

	//Sets the GUIStrings position to the specified position
	void SetPosition(const vec2& position);

	//Sets the GUIStrings color to the specified color
	void SetColor(const vec4& color);

private:
	//Container for storing the GUIStrings characters
	vector<shared_ptr<GUICharacter>> m_characterContainer;

	//The GUIStrings text
	string m_text;

	//The GUIStrings position
	vec2 m_position;

	//The GUIStrings color
	vec4 m_color;
};