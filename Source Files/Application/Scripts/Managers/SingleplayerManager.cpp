//Internal includes
#include "ApplicationHeaders.h"

//Called on initialization
void SingleplayerManager::Awake()
{
	//Initialize GameManager
	InitializeGameManager();
}

//Called once per frame
void SingleplayerManager::Update()
{
	//Depending on the current state of the game
	switch (stateManager->GetState())
	{
		//Fade in state
		case SINGLEPLAYER_STATE_FADEIN:
		{
			//Fade in game
			if (fadeManager->FadeInGUIObjects(0.5f * Time::deltaTime))
			{
				//Set state to countdown
				stateManager->SetState(SINGLEPLAYER_STATE_COUNTDOWN);
			}
			break;
		}

		//Countdown state
		case SINGLEPLAYER_STATE_COUNTDOWN:
		{
			//Centre the ball
			ballController->Centre();

			//Centre the player
			playerController->Centre();

			//Centre the enemy
			enemyController->Centre();

			//Countdown
			if (countdownController->Countdown())
			{
				//If the ball should be served to the player
				if (Random::IntegerInsideRange(0, 1))
				{
					//Serve the ball to the player
					ballController->SetVelocity(vec2(-500.0f, Random::FloatInsideRange(-500.0f, 500.0f)));
				}
				//Otherwise
				else
				{
					//Serve the ball to the enemy
					ballController->SetVelocity(vec2(500.0f, Random::FloatInsideRange(-500.0f, 500.0f)));
				}

				//Reset player and enemy velocities
				playerController->SetVelocity(vec2(0.0f, 0.0f));
				enemyController->SetVelocity(vec2(0.0f, 0.0f));

				//Set state to play
				stateManager->SetState(SINGLEPLAYER_STATE_PLAY);
			}
			break;
		}

		//Play state
		case SINGLEPLAYER_STATE_PLAY:
		{
			//Update ball
			ballController->Update();

			//Update player
			playerController->Update();

			//Update enemy
			enemyController->Update(ballController->GetPosition(), ballController->GetVelocity());

			//If the ball is colliding with the player
			if (ballController->GetPosition().x >= playerController->GetPosition().x &&
				ballController->GetPosition().x <= playerController->GetPosition().x + PLAYER_WIDTH &&
				ballController->GetPosition().y + BALL_HEIGHT >= playerController->GetPosition().y &&
				ballController->GetPosition().y <= playerController->GetPosition().y + PLAYER_HEIGHT)
			{
				//Correct the balls position on the x-axis
				ballController->SetPosition(vec2(playerController->GetPosition().x + PLAYER_WIDTH, ballController->GetPosition().y));

				//Inverse the balls x-velocity and add the players adjusted velocity to the ball
				ballController->SetVelocity(vec2(-ballController->GetVelocity().x, ballController->GetVelocity().y) + playerController->GetVelocity());
			}

			//If the ball is colliding with the enemy
			if (ballController->GetPosition().x + BALL_WIDTH >= enemyController->GetPosition().x &&
				ballController->GetPosition().x + BALL_WIDTH <= enemyController->GetPosition().x + ENEMY_WIDTH &&
				ballController->GetPosition().y + BALL_HEIGHT >= enemyController->GetPosition().y &&
				ballController->GetPosition().y <= enemyController->GetPosition().y + ENEMY_HEIGHT)
			{
				//Correct the balls position on the x-axis
				ballController->SetPosition(vec2(enemyController->GetPosition().x - BALL_WIDTH, ballController->GetPosition().y));

				//Inverse the balls x-velocity and add the enemys adjusted velocity to the ball
				ballController->SetVelocity(vec2(-ballController->GetVelocity().x, ballController->GetVelocity().y) + enemyController->GetVelocity());
			}

			//If the ball is colliding with the top edge of the screen
			if (ballController->GetPosition().y < 0.0f)
			{
				//Correct the balls position on the y-axis
				ballController->SetPosition(vec2(ballController->GetPosition().x, 0.0f));

				//Inverse the balls y-velocity
				ballController->SetVelocity(vec2(ballController->GetVelocity().x, -ballController->GetVelocity().y));
			}

			//If the ball is colliding with the bottom edge of the screen
			if (ballController->GetPosition().y + BALL_HEIGHT > 1080.0f)
			{
				//Correct the balls position on the y-axis
				ballController->SetPosition(vec2(ballController->GetPosition().x, 1080.0f - BALL_HEIGHT));

				//Inverse the balls y-velocity
				ballController->SetVelocity(vec2(ballController->GetVelocity().x, -ballController->GetVelocity().y));
			}

			//If the ball is off the left of the screen
			if (ballController->GetPosition().x + BALL_WIDTH < 0.0f)
			{
				//Increment enemy score
				scoreController->IncrementEnemyScore();

				//Set state to countdown
				stateManager->SetState(SINGLEPLAYER_STATE_COUNTDOWN);
			}
			
			//If the ball is off the right of the screen
			if (ballController->GetPosition().x > 1920.0f)
			{
				//Increment player score
				scoreController->IncrementPlayerScore();

				//Set state to countdown
				stateManager->SetState(SINGLEPLAYER_STATE_COUNTDOWN);
			}

			//If the player or enemy score is more or equal to 3
			if (scoreController->GetPlayerScoreValue() >= 3 || scoreController->GetEnemyScoreValue() >= 3)
			{
				//Set state to end
				stateManager->SetState(SINGLEPLAYER_STATE_END);
			}
			break;
		}

		//End state
		case SINGLEPLAYER_STATE_END:
		{
			//If the player score is equal to 3
			if (scoreController->GetPlayerScoreValue() == 3)
			{
				//Fade in win message
				if (winMessage->FadeIn(0.5f * Time::deltaTime))
				{
					//Add win message to fade manager GUI list
					fadeManager->RegisterGUIObject(winMessage);

					//Set state to fade out
					stateManager->SetState(SINGLEPLAYER_STATE_FADEOUT);
				}
			}
			//Otherwise
			else
			{
				//Fade in lose message
				if (loseMessage->FadeIn(0.5f * Time::deltaTime))
				{
					//Add lose message to fade manager GUI list
					fadeManager->RegisterGUIObject(loseMessage);

					//Set state to fade out
					stateManager->SetState(SINGLEPLAYER_STATE_FADEOUT);
				}
			}
			break;
		}

		//Fade out state
		case SINGLEPLAYER_STATE_FADEOUT:
		{
			//Fade out game
			if (fadeManager->FadeOutGUIObjects(0.5f * Time::deltaTime))
			{
				//Load MainMenu scene
				SceneManager::LoadScene<MainMenuScene>();
			}
			break;
		}
	}
}