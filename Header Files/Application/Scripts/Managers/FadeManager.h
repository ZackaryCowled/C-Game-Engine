//Pragma comments
#pragma once

//Internal includes
#include "Application.h"

//Fade Manager Script
class FadeManager : public Script
{
public:
	//Fades in all registered GUI objects
	//Function returns true when all registered GUI objects are fully faded in
	const bool FadeInGUIObjects(const float fadeSpeed);

	//Fades out all registered GUI objects
	//Function reutrns true when all registered GUI objects are fully faded out
	const bool FadeOutGUIObjects(const float fadeSpeed);

	//Registers the specified GUI object
	void RegisterGUIObject(GUIObject* p_guiObject);

	//Unregisters the specified GUI object
	void UnregisterGUIObject(GUIObject* p_guiObject);

private:
	//Container for storing GUI objects
	vector<GUIObject*> guiObjectContainer;
};