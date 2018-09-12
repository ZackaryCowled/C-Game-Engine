//Pragma comments
#pragma once

//Internal includes
#include "Application.h"

//Score Controller Script
class ScoreController : public Script
{
public:
	//Called on initialization
	virtual void Awake();

	//Returns the players score GUI object
	GUIObject* GetPlayerScore();

	//Returns the enemy score GUI Object
	GUIObject* GetEnemyScore();

	//Returns the score divider GUI Object
	GUIObject* GetScoreDivider();

	//Returns the players score
	const int GetPlayerScoreValue() const;

	//Returns the enemys score
	const int GetEnemyScoreValue() const;

	//Increments the players score
	void IncrementPlayerScore();

	//Increments the enemys score
	void IncrementEnemyScore();

	//Sets the players score
	void SetPlayerScore(const int score);

	//Sets the enemys score
	void SetEnemyScore(const int score);

protected:
	//Updates the player score texture
	void UpdatePlayerScoreTexture();

	//Updates the enemy score texture
	void UpdateEnemyScoreTexture();

private:
	//The scripts parent
	GameObject* parent;

	//Player score object
	GUIObject* playerScore;

	//Enemy score object
	GUIObject* enemyScore;

	//Score divider object
	GUIObject* scoreDivider;

	//Player score value
	int playerScoreValue;

	//Enemy score value
	int enemyScoreValue;
};