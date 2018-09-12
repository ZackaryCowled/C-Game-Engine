//Pragma comments
#pragma once

//Internal includes
#include "Application.h"

//Mouse Controller Script
class MouseController : public Script
{
public:
	//Called on initialization
	virtual void Awake();

	//Updates the mouse the mouse controller is controlling
	virtual void Update();

	//Returns the mouse the mouse controller is controlling
	GUIObject* GetMouse();

private:
	//The scripts parent
	GameObject* parent;

	//Mouse object
	GUIObject* mouse;
};