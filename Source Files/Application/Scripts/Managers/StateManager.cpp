//Internal includes
#include "ApplicationHeaders.h"

//Returns the current state
const int StateManager::GetState() const
{
	//Return the current state
	return state;
}

//Sets the state to the specified state
void StateManager::SetState(const int state)
{
	//Set the state to the specified state
	this->state = state;
}