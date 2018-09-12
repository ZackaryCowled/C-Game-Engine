//Pragma comments
#pragma once

//Internal includes
#include "Application.h"

//Background Controller Script
class BackgroundController : public Script
{
public:
	//Called on initialization
	virtual void Awake();

	//Updates the background the background controller is controlling
	virtual void Update();

	//Returns the background the background controller is controlling
	GUIObject* GetBackground();

private:
	//The scripts parent
	GameObject* parent;

	//Smoke effect object
	GUIObject* smokeEffect;

	//Smoke effect speed
	float smokeEffectSpeed;
};