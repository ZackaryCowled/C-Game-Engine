//Precompiler definitions
#define _WINSOCK_DEPRECATED_NO_WARNINGS

//Internal includes
#include "Network.h"

//External includes
#include <WinSock2.h>

//Initializes the network library
const bool Network::Initialize()
{
	//Create winsock data object
	WSADATA winsockData;

	//Initialize winsock
	if (WSAStartup(MAKEWORD(2, 2), &winsockData) == NO_ERROR)
	{
		//Winsock initialized successfully
		return true;
	}

	//Winsock failed to initialize
	return false;
}

//Returns the systems local IPV4
const IPV4 Network::GetLocalIPV4()
{
	//Create intermediary attributes
	char hostName[255];
	hostent* hostData;

	//Query hostname
	if (gethostname(hostName, sizeof(hostName)) == NO_ERROR)
	{
		//Query host information
		if ((hostData = gethostbyname(hostName)) != NULL)
		{
			//Return the systems local IPV4
			return IPV4(inet_ntoa(*(struct in_addr *)*hostData->h_addr_list), IPV4_ANY_PORT);
		}
	}

	//Return default systems local IPV4
	return IPV4(IPV4_ANY_ADDRESS, IPV4_ANY_PORT);
}

//Termiantes the network library
const bool Network::Terminate()
{
	//Cleanup winsock
	if (WSACleanup() == NO_ERROR)
	{
		//Winsock cleanup succeeded
		return true;
	}

	//Winsock cleanup failed
	return false;
}