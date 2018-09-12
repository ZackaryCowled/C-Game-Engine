//Pragma comments
#pragma once

//Precompiler definitions
#define PLAYER_WIDTH 22.0f
#define PLAYER_HEIGHT 128.0f

//Internal includes
#include "Application.h"

//Player Controller Script
class PlayerController : public Script
{
public:
	//Called on initialization
	virtual void Awake();

	//Updates the player the player controller is controlling
	virtual void Update();

	//Centres the player the player controller is controlling
	void Centre();

	//Returns the player the player controller is controlling
	GUIObject* GetPlayer();

	//Returns the position of the player the player controller is controlling
	const vec2& GetPosition() const;

	//Returns the velocity of the player the player controller is controlling
	const vec2& GetVelocity() const;

	//Sets the velocity of the player the player controller is controlling
	void SetVelocity(const vec2& velocity);

private:
	//The scripts parent
	GameObject* parent;

	//Player object
	GUIObject* player;

	//Players position
	vec2 position;

	//Players velocity
	vec2 velocity;

	//Speed the player accelerates
	float accelerationSpeed;

	//Players friction
	float friction;
};