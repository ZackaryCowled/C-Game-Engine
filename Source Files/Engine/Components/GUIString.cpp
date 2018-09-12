//Internal includes
#include "Application.h"

//Creates and initializes a GUIString instance (Default constructor)
GUIString::GUIString()
{
	//Initialize GUIString
	SetPosition(vec2(0.0f, 0.0f));
	SetColor(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	SetText("");
	GUIManager::RegisterGUIString(this);
}

//Creates and initializes a GUIString instance with the specified text
GUIString::GUIString(const string& text)
{
	//Initialize GUIString
	SetPosition(vec2(0.0f, 0.0f));
	SetColor(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	SetText(text);
	GUIManager::RegisterGUIString(this);
}

//Releases the GUIStrings resources
GUIString::~GUIString()
{
	//Clear the GUIString character container
	m_characterContainer.clear();

	//Unregister the GUIString
	GUIManager::UnregisterGUIString(this);
}

//Returns a pointer to the GUICharacter at the specified index in the GUIStrings character container
GUICharacter* GUIString::GetCharacterAt(const unsigned int index)
{
	//Return the character at the specified index in the GUIStrings character container
	return m_characterContainer[index].get();
}

//Returns the number of characters in the GUIString
const unsigned int GUIString::GetCharacterCount()
{
	//Return the number of characters in the GUIStrings character container
	return (unsigned int)m_characterContainer.size();
}

//Returns the GUIStrings text
string GUIString::GetText()
{
	//Return the GUIStrings text
	return m_text;
}

//Returns the GUIStrings position
vec2 GUIString::GetPosition()
{
	//Return the GUIStrings position
	return m_position;
}

//Returns the GUIStrings color
vec4 GUIString::GetColor()
{
	//Return the GUIStrings color
	return m_color;
}

//Sets the GUIStrings text to the specified text
void GUIString::SetText(const string& text)
{
	//Set the GUIStrings text to the specified text
	m_text = text;

	//Clear the GUIStrings character container
	m_characterContainer.clear();

	//For each character in the GUIStrings text
	for (unsigned int characterIndex = 0; characterIndex < m_text.length(); ++characterIndex)
	{
		//Add character to the character container
		m_characterContainer.push_back(shared_ptr<GUICharacter>(new GUICharacter(text[characterIndex])));
	}

	//Update the characters position and color
	SetPosition(GetPosition());
	SetColor(GetColor());
}

//Sets the GUIStrings position to the specified position
void GUIString::SetPosition(const vec2& position)
{
	//Set the GUIStrings position to the specified position
	m_position = position;

	//Create intermediary attributes
	vec2 offset = position;

	//For each character in the GUIStrings character container
	for (unsigned int characterIndex = 0; characterIndex < m_characterContainer.size(); ++characterIndex)
	{
		//Set the characters position
		m_characterContainer[characterIndex]->SetPosition(offset + m_characterContainer[characterIndex]->GetBearing());

		//Calculate intermediary attributes
		offset += m_characterContainer[characterIndex]->GetAdvance();
	}
}

//Sets the GUIStrings color to the specified color
void GUIString::SetColor(const vec4& color)
{
	//Set the GUIStrings color to the specified color
	m_color = color;

	//For each character in the GUIStrings character container
	for (unsigned int characterIndex = 0; characterIndex < m_characterContainer.size(); ++characterIndex)
	{
		//Set the characters color
		m_characterContainer[characterIndex]->SetColor(m_color);
	}
}