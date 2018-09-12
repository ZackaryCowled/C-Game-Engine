//Pragma comments
#pragma once

//Precompiler definitions
#define ENEMY_WIDTH 22.0f
#define ENEMY_HEIGHT 128.0f

//Internal includes
#include "Application.h"

//Enemy Controller Script
class EnemyController : public Script
{
public:
	//Called on initialization
	virtual void Awake();

	//Updates the enemy the enemy controller is controlling
	virtual void Update(const vec2& target, const vec2& targetVelocity);

	//Updates the enemys the enemy controller is controlling
	void SimpleUpdate();

	//Centres the enemy the enemy controller is controlling
	void Centre();

	//Returns the enemy the enemy controller is controlling
	GUIObject* GetEnemy();

	//Returns the position of the enemy the enemy controller is controlling
	const vec2& GetPosition() const;

	//Returns the velocity of the enemy the enemy controller is controlling
	const vec2& GetVelocity() const;

	//Sets the position of the enemy to the specified position
	void SetPosition(const vec2& position);

	//Sets the velocity of the enemy the enemy controller is controlling
	void SetVelocity(const vec2& velocity);

private:
	//The scripts parent
	GameObject* parent;

	//Enemy object
	GUIObject* enemy;

	//Enemys position
	vec2 position;

	//Enemys velocity
	vec2 velocity;

	//Speed the enemy accelerates
	float accelerationSpeed;

	//Enemys friction
	float friction;

	//Ememys difficulty
	float difficulty;
};