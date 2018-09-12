//Pragma comments
#pragma once

//Internal includes
#include "IPV4.h"

//External includes
#include <vector>

//Using directives
using std::vector;

//Object with various functions for transferring data on networks using the transmission control protocol
class TCPSocket
{
public:
	//Creates and initializes a TCP socket instance
	TCPSocket();

	//Opens the TCP socket using any available IPV4 and port
	const bool Open();

	//Opens the TCP socket using the specified IPV4
	const bool Open(const IPV4& ipv4);

	//Opens the TCP socket using any available IPV4 and the specified port
	const bool Open(const unsigned short port);

	//Opens the TCP socket using the specified IPV4 and any available port
	const bool Open(const string& ipv4);

	//Opens the TCP socket using the specified IPV4 and port
	const bool Open(const string& ipv4, const unsigned short port);

	//Accepts an incomming connection if one exists
	const bool AcceptConnection();

	//Accepts an incomming connection if one exists and stores the clients public IPV4 address
	const bool AcceptConnection(IPV4& publicIPV4);

	//Accepts an incomming connection if one exists and stores the clients public and private IPV4 addresses
	const bool AcceptConnection(IPV4& publicIPV4, IPV4& privateIPV4);

	//Closes the TCP socket instance
	const bool Close();

	//Connects the TCP socket to the specified host
	void ConnectTo(const IPV4& ipv4);

	//Connects the TCP socket to the specified host
	//If the specified hostURL cannot resolve an IPV4 the host URL is used as an IPV4
	void ConnectTo(const URL& hostURL);

	//Connects the TCP socket to the specified host
	//If the specified hostname cannot resolve an IPV4 the hostname is used as an IPV4
	void ConnectTo(const string& hostname);

	//Connects the TCP socket to the specified host and port
	//If the specified hostURL cannot resolve an IPV4 the host URL is used as an IPV4
	void ConnectTo(const URL& hostURL, const unsigned short port);

	//Connects the TCP socket to the specified host and port
	//If the specified hostname cannot resolve an IPV4 the hostname is used as an IPV4
	void ConnectTo(const string& hostname, const unsigned short port);

	//Returns a flag indicating whether the TCP socket is connected to a host
	const bool ConnectedToHost();

	//Disables blocking by the TCP socket instance
	const bool DisableBlocking();

	//Disables TCP socket from listening for incomming connections
	const bool DisableIncommingConnections() const;

	//Disconnects the TCP socket from the connected host
	const bool Disconnect();

	//Disconnects the client at the specified index in the connected clients list
	void DisconnectClientAtIndex(const unsigned int index);

	//Enables blocking by the TCP socket instance
	const bool EnableBlocking();

	//Enables TCP socket listening for incoming connections
	const bool EnableIncommingConnections() const;

	//Returns the number of clients connected to the TCP socket
	const unsigned int GetClientCount();

	//Returns the clients public IPV4 address at the specified index in the connected clients list
	const IPV4 GetClientPublicIPV4(const unsigned int index);

	//Returns the clients private IPV4 address at the specified index in the connected clients list
	const IPV4 GetClientPrivateIPV4(const unsigned int index);

	//Returns the TCP sockets public IPV4
	const IPV4 GetPublicIPV4();

	//Returns the TCP sockets private IPV4
	const IPV4 GetPrivateIPV4();

	//Receives a packet if one is available from the connected host
	const bool ReceivePacket(void* packetData, const int packetSize);

	//Receives a packet if one is available from the client at the specified index in the connected clients list
	const bool ReceivePacketFromClientAt(const unsigned int index, void* packetData, const int packetSize);

	//Sends a packet to the connected host
	const bool SendPacket(void* packetData, const int packetSize);

	//Sends a packet to the client at the specified index in the connected clients list
	const bool SendPacketToClientAt(const unsigned int index, void* packetData, const int packetSize);

private:
	//TCP socket handle
	int m_socketHandle;

	//Connected clients list
	vector<int> m_connectedClientsList;
};