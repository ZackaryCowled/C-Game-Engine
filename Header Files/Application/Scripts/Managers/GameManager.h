//Pragma comments
#pragma once

//Internal includes
#include "Application.h"

//Game Manager Script
class GameManager : public Script
{
public:
	//Called on initialization
	virtual void Awake() = 0;

	//Called once per frame
	virtual void Update() = 0;

	//Initializes the GameManager
	void InitializeGameManager();

protected:
	//The scripts parent
	GameObject* parent;

	//Ball controller
	shared_ptr<BallController> ballController;

	//Player controller
	shared_ptr<PlayerController> playerController;

	//Enemy controller
	shared_ptr<EnemyController> enemyController;

	//Score Controller
	shared_ptr<ScoreController> scoreController;

	//Countdown controller
	shared_ptr<CountdownController> countdownController;

	//Win message
	GUIObject* winMessage;

	//Lose message
	GUIObject* loseMessage;

	//Fade Manager
	shared_ptr<FadeManager> fadeManager;

	//State Manager
	shared_ptr<StateManager> stateManager;
};