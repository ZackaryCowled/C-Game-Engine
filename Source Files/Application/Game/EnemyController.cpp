//Internal includes
#include "ApplicationHeaders.h"

//Called on initialization
void EnemyController::Awake()
{
	//Initialize parent
	parent = GetParent();

	//Initialize enemy
	enemy = parent->AddComponent<GUIObject>();
	enemy->SetTextureMap("Textures/Paddle.png");
	enemy->SetScale(GUIManager::CreateScaleFromReference(vec2(1920.0f, 1080.0f), vec2(ENEMY_WIDTH, ENEMY_HEIGHT)));
	enemy->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), vec2(1888.0f, 476.0f)));
	enemy->SetColor(vec4(1.0f, 0.0f, 0.0f, 0.0f));

	//Initialize position
	position = vec2(1888.0f, 476.0f);

	//Initialize velocity
	velocity = vec2(0.0f, 0.0f);

	//Initialize acceleration speed
	accelerationSpeed = 2000.0f;

	//Initialize friction
	friction = 5.0f;

	//Initialize difficulty
	difficulty = 0.25f;
}

//Updates the enemy the enemy controller is controlling
void EnemyController::Update(const vec2& target, const vec2& targetVelocity)
{
	//If the enemy is colliding with the top edge of the screen
	if (position.y < 0.0f)
	{
		//Correct the enemys position on the y-axis
		position.y = 0.0f;

		//Inverse the enemys velocity on the y-axis
		velocity = vec2(velocity.x, -velocity.y);
	}

	//If the enemy is colliding with the bottom edge of the screen
	if (position.y + ENEMY_HEIGHT > 1080.0f)
	{
		//Correct the enemys position on the y-axis
		position.y = 1080.0f - ENEMY_HEIGHT;

		//Inverse the enemys velocity on the y-axis
		velocity = vec2(velocity.x, -velocity.y);
	}

	//Create intermediary values
	vec2 ghostPosition = target;
	vec2 ghostVelocity = normalize(targetVelocity);
	int passes = (int)(difficulty * 1000.0f);

	//For the specified number of passes
	for (int iteration = 0; iteration < passes && ghostPosition.x + BALL_WIDTH < position.x; ++iteration)
	{
		//Move the ghosts position by the ghosts velocity
		ghostPosition += ghostVelocity;

		//If ghost is colliding with the left edge of the screen
		if (ghostPosition.x < 0.0f)
		{
			//Fix ghosts position on the x-axis
			ghostPosition.x = -ghostPosition.x;
			
			//Invert ghosts velocity on the x-axis
			ghostVelocity.x = -ghostVelocity.x;
		}

		//If ghost is colliding with the top edge of the screen
		if (ghostPosition.y < 0.0f)
		{
			//Fix ghosts position on the y-axis
			ghostPosition.y = -ghostPosition.y;

			//Invert ghosts velocity on the y-axis
			ghostVelocity.y = -ghostVelocity.y;
		}

		//If ghost is colliding with the bottom edge of the screen
		if (ghostPosition.y + BALL_HEIGHT > 1080.0f) 
		{
			//Fix ghosts position on the y-axis
			ghostPosition.y -= (ghostPosition.y + BALL_HEIGHT) - 1080.0f;

			//Invert ghosts position on the y-axis
			ghostVelocity.y = -ghostVelocity.y;
		}
	}

	//If the targets position on the y-axis is higher then the enemys
	if (ghostPosition.y + BALL_HEIGHT / 2.0f < position.y + ENEMY_HEIGHT / 2.0f)
	{
		//Move enemy up
		velocity += vec2(0.0f, -accelerationSpeed * Time::deltaTime);
	}

	//If the targets position on the y-axis is lower then the enemys
	if (ghostPosition.y + BALL_HEIGHT / 2.0f > position.y + ENEMY_HEIGHT / 2.0f)
	{
		//Move enemy down
		velocity += vec2(0.0f, accelerationSpeed * Time::deltaTime);
	}

	//Apply friction to enemy
	velocity -= velocity * friction * Time::deltaTime;

	//Apply velocity to enemys position
	position += velocity * Time::deltaTime;

	//Update enemys position
	enemy->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), position));
}

//Updates the enemys the enemy controller is controlling
void EnemyController::SimpleUpdate()
{
	//Apply friction to enemy
	velocity -= velocity * friction * Time::deltaTime;

	//Apply velocity to enemys position
	position += velocity * Time::deltaTime;

	//Update enemys position
	enemy->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), position));
}

//Centres the enemy the enemy controller is controlling
void EnemyController::Centre()
{
	//Centre the enemy the enemy controller is controlling
	position = vec2(1888.0f, 476.0f);
	enemy->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), position));
}

//Returns the enemy the enemy controller is controlling
GUIObject* EnemyController::GetEnemy()
{
	//Return the enemy the enemy controller is controlling
	return enemy;
}

//Returns the position of the enemy the enemy controller is controlling
const vec2& EnemyController::GetPosition() const
{
	//Return the position of the enemy the enemy controller is controlling
	return position;
}

//Returns the velocity of the enemy the enemy controller is controlling
const vec2& EnemyController::GetVelocity() const
{
	//Return the velocity of the enemy the enemy controller is controlling
	return velocity;
}

//Sets the position of the enemy to the specified position
void EnemyController::SetPosition(const vec2& position)
{
	//Set the position of the enemy to the specified position
	this->position = position;
	enemy->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), this->position));
}

//Sets the velocity of the enemy the enemy controller is controlling
void EnemyController::SetVelocity(const vec2& velocity)
{
	//Set the velocity of the enemy the enemy controller is controlling
	this->velocity = velocity;
}