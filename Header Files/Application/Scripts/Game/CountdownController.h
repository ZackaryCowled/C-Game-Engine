//Pragma comments
#pragma once

//Precompiler definitions
#define COUNTDOWN_STATE_3 0
#define COUNTDOWN_STATE_2 1
#define COUNTDOWN_STATE_1 2
#define COUNTDOWN_STATE_FINISHED 3

//Internal includes
#include "Application.h"
#include "StateManager.h"

//Countdown Controller Script
class CountdownController : public Script
{
public:
	//Called on initialization
	virtual void Awake();

	//Performs countdown operation
	//Function returns true if the countdown is finished
	const bool Countdown();

private:
	//The scripts parent
	GameObject* parent;

	//Number object
	GUIObject* number;

	//State manager
	shared_ptr<StateManager> stateManager;
};