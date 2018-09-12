//Pragma comments
#pragma once

//Update client packet
struct UpdateClientPacket
{
	//Game ID
	unsigned int gameID;

	//Client ID
	unsigned int clientID;

	//Clients paddle position on the y-axis
	float clientPaddlePositionY;

	//Clients paddle velocity on the y-axis
	float clientPaddleVelocityY;
};

//Update game packet
struct UpdateGamePacket
{
	//Balls position on the x-axis
	float ballPositionX;

	//Balls position on the y-axis
	float ballPositionY;

	//Balls velocity on the x-axis
	float ballVelocityX;

	//Balls velocity on the y-axis
	float ballVelocityY;

	//Enemys paddle position on the y-axis
	float enemyPaddlePositionY;

	//Enemys paddle velocity on the y-axis
	float enemyPaddleVelocityY;
};