//Internal includes
#include "ApplicationHeaders.h"

//Called on initialization
void MultiplayerScene::Awake()
{
	//Create and configure MultiplayerManager
	GameObject* multiplayerManager = new GameObject();
	multiplayerManager->AddComponent<MultiplayerManager>();
}