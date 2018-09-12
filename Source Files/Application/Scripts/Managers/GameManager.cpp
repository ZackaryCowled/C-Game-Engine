//Internal includes
#include "ApplicationHeaders.h"

//Initializes the GameManager
void GameManager::InitializeGameManager()
{
	//Initialize parent
	parent = GetParent();

	//Initialize ball controller
	ballController = shared_ptr<BallController>(new BallController());
	ballController->SetParent(parent);
	ballController->Awake();

	//Initialize player controller
	playerController = shared_ptr<PlayerController>(new PlayerController());
	playerController->SetParent(parent);
	playerController->Awake();

	//Initialize enemy controller
	enemyController = shared_ptr<EnemyController>(new EnemyController());
	enemyController->SetParent(parent);
	enemyController->Awake();

	//Initialize score controller
	scoreController = shared_ptr<ScoreController>(new ScoreController());
	scoreController->SetParent(parent);
	scoreController->Awake();

	//Initialize countdown controller
	countdownController = shared_ptr<CountdownController>(new CountdownController());
	countdownController->SetParent(parent);
	countdownController->Awake();

	//Initialize win message
	winMessage = parent->AddComponent<GUIObject>();
	winMessage->SetTextureMap("Textures/WinMessage.png");
	winMessage->SetScale(GUIManager::CreateScaleFromReference(vec2(1920.0f, 1080.0f), vec2(302.0f, 49.0f)));
	winMessage->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), vec2(809.0f, 515.5f)));
	winMessage->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

	//Initialize lose message
	loseMessage = parent->AddComponent<GUIObject>();
	loseMessage->SetTextureMap("Textures/LoseMessage.png");
	loseMessage->SetScale(GUIManager::CreateScaleFromReference(vec2(1920.0f, 1080.0f), vec2(314.0f, 49.0f)));
	loseMessage->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), vec2(803.0f, 515.5f)));
	loseMessage->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

	//Initialize fade manager
	fadeManager = shared_ptr<FadeManager>(new FadeManager());
	fadeManager->RegisterGUIObject(ballController->GetBall());
	fadeManager->RegisterGUIObject(playerController->GetPlayer());
	fadeManager->RegisterGUIObject(enemyController->GetEnemy());
	fadeManager->RegisterGUIObject(scoreController->GetPlayerScore());
	fadeManager->RegisterGUIObject(scoreController->GetEnemyScore());
	fadeManager->RegisterGUIObject(scoreController->GetScoreDivider());

	//Initialize state manager
	stateManager = shared_ptr<StateManager>(new StateManager());
	stateManager->SetState(0);
}