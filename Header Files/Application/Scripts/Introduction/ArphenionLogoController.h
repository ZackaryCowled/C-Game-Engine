//Pragma comments
#pragma once

//Internal includes
#include "Application.h"

//Arphenion Logo Controller Script
class ArphenionLogoController : public Script
{
public:
	//Called on initialization
	virtual void Awake();
	
	//Returns the arphenion logo the arphenion logo controller is controlling
	GUIObject* GetArphenionLogo();

private:
	//The scripts parent
	GameObject* parent;

	//Arphenion logo object
	GUIObject* arphenionLogo;
};