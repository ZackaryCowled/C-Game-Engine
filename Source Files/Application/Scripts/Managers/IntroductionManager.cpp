//Internal includes
#include "ApplicationHeaders.h"

//Called on initialization
void IntroductionManager::Awake()
{
	//Initialize parent
	parent = GetParent();

	//Initialize arphenion logo controller
	arphenionLogoController = shared_ptr<ArphenionLogoController>(new ArphenionLogoController());
	arphenionLogoController->SetParent(parent);
	arphenionLogoController->Awake();

	//Initialize fade manager
	fadeManager = shared_ptr<FadeManager>(new FadeManager());
	fadeManager->RegisterGUIObject(arphenionLogoController->GetArphenionLogo());

	//Initialize state manager
	stateManager = shared_ptr<StateManager>(new StateManager());
	stateManager->SetState(INTRODUCTION_STATE_FADEIN);
}

//Called once per frame
void IntroductionManager::Update()
{
	//Depending on the current state of the introduction
	switch (stateManager->GetState())
	{
		//Fade in state
		case INTRODUCTION_STATE_FADEIN:
		{
			//Fade in introduction
			if (fadeManager->FadeInGUIObjects(0.3f * Time::deltaTime))
			{
				//Set state to fade out
				stateManager->SetState(INTRODUCTION_STATE_FADEOUT);
			}
			break;
		}

		//Fade out state
		case INTRODUCTION_STATE_FADEOUT:
		{
			//Fade out introduction
			if (fadeManager->FadeOutGUIObjects(0.3f * Time::deltaTime))
			{
				//Load MainMenu scene
				SceneManager::LoadScene<MainMenuScene>();
			}
			break;
		}
	}
}