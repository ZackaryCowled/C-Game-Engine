//Pragma comments
#pragma once

//Internal includes
#include "Application.h"

//State Manager Script
class StateManager : public Script
{
public:
	//Returns the current state
	const int GetState() const;

	//Sets the state to the specified state
	void SetState(const int state);

private:
	//Current state
	int state;
};