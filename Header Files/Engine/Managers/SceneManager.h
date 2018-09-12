//Pragma comments
#pragma once

//External includes
#include <string>

//Using directives
using std::string;

//Singleton object providing various functions for managing the applications scene
class SceneManager
{
public:
	//Loads the specfied scene after erasing any assets in the current scene
	template<class SceneScript> static void LoadScene()
	{
		//Destroy any GameObjects in the current scene
		GameObjectManager::DestroyAllGameObjects();

		//Destroy all GUI elements
		GUIManager::DestroyAllGUIElements();

		//Create scene script
		SceneScript scene;
		scene.Awake();
	}
};