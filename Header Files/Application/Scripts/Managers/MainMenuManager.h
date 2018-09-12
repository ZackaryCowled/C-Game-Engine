//Pragma comments
#pragma once

//Precompiler definitions
#define MAINMENU_STATE_FADEIN 0
#define MAINMENU_STATE_SELECTION 1
#define MAINMENU_STATE_FADEOUT 2
#define MAINMENU_BUTTON_SINGEPLAYER 0
#define MAINMENU_BUTTON_MULTIPLAYER 1
#define MAINMENU_BUTTON_EXIT 2

//Internal includes
#include "Application.h"

//Main Menu Manager Script
class MainMenuManager : public Script
{
public:
	//Called on initialization
	virtual void Awake();

	//Called once per frame
	virtual void Update();

private:
	//The scripts parent
	GameObject* parent;

	//Background controller
	shared_ptr<BackgroundController> backgroundController;

	//Pong label controller
	shared_ptr<PongLabelController> pongLabelController;

	//Singleplayer button controller
	shared_ptr<ButtonController> singleplayerButtonController;

	//Multiplayer button controller
	shared_ptr<ButtonController> multiplayerButtonController;

	//Exit button controller
	shared_ptr<ButtonController> exitButtonController;

	//Mouse controller
	shared_ptr<MouseController> mouseController;

	//Fade manager
	shared_ptr<FadeManager> fadeManager;

	//State manager
	shared_ptr<StateManager> stateManager;

	//Selected button
	int selectedButton;
};