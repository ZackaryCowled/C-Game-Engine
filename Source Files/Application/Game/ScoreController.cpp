//Internal includes
#include "ApplicationHeaders.h"

//Called on initialization
void ScoreController::Awake()
{
	//Initialize parent
	parent = GetParent();

	//Initialize player score
	playerScore = parent->AddComponent<GUIObject>();
	playerScore->SetTextureMap("Textures/Score0.png");
	playerScore->SetScale(GUIManager::CreateScaleFromReference(vec2(1920.0f, 1080.0f), vec2(50.0f, 69.0f)));
	playerScore->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), vec2(885.0f, 10.0f)));
	playerScore->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

	//Initialize enemy score
	enemyScore = parent->AddComponent<GUIObject>();
	enemyScore->SetTextureMap("Textures/Score0.png");
	enemyScore->SetScale(GUIManager::CreateScaleFromReference(vec2(1920.0f, 1080.0f), vec2(50.0f, 69.0f)));
	enemyScore->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), vec2(985.0f, 10.0f)));
	enemyScore->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

	//Initialize score divider
	scoreDivider = parent->AddComponent<GUIObject>();
	scoreDivider->SetTextureMap("Textures/Score-.png");
	scoreDivider->SetScale(GUIManager::CreateScaleFromReference(vec2(1920.0f, 1080.0f), vec2(50.0f, 69.0f)));
	scoreDivider->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), vec2(935.0f, 10.0f)));
	scoreDivider->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

	//Initialize player score value
	playerScoreValue = 0;

	//Initialize enemy score value
	enemyScoreValue = 0;
}

//Returns the players score GUI object
GUIObject* ScoreController::GetPlayerScore()
{
	//Return the player score GUI object
	return playerScore;
}

//Returns the enemy score GUI Object
GUIObject* ScoreController::GetEnemyScore()
{
	//Return the enemy score GUI object
	return enemyScore;
}

//Returns the score divider GUI Object
GUIObject* ScoreController::GetScoreDivider()
{
	//Return the score divider GUI object
	return scoreDivider;
}

//Returns the players score
const int ScoreController::GetPlayerScoreValue() const
{
	//Return the player score value
	return playerScoreValue;
}

//Returns the enemys score
const int ScoreController::GetEnemyScoreValue() const
{
	//Return the enemy score value
	return enemyScoreValue;
}

//Increments the players score
void ScoreController::IncrementPlayerScore()
{
	//Increment the player score value
	playerScoreValue++;

	//Update player score texture
	UpdatePlayerScoreTexture();
}

//Increments the enemys score
void ScoreController::IncrementEnemyScore()
{
	//Increment the enemy score value
	enemyScoreValue++;

	//Update enemy score texture
	UpdateEnemyScoreTexture();
}

//Sets the players score
void ScoreController::SetPlayerScore(const int score)
{
	//Set the players score to the specified score
	playerScoreValue = score;

	//Update player score texture
	UpdatePlayerScoreTexture();
}

//Sets the enemys score
void ScoreController::SetEnemyScore(const int score)
{
	//Set the enemy score to the specified score
	enemyScoreValue = score;

	//Update enemy score texture
	UpdateEnemyScoreTexture();
}

//Updates the player score texture
void ScoreController::UpdatePlayerScoreTexture()
{
	//Depending on the player score
	switch (playerScoreValue)
	{
		//Player score: 0
		case 0:
		{
			//Set player score texture to 0
			playerScore->SetTextureMap("Textures/Score0.png");
			break;
		}

		//Player score: 1
		case 1:
		{
			//Set player score texture to 1
			playerScore->SetTextureMap("Textures/Score1.png");
			break;
		}

		//Player score 2
		case 2:
		{
			//Set player score texture to 2
			playerScore->SetTextureMap("Textures/Score2.png");
			break;
		}

		//Player score 3
		case 3:
		{
			//Set player score texture to 3
			playerScore->SetTextureMap("Textures/Score3.png");
			break;
		}
	}
}

//Updates the enemy score texture
void ScoreController::UpdateEnemyScoreTexture()
{
	//Depending on the enemy score
	switch (enemyScoreValue)
	{
		//Enemy score: 0
		case 0:
		{
			//Set enemy score texture to 0
			enemyScore->SetTextureMap("Textures/Score0.png");
			break;
		}

		//Enemy score: 1
		case 1:
		{
			//Set enemy score texture to 1
			enemyScore->SetTextureMap("Textures/Score1.png");
			break;
		}

		//Enemy score 2
		case 2:
		{
			//Set enemy score texture to 2
			enemyScore->SetTextureMap("Textures/Score2.png");
			break;
		}

		//Enemy score 3
		case 3:
		{
			//Set enemy score texture to 3
			enemyScore->SetTextureMap("Textures/Score3.png");
			break;
		}
	}
}