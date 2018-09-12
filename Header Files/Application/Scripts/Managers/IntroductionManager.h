//Pragma comments
#pragma once

//Precompiler definitions
#define INTRODUCTION_STATE_FADEIN 0
#define INTRODUCTION_STATE_FADEOUT 1

//Internal includes
#include "Application.h"

//Introduction Manager Script
class IntroductionManager : public Script
{
public:
	//Called on initialization
	virtual void Awake();

	//Called once per frame
	virtual void Update();

private:
	//The scripts parent
	GameObject* parent;

	//Arphenion logo controller
	shared_ptr<ArphenionLogoController> arphenionLogoController;

	//Fade manager
	shared_ptr<FadeManager> fadeManager;

	//State manager
	shared_ptr<StateManager> stateManager;
};