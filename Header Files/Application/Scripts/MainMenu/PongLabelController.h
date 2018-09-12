//Pragma comments
#pragma once

//Internal includes
#include "Application.h"

//Pong Label Controller Script
class PongLabelController : public Script
{
public:
	//Called on initialization
	virtual void Awake();

	//Returns the pong label the pong label controller is controlling
	GUIObject* GetPongLabel();

private:
	//The scripts parent
	GameObject* parent;

	//Pong label object
	GUIObject* pongLabel;
};