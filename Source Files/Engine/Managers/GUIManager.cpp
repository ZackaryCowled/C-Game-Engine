//Internal includes
#include "Application.h"

//Initialize static GUIManager attributes
vector<GUIObject*> GUIManager::m_guiObjectContainer = vector<GUIObject*>();
vector<GUIString*> GUIManager::m_guiStringContainer = vector<GUIString*>();

//Returns the position to use based of a reference resolution and position
const vec2 GUIManager::CreatePositionFromReference(const vec2& referenceResolution, const vec2& position)
{
	//Return position based of the reference resolution and position
	return vec2(position.x / referenceResolution.x * WindowManager::GetWindowWidthf(), position.y / referenceResolution.y * WindowManager::GetWindowHeightf());
}

//Returns the scale to use based of a reference resolution and the scale of the image
const vec2 GUIManager::CreateScaleFromReference(const vec2& referenceResolution, const vec2& imageResolution)
{
	//Return scale for image based of the reference resolution and original image resolution
	return vec2(imageResolution.x / referenceResolution.x * WindowManager::GetWindowWidthf(), imageResolution.y / referenceResolution.y * WindowManager::GetWindowHeightf());
}

//Destroys all GUI elements
void GUIManager::DestroyAllGUIElements()
{
	//While there are GUI objects in the applications GUI object container
	while (m_guiObjectContainer.size() > 0)
	{
		//Erase GUI object
		m_guiObjectContainer.erase(m_guiObjectContainer.begin());
	}

	//While there are GUI strings in the applications GUI string container
	while (m_guiStringContainer.size() > 0)
	{
		//Erase GUI string
		m_guiStringContainer.erase(m_guiStringContainer.begin());
	}
}

//Returns the GUIObject at the specified index in the applications GUI object container
GUIObject* GUIManager::GetGUIObjectAt(const unsigned int index)
{
	//Return the GUIObject at the specified index in the applications GUI object container
	return m_guiObjectContainer[index];
}

//Returns the GUIString at the specified index in the applications GUI string container
GUIString* GUIManager::GetGUIStringAt(const unsigned int index)
{
	//Return the GUIString at the specified index in the applications GUI string container
	return m_guiStringContainer[index];
}

//Returns the number of GUIObjects in the applications GUI object container
const unsigned int GUIManager::GetGUIObjectCount()
{
	//Return the number of GUIObjects in the applications GUI object container
	return (unsigned int)m_guiObjectContainer.size();
}

//Returns the number of GUIStrings in the applications GUI object container
const unsigned int GUIManager::GetGUIStringCount()
{
	//Return the number of GUIStrings in the applications GUI string container
	return (unsigned int)m_guiStringContainer.size();
}

//Registers the specified GUI object
void GUIManager::RegisterGUIObject(GUIObject* p_guiObject)
{
	//Register the specified GUIObject
	m_guiObjectContainer.push_back(p_guiObject);
}

//Registers the specified GUI string
void GUIManager::RegisterGUIString(GUIString* p_guiString)
{
	//Register the specified GUIString
	m_guiStringContainer.push_back(p_guiString);
}

//Unregisters the specified GUI object
void GUIManager::UnregisterGUIObject(GUIObject* p_guiObject)
{
	//For each GUIObject in the applications GUIObject container
	for (unsigned int guiObjectIndex = 0; guiObjectIndex < m_guiObjectContainer.size(); ++guiObjectIndex)
	{
		//If the GUIObject is the specified GUIObject
		if (m_guiObjectContainer[guiObjectIndex] == p_guiObject)
		{
			//Erase the GUIObject from the applications GUIObject container
			m_guiObjectContainer.erase(m_guiObjectContainer.begin() + guiObjectIndex);

			//Return from the function
			return;
		}
	}
}

//Unregisters the specified GUI string
void GUIManager::UnregisterGUIString(GUIString* p_guiString)
{
	//For each GUIString in the applications GUI string container
	for (unsigned int guiStringIndex = 0; guiStringIndex < m_guiStringContainer.size(); ++guiStringIndex)
	{
		//If the GUIString is the specified GUIstring
		if (m_guiStringContainer[guiStringIndex] == p_guiString)
		{
			//Erase the GUIString from the applications GUIString container
			m_guiStringContainer.erase(m_guiStringContainer.begin() + guiStringIndex);

			//Return from the function
			return;
		}
	}
}