//Internal includes
#include "GameObjectManager.h"
#include "Application.h"

//Initializes the GameObject managers GameObject container
vector<GameObject*> InitializeGameObjectContainer()
{
	//Return default GameObject container
	return vector<GameObject*>();
}

//Initialize static GameObject manager attributes
vector<GameObject*> GameObjectManager::m_gameObjectContainer(InitializeGameObjectContainer());

//Destroys all GameObjects managed by the GameObject manager
void GameObjectManager::DestroyAllGameObjects()
{
	//While there are one or more GameObjects in the applications GameObject container
	while (m_gameObjectContainer.size() > 0)
	{
		//If the GameObject is valid
		if (m_gameObjectContainer[0] != nullptr)
		{
			//Destroy the GameObject
			m_gameObjectContainer[0]->Destroy();
		}
	}
}

//Returns a pointer to the first GameObject found with the specified name
//If no GameObject exist with the specified name the function returns a null pointer
GameObject* GameObjectManager::FindGameObjectWithName(const string& name)
{
	//For each GameObject in the applications GameObject container
	for (unsigned int gameObjectIndex = 0; gameObjectIndex < m_gameObjectContainer.size(); gameObjectIndex++)
	{
		//If the GameObject has the specified name
		if (m_gameObjectContainer[gameObjectIndex]->GetName() == name)
		{
			//Return a pointer to the GameObject
			return m_gameObjectContainer[gameObjectIndex];
		}
	}

	//No GameObject has the specified name
	return nullptr;
}

//Returns a pointer to the first GameObject found with the specified tag
//If no GameObject exists with the specified tag the function returns a null pointer
GameObject* GameObjectManager::FindGameObjectWithTag(const string& tag)
{
	//For each GameObject in the applications GameObject container
	for (unsigned int gameObjectIndex = 0; gameObjectIndex < m_gameObjectContainer.size(); gameObjectIndex++)
	{
		//If the GameObject has the specified tag
		if (m_gameObjectContainer[gameObjectIndex]->GetTag() == tag)
		{
			//Return a pointer to the GameObject
			return m_gameObjectContainer[gameObjectIndex];
		}
	}

	//No GameObject has the specified tag
	return nullptr;
}

//Returns the number of GameObjects managed by the GameObject manager
const unsigned int GameObjectManager::GetGameObjectCount()
{
	//Return the number of GameObjects managed by the GameObject manager
	return (unsigned int)m_gameObjectContainer.size();
}

//Returns the GameObject at the specified index in the applications GameObject container
GameObject* GameObjectManager::GetGameObjectAt(const unsigned int index)
{
	//Return the GameObject at the specified index in the applications GameObject container
	return m_gameObjectContainer[index];
}

//Registers the specified GameObject
void GameObjectManager::RegisterGameObject(GameObject* p_gameObject)
{
	//Register the specified GameObject
	m_gameObjectContainer.push_back(p_gameObject);
}

//Unregisters the specified GameObject
void GameObjectManager::UnregisterGameObject(GameObject* p_gameObject)
{
	//For each GameObject in the applications GameObject container
	for (unsigned int gameObjectIndex = 0; gameObjectIndex < m_gameObjectContainer.size(); gameObjectIndex++)
	{
		//If the GameObject is the specified GameObject
		if (m_gameObjectContainer[gameObjectIndex] == p_gameObject)
		{
			//Erase the GameObject from the applications GameObject container
			m_gameObjectContainer.erase(m_gameObjectContainer.begin() + gameObjectIndex);

			//Return from the function
			return;
		}
	}
}

//Updates all the GameObjects managed by the GameObject manager
void GameObjectManager::UpdateAllGameObjects()
{
	//For each GameObject in the applications GameObject container
	for (unsigned int gameObjectIndex = 0; gameObjectIndex < m_gameObjectContainer.size(); ++gameObjectIndex)
	{
		//Update the GameObject
		m_gameObjectContainer[gameObjectIndex]->Update();
	}

	//For each GameObject in the applications GameObject container
	for (unsigned int gameObjectIndex = 0; gameObjectIndex < m_gameObjectContainer.size(); ++gameObjectIndex)
	{
		//Late update the GameObject
		m_gameObjectContainer[gameObjectIndex]->LateUpdate();
	}
}