//Pragma comments
#pragma once

//External incldues
#include <vector>

//Using directives
using std::vector;

//Forward declarations
class GUIObject;
class GUIString;

//Singleton class for managing the applicaitions GUI objects
class GUIManager
{
public:
	//Returns the position to use based of a reference resolution and position
	static const vec2 CreatePositionFromReference(const vec2& referenceResolution, const vec2& position);

	//Returns the scale to use based of a reference resolution and the scale of the image
	static const vec2 CreateScaleFromReference(const vec2& referenceResolution, const vec2& imageResolution);

	//Destroys all GUI elements
	static void DestroyAllGUIElements();

	//Returns the GUIObject at the specified index in the applications GUI object container
	static GUIObject* GetGUIObjectAt(const unsigned int index);

	//Returns the GUIString at the specified index in the applications GUI string container
	static GUIString* GetGUIStringAt(const unsigned int index);

	//Returns the number of GUIObjects in the applications GUI object container
	static const unsigned int GetGUIObjectCount();

	//Returns the number of GUIStrings in the applications GUI object container
	static const unsigned int GetGUIStringCount();

	//Registers the specified GUI object
	static void RegisterGUIObject(GUIObject* p_guiObject);

	//Registers the specified GUI string
	static void RegisterGUIString(GUIString* p_guiString);

	//Unregisters the specified GUI object
	static void UnregisterGUIObject(GUIObject* p_guiObject);

	//Unregisters the specified GUI string
	static void UnregisterGUIString(GUIString* p_guiString);

private:
	//Container for storing the applications GUI objects
	static vector<GUIObject*> m_guiObjectContainer;

	//Container for storing the applications GUI strings
	static vector<GUIString*> m_guiStringContainer;
};