//Pragma comments
#pragma once

//Internal includes
#include "IPV4.h"

//Object with various functions for transferring data on networks using the user-datagram protocol
class UDPSocket
{
public:
	//Creates and initializes a UDP socket instance
	UDPSocket();

	//Opens the UDP socket using any available IPV4 and port
	const bool Open();

	//Opens the UDP socket using the specified IPV4
	const bool Open(const IPV4& ipv4);

	//Opens the UDP socket using any available IPV4 and the specified port
	const bool Open(const unsigned short port);

	//Opens the UDP socket using the specified IPV4 and any available port
	const bool Open(const string& ipv4);

	//Opens the UDP socket using the specified IPV4 and port
	const bool Open(const string& ipv4, const unsigned short port);

	//Closes the UDP socket instance
	const bool Close();

	//Disables blocking by the UDP socket instance
	const bool DisableBlocking();

	//Enables blocking by the UDP socket instance
	const bool EnableBlocking();

	//Returns the UDP sockets public IPV4
	const IPV4 GetPublicIPV4();

	//Returns the UDP sockets private IPV4
	const IPV4 GetPrivateIPV4();

	//Receives a packet if one is available
	const bool ReceivePacket(void* packetData, const int packetSize);

	//Receives a packet if one is available and stores the senders public IPV4 address
	const bool ReceivePacket(void* packetData, const int packetSize, IPV4& publicIPV4);

	//Sends a packet from the UDP socket instance to the specified IPV4
	const bool SendPacket(const void* packetData, const int packetSize, const IPV4& ipv4);

	//Sends a packet from the UDP socket instance to the specified IPV4 and port
	const bool SendPacket(const void* packetData, const int packetSize, const string& ipv4, const unsigned short port);

private:
	//UDP socket handle
	int m_socketHandle;
};