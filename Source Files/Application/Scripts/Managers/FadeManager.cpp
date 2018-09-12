//Internal includes
#include "ApplicationHeaders.h"

//Fades in all registered GUI objects
//Function returns true when all registered GUI objects are fully faded in
const bool FadeManager::FadeInGUIObjects(const float fadeSpeed)
{
	//Flag representing whether all registered GUI objects are fully faded in
	bool fadeStatus = true;

	//For each registered GUI object
	for (unsigned int guiObjectIndex = 0; guiObjectIndex < guiObjectContainer.size(); ++guiObjectIndex)
	{
		//Fade in the GUI object
		if (!guiObjectContainer[guiObjectIndex]->FadeIn(fadeSpeed))
		{
			//Set the fade status flag to false
			fadeStatus = false;
		}
	}

	//Return the fade status
	return fadeStatus;
}

//Fades out all registered GUI objects
//Function reutrns true when all registered GUI objects are fully faded out
const bool FadeManager::FadeOutGUIObjects(const float fadeSpeed)
{
	//Flag representing whether all registered GUI objects are fully faded out
	bool fadeStatus = true;

	//For each registered GUI object
	for (unsigned int guiObjectIndex = 0; guiObjectIndex < guiObjectContainer.size(); ++guiObjectIndex)
	{
		//Fade out the GUI object
		if (!guiObjectContainer[guiObjectIndex]->FadeOut(fadeSpeed))
		{
			//Set the fade status flag to false
			fadeStatus = false;
		}
	}

	//Return the fade status
	return fadeStatus;
}

//Registers the specified GUI object
void FadeManager::RegisterGUIObject(GUIObject* p_guiObject)
{
	//Register the specified GUI object
	guiObjectContainer.push_back(p_guiObject);
}

//Unregisters the specified GUI object
void FadeManager::UnregisterGUIObject(GUIObject* p_guiObject)
{
	//For each registered GUI object
	for (unsigned int guiObjectIndex = 0; guiObjectIndex < guiObjectContainer.size(); ++guiObjectIndex)
	{
		//If the address of the registered GUI object is the same as the specified GUI object
		if (guiObjectContainer[guiObjectIndex] == p_guiObject)
		{
			//Erase the GUI object from the GUI object container (Unregister GUI object)
			guiObjectContainer.erase(guiObjectContainer.begin() + guiObjectIndex);

			//Return from the function
			return;
		}
	}
}