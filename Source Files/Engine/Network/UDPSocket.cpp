//Precompiler definitions
#define _WINSOCK_DEPRECATED_NO_WARNINGS

//Internal includes
#include "UDPSocket.h"

//External includes
#include <WinSock2.h>

//Creates and initializes a UDP socket instance
UDPSocket::UDPSocket()
{
	//Initialize UDP socket
	m_socketHandle = 0;
}

//Opens the UDP socket using any available IPV4 and port
const bool UDPSocket::Open()
{
	//Create UDP socket
	if ((m_socketHandle = (int)socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
	{
		//Failed to open UDP socket
		return false;
	}

	//Create address
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = IPV4_ANY_PORT;

	//Bind address to UDP socket
	if (bind(m_socketHandle, (const sockaddr*)&address, sizeof(address)) == SOCKET_ERROR)
	{
		//Failed to bind address to UDP socket
		return false;
	}

	//Successfully opened UDP socket
	return true;
}

//Opens the UDP socket using the specified IPV4
const bool UDPSocket::Open(const IPV4& ipv4)
{
	//Create UDP socket
	if ((m_socketHandle = (int)socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
	{
		//Failed to open UDP socket
		return false;
	}

	//Create address
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(ipv4.GetAddress().c_str());
	address.sin_port = htons(ipv4.GetPort());

	//Bind address to UDP socket
	if (bind(m_socketHandle, (const sockaddr*)&address, sizeof(address)) == SOCKET_ERROR)
	{
		//Failed to bind address to UDP socket
		return false;
	}

	//Successfully opened UDP socket
	return true;
}

//Opens the UDP socket using any available IPV4 and the specified port
const bool UDPSocket::Open(const unsigned short port)
{
	//Create UDP socket
	if ((m_socketHandle = (int)socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
	{
		//Failed to open UDP socket
		return false;
	}

	//Create address
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	//Bind address to UDP socket
	if (bind(m_socketHandle, (const sockaddr*)&address, sizeof(address)) == SOCKET_ERROR)
	{
		//Failed to bind address to UDP socket
		return false;
	}

	//Successfully opened UDP socket
	return true;
}

//Opens the UDP socket using the specified IPV4 and any available port
const bool UDPSocket::Open(const string& ipv4)
{
	//Create UDP socket
	if ((m_socketHandle = (int)socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
	{
		//Failed to open UDP socket
		return false;
	}

	//Create address
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(ipv4.c_str());
	address.sin_port = IPV4_ANY_PORT;

	//Bind address to UDP socket
	if (bind(m_socketHandle, (const sockaddr*)&address, sizeof(address)) == SOCKET_ERROR)
	{
		//Failed to bind address to UDP socket
		return false;
	}

	//Successfully opened UDP socket
	return true;
}

//Opens the UDP socket using the specified IPV4 and port
const bool UDPSocket::Open(const string& ipv4, const unsigned short port)
{
	//Create UDP socket
	if ((m_socketHandle = (int)socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
	{
		//Failed to open UDP socket
		return false;
	}

	//Create address
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(ipv4.c_str());
	address.sin_port = htons(port);

	//Bind address to UDP socket
	if (bind(m_socketHandle, (const sockaddr*)&address, sizeof(address)) == SOCKET_ERROR)
	{
		//Failed to bind address to UDP socket
		return false;
	}

	//Successfully opened UDP socket
	return true;
}

//Closes the UDP socket instance
const bool UDPSocket::Close()
{
	//Close UDP socket
	if (closesocket(m_socketHandle) == NO_ERROR)
	{
		//Successfully closed UDP socket
		return true;
	}
	
	//Failed to close UDP socket
	return false;
}

//Disables blocking by the UDP socket instance
const bool UDPSocket::DisableBlocking()
{
	//Create non-blocking flag
	DWORD nonBlocking = 1;

	//Disable blocking by the UDP socket
	if (ioctlsocket(m_socketHandle, FIONBIO, &nonBlocking) == NO_ERROR)
	{
		//Successfully disabled blocking
		return true;
	}

	//Failed to disable blocking
	return false;
}

//Enables blocking by the UDP socket instance
const bool UDPSocket::EnableBlocking()
{
	//Create blocking flag
	DWORD blocking = 0;

	//Enable blocking by the UDP socket
	if (ioctlsocket(m_socketHandle, FIONBIO, &blocking) == NO_ERROR)
	{
		//Successfully enabled blocking
		return true;
	}

	//Failed to enable blocking
	return false;
}

//Returns the UDP sockets public IPV4
const IPV4 UDPSocket::GetPublicIPV4()
{
	//Create intermediary values
	sockaddr_in address;
	int addressLength = sizeof(address);

	//Query the UDP sockets public address
	getpeername(m_socketHandle, (sockaddr*)&address, &addressLength);

	//Return the UDP sockets public IPV4
	return IPV4(inet_ntoa(address.sin_addr), ntohs(address.sin_port));
}

//Returns the UDP sockets private IPV4
const IPV4 UDPSocket::GetPrivateIPV4()
{
	//Create intermediary values
	sockaddr_in address;
	int addressLength = sizeof(address);

	//Query the UDP sockets private address
	getsockname(m_socketHandle, (sockaddr*)&address, &addressLength);

	//Return the UDP sockets private IPV4
	return IPV4(inet_ntoa(address.sin_addr), ntohs(address.sin_port));
}

//Receives a packet if one is available
const bool UDPSocket::ReceivePacket(void* packetData, const int packetSize)
{
	//Receive packet from sender
	int receivedBytes = recvfrom(m_socketHandle, (char*)packetData, packetSize, 0, nullptr, nullptr);

	//If the number of bytes received is equal to the packet size
	if (receivedBytes >= 0)
	{
		//Successfully received packet
		return true;
	}

	//Failed to receive packet
	return false;
}

//Receives a packet if one is available and stores the senders public IPV4 address
const bool UDPSocket::ReceivePacket(void* packetData, const int packetSize, IPV4& publicIPV4)
{
	//Create address for storing the senders IPV4
	sockaddr_in senderAddress;
	int senderAddressLength = sizeof(senderAddress);

	//Receive packet from sender
	int receivedBytes = recvfrom(m_socketHandle, (char*)packetData, packetSize, 0, (sockaddr*)&senderAddress, &senderAddressLength);

	//If the number of bytes received is equal to the packet size
	if (receivedBytes == packetSize)
	{
		//Store senders public IPV4 address in the specified IPV4
		publicIPV4.Set(inet_ntoa(senderAddress.sin_addr), ntohs(senderAddress.sin_port));

		//Successfully received packet
		return true;
	}

	//Failed to receive packet
	return false;
}

//Sends a packet from the UDP socket instance to the specified IPV4
const bool UDPSocket::SendPacket(const void* packetData, const int packetSize, const IPV4& ipv4)
{
	//Create address using the specified IPV4
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(ipv4.GetAddress().c_str());
	address.sin_port = htons(ipv4.GetPort());

	//Send packet to the recipient IPV4 from the specified socket
	int sentBytes = sendto(m_socketHandle, (char*)packetData, packetSize, 0, (const sockaddr*)&address, sizeof(address));

	//If the number of bytes sent is equal to the size of the packet
	if (sentBytes == packetSize)
	{
		//Packet sent successfully
		return true;
	}

	//Packet failed to send
	return false;
}

//Sends a packet from the UDP socket instance to the specified IPV4 and port
const bool UDPSocket::SendPacket(const void* packetData, const int packetSize, const string& ipv4, const unsigned short port)
{
	//Create address using the specified IPV4
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(ipv4.c_str());
	address.sin_port = htons(port);

	//Send packet to the recipient IPV4 from the specified socket
	int sentBytes = sendto(m_socketHandle, (char*)packetData, packetSize, 0, (const sockaddr*)&address, sizeof(address));

	//If the number of bytes sent is equal to the size of the packet
	if (sentBytes == packetSize)
	{
		//Packet sent successfully
		return true;
	}

	//Packet failed to send
	return false;
}