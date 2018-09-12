//Internal includes
#include "ApplicationHeaders.h"

//Called on initialization
void BallController::Awake()
{
	//Initialize parent
	parent = GetParent();

	//Initialize ball
	ball = parent->AddComponent<GUIObject>();
	ball->SetTextureMap("Textures/Ball.png");
	ball->SetScale(GUIManager::CreateScaleFromReference(vec2(1920.0f, 1080.0f), vec2(BALL_WIDTH, BALL_HEIGHT)));
	ball->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), vec2(929.5f, 509.5f)));
	ball->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

	//Initialize position
	position = vec2(929.5f, 509.5f);

	//Initialize velocity
	velocity = vec2(0.0f, 0.0f);
}

//Updates the ball the ball controller is controlling
void BallController::Update()
{
	//Apply velocity to the ball position
	position += velocity * Time::deltaTime;

	//Update balls position
	ball->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), position));
}

//Centres the ball the ball controller is controlling
void BallController::Centre()
{
	//Centre the ball the ball controller is controlling
	position = vec2(929.5f, 509.5f);
	ball->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), position));
}

//Returns the ball the ball controller is controlling
GUIObject* BallController::GetBall()
{
	//Return the ball the ball controller is controlling
	return ball;
}

//Returns the position of the ball the ball controller is controlling
const vec2& BallController::GetPosition() const
{
	//Return the position of the ball the ball controller is controlling
	return position;
}

//Returns the velocity of the ball the ball controller is controlling
const vec2& BallController::GetVelocity() const
{
	//Return the velocity of the ball the ball controller is controlling
	return velocity;
}

//Sets the position of the ball the ball controller is controlling
void BallController::SetPosition(const vec2& position)
{
	//Set the position of the ball the ball controller is controlling
	this->position = position;
}

//Sets the velocity of the ball the ball controller is controlling
void BallController::SetVelocity(const vec2& velocity)
{
	//Set the velocity of the ball the ball controller is controlling
	this->velocity = velocity;
}