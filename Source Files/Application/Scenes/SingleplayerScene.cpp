//Internal includes
#include "ApplicationHeaders.h"

//Called on initialization
void SingleplayerScene::Awake()
{
	//Create and configure SingleplayerManager
	GameObject* singleplayerManager = new GameObject();
	singleplayerManager->AddComponent<SingleplayerManager>();
}