//Pragma comments
#pragma once

//Precompiler definitions
#define MULTIPLAYER_CONNECTING_TO_SERVER 0
#define MULTIPLAYER_STATE_WAITING_FOR_GAME 1
#define MULTIPLAYER_STATE_FADEIN 2
#define MULTIPLAYER_STATE_COUNTDOWN 3
#define MULTIPLAYER_STATE_PLAY 4
#define MULTIPLAYER_STATE_END 5
#define MULTIPLAYER_STATE_FADEOUT 6

//Internal includes
#include "Application.h"

//External includes
#include <Network.h>

//Multiplayer Manager Script
class MultiplayerManager : public GameManager
{
public:
	//Called on initialization
	virtual void Awake();

	//Called once per frame
	virtual void Update();

private:
	//Matchmaking GUI controller
	shared_ptr<MatchmakingGUIController> matchmakingGUIController;

	//TCP socket
	TCPSocket tcpSocket;

	//UDP socket
	UDPSocket udpSocket;

	//Client ID
	unsigned int clientID;

	//Game ID
	unsigned int gameID;

	//Packet timer
	float packetTimer;

	//Packet send interval
	float packetSendInterval;

	//Client update packet
	UpdateClientPacket updateClientPacket;

	//Update game packet
	UpdateGamePacket updateGamePacket;
};