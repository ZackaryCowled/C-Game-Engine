//Pragma comments
#pragma once
#pragma comment(lib, "ws2_32.lib")

//Internal includes
#include "HTTPSocket.h"
#include "IPV4.h"
#include "UDPSocket.h"
#include "URL.h"
#include "TCPSocket.h"

//Singleton class providing functions for initializing and termianting the network library
class Network
{
public:
	//Initializes the network library
	static const bool Initialize();

	//Returns the systems local IPV4
	static const IPV4 GetLocalIPV4();

	//Termiantes the network library
	static const bool Terminate();
};