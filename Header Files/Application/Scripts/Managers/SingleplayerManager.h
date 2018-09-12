//Pragma comments
#pragma once

//Precompiler definitions
#define SINGLEPLAYER_STATE_FADEIN 0
#define SINGLEPLAYER_STATE_COUNTDOWN 1
#define SINGLEPLAYER_STATE_PLAY 2
#define SINGLEPLAYER_STATE_END 3
#define SINGLEPLAYER_STATE_FADEOUT 4

//Internal include
#include "Application.h"

//Singleplayer Manager Script
class SingleplayerManager : public GameManager
{
public:
	//Called on initialization
	virtual void Awake();

	//Called once per frame
	virtual void Update();
};