//Pragma comments
#pragma once

//External includes
#include <string>
#include <vector>
#include <memory>

//Using directives
using std::shared_ptr;
using std::string;
using std::vector;

//Forward declarations
class GameObject;

//Singleton classfor managing the applications GameObjects
class GameObjectManager
{
public:
	//Destroys all GameObjects managed by the GameObject manager
	static void DestroyAllGameObjects();

	//Returns a pointer to the first GameObject found with the specified name
	//If no GameObject exist with the specified name the function returns a null pointer
	static GameObject* FindGameObjectWithName(const string& name);

	//Returns a pointer to the first GameObject found with the specified tag
	//If no GameObject exists with the specified tag the function returns a null pointer
	static GameObject* FindGameObjectWithTag(const string& tag);

	//Returns the number of GameObjects managed by the GameObject manager
	static const unsigned int GetGameObjectCount();

	//Returns the GameObject at the specified index in the applications GameObject container
	static GameObject* GetGameObjectAt(const unsigned int index);

	//Registers the specified GameObject
	static void RegisterGameObject(GameObject* p_gameObject);

	//Unregisters the specified GameObject
	static void UnregisterGameObject(GameObject* p_gameObject);

	//Updates all the GameObjects managed by the GameObject manager
	static void UpdateAllGameObjects();

private:
	//Container for storing the applications GameObject instances
	static vector<GameObject*> m_gameObjectContainer;
};