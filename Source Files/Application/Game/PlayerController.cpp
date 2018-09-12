//Internal includes
#include "ApplicationHeaders.h"

//Called on initialization
void PlayerController::Awake()
{
	//Initialize parent
	parent = GetParent();

	//Initialize player
	player = parent->AddComponent<GUIObject>();
	player->SetTextureMap("Textures/Paddle.png");
	player->SetScale(GUIManager::CreateScaleFromReference(vec2(1920.0f, 1080.0f), vec2(PLAYER_WIDTH, PLAYER_HEIGHT)));
	player->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), vec2(10.0f, 476.0f)));
	player->SetColor(vec4(0.0f, 1.0f, 0.0f, 0.0f));

	//Initialize position
	position = vec2(10.0f, 476.0f);

	//Initialize velocity
	velocity = vec2(0.0f, 0.0f);

	//Initialize acceleration speed
	accelerationSpeed = 2000.0f;

	//Initialize friction
	friction = 5.0f;
}

//Updates the player the player controller is controlling
void PlayerController::Update()
{
	//If the player is colliding with the top edge of the screen
	if (position.y < 0.0f)
	{
		//Correct the players position on the y-axis
		position.y = 0.0f;

		//Inverse the players velocity on the y-axis
		velocity = vec2(velocity.x, -velocity.y);
	}

	//If the player is colliding with the bottom edge of the screen
	if (position.y + ENEMY_HEIGHT > 1080.0f)
	{
		//Correct the players position on the y-axis
		position.y = 1080.0f - ENEMY_HEIGHT;

		//Inverse the players velocity on the y-axis
		velocity = vec2(velocity.x, -velocity.y);
	}

	//If the W or up arrow key is down
	if (Input::GetKey(EVENT_TRIGGER_KEY_W) || Input::GetKey(EVENT_TRIGGER_KEY_UP))
	{
		//Increase the players velocity by the acceleration speed
		velocity += vec2(0.0f, -accelerationSpeed * Time::deltaTime);
	}

	//If the S or down arrow key is down
	if (Input::GetKey(EVENT_TRIGGER_KEY_S) || Input::GetKey(EVENT_TRIGGER_KEY_DOWN))
	{
		//Increase the players velocity by the acceleration speed
		velocity += vec2(0.0f, accelerationSpeed * Time::deltaTime);
	}

	//Apply friction to players velocity
	velocity -= velocity * friction * Time::deltaTime;

	//Apply velocity to players position
	position += velocity * Time::deltaTime;

	//Update player position
	player->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), position));
}

//Centres the player the player controller is controlling
void PlayerController::Centre()
{
	//Centre the player the player controller is controlling
	position = vec2(10.0f, 476.0f);
	player->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), position));
}

//Returns the player the player controller is controlling
GUIObject* PlayerController::GetPlayer()
{
	//Return the player the player controller is controlling
	return player;
}

//Returns the position of the player the player controller is controlling
const vec2& PlayerController::GetPosition() const
{
	//Return the position of the player the player controller is controlling
	return position;
}

//Returns the velocity of the player the player controller is controlling
const vec2& PlayerController::GetVelocity() const
{
	//Return the velocity of the player the player controller is controlling
	return velocity;
}

//Sets the velocity of the player the player controller is controlling
void PlayerController::SetVelocity(const vec2& velocity)
{
	//Set the velocity of the player the player controller is controlling
	this->velocity = velocity;
}