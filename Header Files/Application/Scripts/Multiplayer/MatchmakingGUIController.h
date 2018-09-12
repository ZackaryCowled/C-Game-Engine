//Pragma comments
#pragma once

//Internal includes
#include "Application.h"

//Matchmaking GUI controller Script
class MatchmakingGUIController : public Script
{
public:
	//Called on initialization
	virtual void Awake();

	//Called once per frame
	virtual void Update();

	//Hides the connecting to server label
	void HideConnectingToServerLabel();

	//Hides the waiting for game label
	void HideWaitingForGameLabel();

	//Hides the loading icon
	void HideLoadingIcon();

	//Shows the connecting to server label
	void ShowConnectingToServerLabel();

	//Shows the waiting for game label
	void ShowWaitingForGameLabel();

private:
	//The scripts parent
	GameObject* parent;

	//Connecting to server label
	GUIObject* connectingToServerLabel;

	//Waiting for game label
	GUIObject* waitingForGameLabel;

	//Loading icon 1
	GUIObject* loadingIcon1;

	//Loading icon 2
	GUIObject* loadingIcon2;

	//Loading icon 3
	GUIObject* loadingIcon3;

	//Loading icon 4
	GUIObject* loadingIcon4;

	//Loading icon 5
	GUIObject* loadingIcon5;

	//Loading icon 6
	GUIObject* loadingIcon6;

	//Loading icon 7
	GUIObject* loadingIcon7;

	//Loading icon 8
	GUIObject* loadingIcon8;

	//The current loading icon being displayed
	unsigned int currentLoadingIcon;

	//Timer
	float timer;
};