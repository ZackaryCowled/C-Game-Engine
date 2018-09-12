//Internal includes
#include "ApplicationHeaders.h"

//Called on initialization
void MainMenuManager::Awake()
{
	//Initialize parent
	parent = GetParent();

	//Initialize background controller
	backgroundController = shared_ptr<BackgroundController>(new BackgroundController());
	backgroundController->SetParent(parent);
	backgroundController->Awake();


	//Initialize pong label controller
	pongLabelController = shared_ptr<PongLabelController>(new PongLabelController());
	pongLabelController->SetParent(parent);
	pongLabelController->Awake();

	//Initialize singleplayer button controller
	singleplayerButtonController = shared_ptr<ButtonController>(new ButtonController());
	singleplayerButtonController->SetParent(parent);
	singleplayerButtonController->Awake();
	singleplayerButtonController->SetTexture("Textures/SingleplayerLabelUnselected.png");
	singleplayerButtonController->SetScale(GUIManager::CreateScaleFromReference(vec2(1920.0f, 1080.0f), vec2(295.0f, 62.0f)));
	singleplayerButtonController->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), vec2(812.0f, 374.0f)));
	singleplayerButtonController->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

	//Initialize multiplayer button controller
	multiplayerButtonController = shared_ptr<ButtonController>(new ButtonController());
	multiplayerButtonController->SetParent(parent);
	multiplayerButtonController->Awake();
	multiplayerButtonController->SetTexture("Textures/MultiplayerLabelUnselected.png");
	multiplayerButtonController->SetScale(GUIManager::CreateScaleFromReference(vec2(1920.0f, 1080.0f), vec2(278.0f, 62.0f)));
	multiplayerButtonController->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), vec2(821.0f, 518.0f)));
	multiplayerButtonController->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

	//Initialize exit button controller
	exitButtonController = shared_ptr<ButtonController>(new ButtonController());
	exitButtonController->SetParent(parent);
	exitButtonController->Awake();
	exitButtonController->SetTexture("Textures/ExitLabelUnselected.png");
	exitButtonController->SetScale(GUIManager::CreateScaleFromReference(vec2(1920.0f, 1080.0f), vec2(91.0f, 50.0f)));
	exitButtonController->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), vec2(914.5f, 662.0f)));
	exitButtonController->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));
		
	//Initialize mouse controller
	mouseController = shared_ptr<MouseController>(new MouseController());
	mouseController->SetParent(parent);
	mouseController->Awake();

	//Initialize fade manager
	fadeManager = shared_ptr<FadeManager>(new FadeManager());
	fadeManager->RegisterGUIObject(backgroundController->GetBackground());
	fadeManager->RegisterGUIObject(pongLabelController->GetPongLabel());
	fadeManager->RegisterGUIObject(singleplayerButtonController->GetButton());
	fadeManager->RegisterGUIObject(multiplayerButtonController->GetButton());
	fadeManager->RegisterGUIObject(exitButtonController->GetButton());
	fadeManager->RegisterGUIObject(mouseController->GetMouse());

	//Initialize state manager
	stateManager = shared_ptr<StateManager>(new StateManager());
	stateManager->SetState(MAINMENU_STATE_FADEIN);

	//Initialize selected button
	selectedButton = 0;
}

//Called once per frame
void MainMenuManager::Update()
{
	//Update background
	backgroundController->Update();

	//Update mouse
	mouseController->Update();

	//Depending on the current state of the mainmenu
	switch (stateManager->GetState())
	{
		//Fade in state
		case MAINMENU_STATE_FADEIN:
		{
			//Fade in mainmenu
			if (fadeManager->FadeInGUIObjects(0.5f * Time::deltaTime))
			{
				//Set state to selection
				stateManager->SetState(MAINMENU_STATE_SELECTION);
			}
			break;
		}

		//Menu 1 state
		case MAINMENU_STATE_SELECTION:
		{
			//If the mouse is hovering over the singleplayer button
			if (singleplayerButtonController->IsMouseHovering())
			{
				//Set singleplayer button texture to selected texture
				singleplayerButtonController->SetTexture("Textures/SingleplayerLabelSelected.png");

				//If the left mouse button is down
				if (Input::GetMouseButton(EVENT_TRIGGER_MOUSE_LEFT))
				{
					//Select singleplayer button
					selectedButton = MAINMENU_BUTTON_SINGEPLAYER;

					//Set state to fade out
					stateManager->SetState(MAINMENU_STATE_FADEOUT);
				}
			}
			//Otherwise
			else
			{
				//Set singleplayer button texture to unselected texture
				singleplayerButtonController->SetTexture("Textures/SingleplayerLabelUnselected.png");
			}

			//If the mouse is hovering over the multiplayer button
			if (multiplayerButtonController->IsMouseHovering())
			{
				//Set multiplayer button texture to selected texture
				multiplayerButtonController->SetTexture("Textures/MultiplayerLabelSelected.png");

				//If the left mouse button is down
				if (Input::GetMouseButton(EVENT_TRIGGER_MOUSE_LEFT))
				{
					//Select multiplayer button
					selectedButton = MAINMENU_BUTTON_MULTIPLAYER;

					//Set state to fade out
					stateManager->SetState(MAINMENU_STATE_FADEOUT);
				}
			}
			//Otherwise
			else
			{
				//Set multiplayer button texture to unselected texture
				multiplayerButtonController->SetTexture("Textures/MultiplayerLabelUnselected.png");
			}

			//If the mouse is hovering over the exit button
			if (exitButtonController->IsMouseHovering())
			{
				//Set exit button texture to selected texture
				exitButtonController->SetTexture("Textures/ExitLabelSelected.png");

				//If the left mouse button is down
				if (Input::GetMouseButton(EVENT_TRIGGER_MOUSE_LEFT))
				{
					//Select exit button
					selectedButton = MAINMENU_BUTTON_EXIT;

					//Set state to fade out
					stateManager->SetState(MAINMENU_STATE_FADEOUT);
				}
			}
			//Otherwise
			else
			{
				//Set exit button texture to unselected texture
				exitButtonController->SetTexture("Textures/ExitLabelUnselected.png");
			}
			break;
		}

		//Fade out state
		case MAINMENU_STATE_FADEOUT:
		{
			//Fade out mainmenu
			if (fadeManager->FadeOutGUIObjects(0.5f * Time::deltaTime))
			{
				//Depending on the button selected
				switch (selectedButton)
				{
					//Singleplayer button
					case MAINMENU_BUTTON_SINGEPLAYER:
					{
						//Load singleplayer scene
						SceneManager::LoadScene<SingleplayerScene>();
						break;
					}

					//Multiplayer button
					case MAINMENU_BUTTON_MULTIPLAYER:
					{
						//Load multiplayer scene
						SceneManager::LoadScene<MultiplayerScene>();
						break;
					}

					//Exit button
					case MAINMENU_BUTTON_EXIT:
					{
						//Quit application
						Application::Quit();
						break;
					}
				}
			}
			break;
		}
	}
}