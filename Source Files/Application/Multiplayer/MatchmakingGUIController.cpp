//Internal includes
#include "ApplicationHeaders.h"

//Called on initialization
void MatchmakingGUIController::Awake()
{
	//Initialize parent
	parent = GetParent();

	//Initialize connecting to server label
	connectingToServerLabel = parent->AddComponent<GUIObject>();
	connectingToServerLabel->SetTextureMap("Textures/ConnectingToServerLabel.png");
	connectingToServerLabel->SetScale(GUIManager::CreateScaleFromReference(vec2(1920.0f, 1080.0f), vec2(411.0f, 41.0f)));
	connectingToServerLabel->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), vec2(729.5f, 519.5f)));
	connectingToServerLabel->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

	//Initialize waiting for game label
	waitingForGameLabel = parent->AddComponent<GUIObject>();
	waitingForGameLabel->SetTextureMap("Textures/WaitingForGameLabel.png");
	waitingForGameLabel->SetScale(GUIManager::CreateScaleFromReference(vec2(1920.0f, 1080.0f), vec2(340.0f, 43.0f)));
	waitingForGameLabel->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), vec2(800.0f, 518.5f)));
	waitingForGameLabel->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

	//Initialize loading icon 1
	loadingIcon1 = parent->AddComponent<GUIObject>();
	loadingIcon1->SetTextureMap("Textures/LoadingIcon01.png");
	loadingIcon1->SetScale(GUIManager::CreateScaleFromReference(vec2(1920.0f, 1080.0f), vec2(40.0f, 40.0f)));
	loadingIcon1->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), vec2(1150.0f, 520.0f)));
	loadingIcon1->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

	//Initialize loading icon 2
	loadingIcon2 = parent->AddComponent<GUIObject>();
	loadingIcon2->SetTextureMap("Textures/LoadingIcon02.png");
	loadingIcon2->SetScale(GUIManager::CreateScaleFromReference(vec2(1920.0f, 1080.0f), vec2(40.0f, 40.0f)));
	loadingIcon2->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), vec2(1150.0f, 520.0f)));
	loadingIcon2->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

	//Initialize loading icon 3
	loadingIcon3 = parent->AddComponent<GUIObject>();
	loadingIcon3->SetTextureMap("Textures/LoadingIcon03.png");
	loadingIcon3->SetScale(GUIManager::CreateScaleFromReference(vec2(1920.0f, 1080.0f), vec2(40.0f, 40.0f)));
	loadingIcon3->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), vec2(1150.0f, 520.0f)));
	loadingIcon3->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

	//Initialize loading icon 4
	loadingIcon4 = parent->AddComponent<GUIObject>();
	loadingIcon4->SetTextureMap("Textures/LoadingIcon04.png");
	loadingIcon4->SetScale(GUIManager::CreateScaleFromReference(vec2(1920.0f, 1080.0f), vec2(40.0f, 40.0f)));
	loadingIcon4->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), vec2(1150.0f, 520.0f)));
	loadingIcon4->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

	//Initialize loading icon 5
	loadingIcon5 = parent->AddComponent<GUIObject>();
	loadingIcon5->SetTextureMap("Textures/LoadingIcon05.png");
	loadingIcon5->SetScale(GUIManager::CreateScaleFromReference(vec2(1920.0f, 1080.0f), vec2(40.0f, 40.0f)));
	loadingIcon5->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), vec2(1150.0f, 520.0f)));
	loadingIcon5->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

	//Initialize loading icon 6
	loadingIcon6 = parent->AddComponent<GUIObject>();
	loadingIcon6->SetTextureMap("Textures/LoadingIcon06.png");
	loadingIcon6->SetScale(GUIManager::CreateScaleFromReference(vec2(1920.0f, 1080.0f), vec2(40.0f, 40.0f)));
	loadingIcon6->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), vec2(1150.0f, 520.0f)));
	loadingIcon6->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

	//Initialize loading icon 7
	loadingIcon7 = parent->AddComponent<GUIObject>();
	loadingIcon7->SetTextureMap("Textures/LoadingIcon07.png");
	loadingIcon7->SetScale(GUIManager::CreateScaleFromReference(vec2(1920.0f, 1080.0f), vec2(40.0f, 40.0f)));
	loadingIcon7->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), vec2(1150.0f, 520.0f)));
	loadingIcon7->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

	//Initialize loading icon 8
	loadingIcon8 = parent->AddComponent<GUIObject>();
	loadingIcon8->SetTextureMap("Textures/LoadingIcon08.png");
	loadingIcon8->SetScale(GUIManager::CreateScaleFromReference(vec2(1920.0f, 1080.0f), vec2(40.0f, 40.0f)));
	loadingIcon8->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), vec2(1150.0f, 520.0f)));
	loadingIcon8->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

	//Initialize current loading icon
	currentLoadingIcon = 0;

	//Initialize timer
	timer = 0.0f;
}

//Called once per frame
void MatchmakingGUIController::Update()
{
	//Increment timer
	timer += Time::deltaTime;

	//If the timer is more or equal to 0.1
	if (timer >= 0.1)
	{
		//Update timer
		timer -= 0.1f;

		//Increment the current loading icon
		++currentLoadingIcon;

		//If the current loading icon is not valid
		if (currentLoadingIcon > 7)
		{
			//Reset current loading icon
			currentLoadingIcon = 0;
		}

		//Depending on the current loading icon being displayed
		switch (currentLoadingIcon)
		{
			//Loading icon 1
			case 0:
			{
				//Hide loading icon 8
				loadingIcon8->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

				//Show loading icon 1
				loadingIcon1->SetColor(vec4(1.0f, 1.0f, 1.0f, 1.0f));
				break;
			}

			//Loading icon 2
			case 1:
			{
				//Hide loading icon 1
				loadingIcon1->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

				//Show loading icon 2
				loadingIcon2->SetColor(vec4(1.0f, 1.0f, 1.0f, 1.0f));
				break;
			}

			//Loading icon 3
			case 2:
			{
				//Hide loading icon 2
				loadingIcon2->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

				//Show loading icon 3
				loadingIcon3->SetColor(vec4(1.0f, 1.0f, 1.0f, 1.0f));
				break;
			}

			//Loading icon 4
			case 3:
			{
				//Hide loading icon 3
				loadingIcon3->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

				//Show loading icon 4
				loadingIcon4->SetColor(vec4(1.0f, 1.0f, 1.0f, 1.0f));
				break;
			}

			//Loading icon 5
			case 4:
			{
				//Hide loading icon 4
				loadingIcon4->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

				//Show loading icon 5
				loadingIcon5->SetColor(vec4(1.0f, 1.0f, 1.0f, 1.0f));
				break;
			}

			//Loading icon 6
			case 5:
			{
				//Hide loading icon 5
				loadingIcon5->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

				//Show loading icon 6
				loadingIcon6->SetColor(vec4(1.0f, 1.0f, 1.0f, 1.0f));
				break;
			}

			//Loading icon 7
			case 6:
			{
				//Hide loading icon 6
				loadingIcon6->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

				//Show loading icon 7
				loadingIcon7->SetColor(vec4(1.0f, 1.0f, 1.0f, 1.0f));
				break;
			}

			//Loading icon 8
			case 7:
			{
				//Hide loading icon 7
				loadingIcon7->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

				//Show loading icon 8
				loadingIcon8->SetColor(vec4(1.0f, 1.0f, 1.0f, 1.0f));
				break;
			}
		}
	}
}

//Hides the connecting to server label
void MatchmakingGUIController::HideConnectingToServerLabel()
{
	//Hide the connecting to server label
	connectingToServerLabel->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));
}

//Hides the waiting for game label
void MatchmakingGUIController::HideWaitingForGameLabel()
{
	//Hide the waiting for game label
	waitingForGameLabel->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));
}

//Hides the loading icon
void MatchmakingGUIController::HideLoadingIcon()
{
	//Hide the loading icon
	loadingIcon1->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));
	loadingIcon2->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));
	loadingIcon3->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));
	loadingIcon4->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));
	loadingIcon5->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));
	loadingIcon6->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));
	loadingIcon7->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));
	loadingIcon8->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));
}

//Shows the connecting to server label
void MatchmakingGUIController::ShowConnectingToServerLabel()
{
	//Show the connecting to server label
	connectingToServerLabel->SetColor(vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

//Shows the waiting for game label
void MatchmakingGUIController::ShowWaitingForGameLabel()
{
	//Show the waiting for game label
	waitingForGameLabel->SetColor(vec4(1.0f, 1.0f, 1.0f, 1.0f));
}