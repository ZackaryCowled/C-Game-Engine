//Internal includes
#include "ApplicationHeaders.h"

//Called on initialization
void IntroductionScene::Awake()
{
	//Create and configure IntroductionManager
	GameObject* introductionManager = new GameObject();
	introductionManager->AddComponent<IntroductionManager>();
}