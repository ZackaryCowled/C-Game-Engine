//Pragma comments
#pragma once

//Precompiler definitions
#define BALL_WIDTH 61.0f
#define BALL_HEIGHT 61.0f

//Internal includes
#include "Application.h"

//Ball Controller Script
class BallController : public Script
{
public:
	//Called on initialization
	virtual void Awake();

	//Updates the ball the ball controller is controlling
	virtual void Update();

	//Centres the ball the ball controller is controlling
	void Centre();

	//Returns the ball the ball controller is controlling
	GUIObject* GetBall();

	//Returns the position of the ball the ball controller is controlling
	const vec2& GetPosition() const;

	//Returns the velocity of the ball the ball controller is controlling
	const vec2& GetVelocity() const;

	//Sets the position of the ball the ball controller is controlling
	void SetPosition(const vec2& position);

	//Sets the velocity of the ball the ball controller is controlling
	void SetVelocity(const vec2& velocity);

private:
	//The scripts parent
	GameObject* parent;

	//Ball object
	GUIObject* ball;

	//Balls position
	vec2 position;

	//Balls Velocity
	vec2 velocity;
};