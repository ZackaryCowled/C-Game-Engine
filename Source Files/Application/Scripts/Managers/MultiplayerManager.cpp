//Internal includes
#include "ApplicationHeaders.h"

//Called on initialization
void MultiplayerManager::Awake()
{
	//Initialize GameManager
	InitializeGameManager();

	//Initialize matchmaking GUI controller
	matchmakingGUIController = shared_ptr<MatchmakingGUIController>(new MatchmakingGUIController());
	matchmakingGUIController->SetParent(GetParent());
	matchmakingGUIController->Awake();

	//Initialize network library
	if (Network::Initialize())
	{
		//Initialize TCP socket
		tcpSocket.Open();
		tcpSocket.DisableBlocking();

		//Initialize UDP socket
		udpSocket.Open();
		udpSocket.DisableBlocking();

		//Initialize client ID
		clientID = 0;

		//Initialize game ID
		gameID = 0;

		//Initialize packet timer
		packetTimer = 0.0f;

		//Initialize packet send interval
		packetSendInterval = 0.033f;

		//Initialize update client packet
		updateClientPacket = { 0, 0, 0.0f, 0.0f };

		//Initialize update game packet
		updateGamePacket = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	}
}

//Called once per frame
void MultiplayerManager::Update()
{
	//Depending on the current state of the game
	switch (stateManager->GetState())
	{
		//Connecting to matchmaking server state
		case MULTIPLAYER_CONNECTING_TO_SERVER:
		{
			//Show connecting to server label
			matchmakingGUIController->ShowConnectingToServerLabel();

			//Update matchmaking GUI controller
			matchmakingGUIController->Update();

			//If not connected to the server
			if (!tcpSocket.ConnectedToHost())
			{
				//Connect to the server
				tcpSocket.ConnectTo(IPV4(URL("zackarycowled.com"), 30000));
			}
			//Otherwise
			else
			{
				//Receive a packet from the server if one is available
				if (tcpSocket.ReceivePacket(&clientID, sizeof(clientID)))
				{
					//Disconnect from the server
					tcpSocket.Disconnect();

					//Close the socket
					tcpSocket.Close();

					//Hide connecting to server label
					matchmakingGUIController->HideConnectingToServerLabel();

					//Set state to waiting for game
					stateManager->SetState(MULTIPLAYER_STATE_WAITING_FOR_GAME);
					break;
				}
			}

			//If the escape key is down
			if (Input::GetKey(EVENT_TRIGGER_KEY_ESCAPE))
			{
				//Close the socket
				tcpSocket.Close();

				//Set state to fade out
				stateManager->SetState(MULTIPLAYER_STATE_FADEOUT);
			}
			break;
		}

		//Waiting for game state
		case MULTIPLAYER_STATE_WAITING_FOR_GAME:
		{
			//Show waiting for game label
			matchmakingGUIController->ShowWaitingForGameLabel();

			//Update matchmaking GUI controller
			matchmakingGUIController->Update();

			//Increment packet timer
			packetTimer += Time::deltaTime;

			//If the packet timer is equal to or has exceeded the packet send interval
			if (packetTimer >= packetSendInterval)
			{
				//Send game request to the server
				udpSocket.SendPacket(&clientID, sizeof(clientID), IPV4(URL("zackarycowled.com"), 30001));

				//Update packet timer
				packetTimer -= packetSendInterval;
			}

			//Receive game ID from the server if available
			if (udpSocket.ReceivePacket(&gameID, sizeof(gameID)))
			{
				//Hide waiting for game label
				matchmakingGUIController->HideWaitingForGameLabel();

				//Hide loading icon
				matchmakingGUIController->HideLoadingIcon();

				//Set state to fade in
				stateManager->SetState(MULTIPLAYER_STATE_FADEIN);
				break;
			}

			//If the escape key is down
			if (Input::GetKey(EVENT_TRIGGER_KEY_ESCAPE))
			{
				//Set state to fade out
				stateManager->SetState(MULTIPLAYER_STATE_FADEOUT);
			}
			break;
		}

		//Fade in state
		case MULTIPLAYER_STATE_FADEIN:
		{
			//Fade in game
			if (fadeManager->FadeInGUIObjects(0.5f * Time::deltaTime))
			{
				//Set state to countdown
				stateManager->SetState(MULTIPLAYER_STATE_COUNTDOWN);
			}

			//Increment packet timer
			packetTimer += Time::deltaTime;

			//If the packet timer is equal to or has exceeded the packet send interval
			if (packetTimer >= packetSendInterval)
			{
				//Configure update client packet
				updateClientPacket = { gameID, clientID, playerController->GetPosition().y, playerController->GetVelocity().y };

				//Send update client packet to the server
				udpSocket.SendPacket(&updateClientPacket, sizeof(updateClientPacket), IPV4(URL("zackarycowled.com"), 30002));

				//Update packet timer
				packetTimer -= packetSendInterval;
			}

			//Receive a game update from the server if one is available
			if (udpSocket.ReceivePacket(&updateGamePacket, sizeof(updateGamePacket)))
			{
				//Update ball
				ballController->SetPosition(vec2(updateGamePacket.ballPositionX, updateGamePacket.ballPositionY));
				ballController->SetVelocity(vec2(updateGamePacket.ballVelocityX, updateGamePacket.ballVelocityY));

				//Update enemy
				enemyController->SetPosition(vec2(enemyController->GetPosition().x, updateGamePacket.enemyPaddlePositionY));
				enemyController->SetVelocity(vec2(0.0f, updateGamePacket.enemyPaddleVelocityY));
			}
			break;
		}

		//Countdown state
		case MULTIPLAYER_STATE_COUNTDOWN:
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
				//Reset player and enemy velocities
				playerController->SetVelocity(vec2(0.0f, 0.0f));
				enemyController->SetVelocity(vec2(0.0f, 0.0f));

				//Set state to play
				stateManager->SetState(MULTIPLAYER_STATE_PLAY);
			}

			//Increment packet timer
			packetTimer += Time::deltaTime;

			//If the packet timer is equal to or has exceeded the packet send interval
			if (packetTimer >= packetSendInterval)
			{
				//Configure update client packet
				updateClientPacket = { gameID, clientID, playerController->GetPosition().y, playerController->GetVelocity().y };

				//Send update client packet to the server
				udpSocket.SendPacket(&updateClientPacket, sizeof(updateClientPacket), IPV4(URL("zackarycowled.com"), 30002));

				//Update packet timer
				packetTimer -= packetSendInterval;
			}

			//Receive a game update from the server if one is available
			if (udpSocket.ReceivePacket(&updateGamePacket, sizeof(updateGamePacket)))
			{
				//Update ball
				ballController->SetPosition(vec2(updateGamePacket.ballPositionX, updateGamePacket.ballPositionY));
				ballController->SetVelocity(vec2(updateGamePacket.ballVelocityX, updateGamePacket.ballVelocityY));

				//Update enemy
				enemyController->SetPosition(vec2(enemyController->GetPosition().x, updateGamePacket.enemyPaddlePositionY));
				enemyController->SetVelocity(vec2(0.0f, updateGamePacket.enemyPaddleVelocityY));
			}
			break;
		}

		//Play state
		case MULTIPLAYER_STATE_PLAY:
		{			
			//Update player
			playerController->Update();
			
			//Update enemy
			enemyController->SimpleUpdate();

			//Update ball
			ballController->Update();

			//Increment packet timer
			packetTimer += Time::deltaTime;

			//If the packet timer is equal to or has exceeded the packet send interval
			if (packetTimer >= packetSendInterval)
			{
				//Configure update client packet
				updateClientPacket = { gameID, clientID, playerController->GetPosition().y, playerController->GetVelocity().y };

				//Send update client packet to the server
				udpSocket.SendPacket(&updateClientPacket, sizeof(updateClientPacket), IPV4(URL("zackarycowled.com"), 30002));

				//Update packet timer
				packetTimer -= packetSendInterval;
			}

			//Receive a game update from the server if one is available
			if (udpSocket.ReceivePacket(&updateGamePacket, sizeof(updateGamePacket)))
			{
				//Update ball
				ballController->SetPosition(vec2(updateGamePacket.ballPositionX, updateGamePacket.ballPositionY));
				ballController->SetVelocity(vec2(updateGamePacket.ballVelocityX, updateGamePacket.ballVelocityY));

				//Update enemy
				enemyController->SetPosition(vec2(enemyController->GetPosition().x, updateGamePacket.enemyPaddlePositionY));
				enemyController->SetVelocity(vec2(0.0f, updateGamePacket.enemyPaddleVelocityY));
			}

			//If the ball is colliding with the player
			if (ballController->GetPosition().x >= 10.0f &&
				ballController->GetPosition().x <= 32.0f &&
				ballController->GetPosition().y + BALL_HEIGHT >= playerController->GetPosition().y &&
				ballController->GetPosition().y <= playerController->GetPosition().y + PLAYER_HEIGHT)
			{
				//Correct the balls position on the x-axis
				ballController->SetPosition(vec2(32.0f, ballController->GetPosition().y));

				//Inverse the balls x-velocity and add the players adjusted velocity to the ball
				ballController->SetVelocity(vec2(-ballController->GetVelocity().x, ballController->GetVelocity().y) + playerController->GetVelocity());
			}

			//If the ball is colliding with the enemy
			if (ballController->GetPosition().x + BALL_WIDTH >= 1888.0f &&
				ballController->GetPosition().x <= 1910.0f &&
				ballController->GetPosition().y + BALL_HEIGHT >= enemyController->GetPosition().y &&
				ballController->GetPosition().y <= enemyController->GetPosition().y + ENEMY_HEIGHT)
			{
				//Correct the balls position on the x-axis
				ballController->SetPosition(vec2(1827.0f, ballController->GetPosition().y));

				//Inverse the balls x-velocity and add the enemys adjusted velocity to the ball
				ballController->SetVelocity(vec2(-ballController->GetVelocity().x, ballController->GetVelocity().y) + enemyController->GetVelocity());
			}

			//If the ball is colliding with the top edge of the screen
			if (ballController->GetPosition().y <= 0.0f)
			{
				//Correct the balls position on the y-axis
				ballController->SetPosition(vec2(ballController->GetPosition().x, 0.0f));

				//Inverse the balls y-velocity
				ballController->SetVelocity(vec2(ballController->GetVelocity().x, -ballController->GetVelocity().y));
			}

			//If the ball is colliding with the bottom edge of the screen
			if (ballController->GetPosition().y + BALL_HEIGHT >= 1080.0f)
			{
				//Correct the balls position on the y-axis
				ballController->SetPosition(vec2(ballController->GetPosition().x, 1019.0f));

				//Inverse the balls y-velocity
				ballController->SetVelocity(vec2(ballController->GetVelocity().x, -ballController->GetVelocity().y));
			}

			//If the ball is off the left of the screen
			if (ballController->GetPosition().x + BALL_WIDTH < 0.0f)
			{
				//Increment enemy score
				scoreController->IncrementEnemyScore();

				//Set state to countdown
				stateManager->SetState(MULTIPLAYER_STATE_COUNTDOWN);
			}

			//If the ball is off the right of the screen
			if (ballController->GetPosition().x > 1920.0f)
			{
				//Increment player score
				scoreController->IncrementPlayerScore();

				//Set state to countdown
				stateManager->SetState(MULTIPLAYER_STATE_COUNTDOWN);
			}

			//If the player or enemy score is more or equal to 3
			if (scoreController->GetPlayerScoreValue() >= 3 || scoreController->GetEnemyScoreValue() >= 3)
			{
				//Set state to end
				stateManager->SetState(MULTIPLAYER_STATE_END);
			}
			break;
		}

		//End state
		case MULTIPLAYER_STATE_END:
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
					stateManager->SetState(MULTIPLAYER_STATE_FADEOUT);
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
					stateManager->SetState(MULTIPLAYER_STATE_FADEOUT);
				}
			}
			break;
		}

		//Fade out state
		case MULTIPLAYER_STATE_FADEOUT:
		{
			//Fade out game
			if (fadeManager->FadeOutGUIObjects(0.5f * Time::deltaTime))
			{
				//Terminate network library
				Network::Terminate();

				//Load MainMenu scene
				SceneManager::LoadScene<MainMenuScene>();
			}
			break;
		}
	}
}