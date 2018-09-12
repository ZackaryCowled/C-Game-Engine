//Precompiler definitions
#define _WINSOCK_DEPRECATED_NO_WARNINGS

//Internal includes
#include "TCPSocket.h"

//External includes
#include <WinSock2.h>

//Creates and initializes a TCP socket instance
TCPSocket::TCPSocket()
{
	//Initialize TCP socket
	m_socketHandle = 0;
	m_connectedClientsList = vector<int>();
}

//Opens the TCP socket using any available IPV4 and port
const bool TCPSocket::Open()
{
	//Create TCP socket
	if ((m_socketHandle = (int)socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		//Failed to open TCP socket
		return false;
	}

	//Create address
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = IPV4_ANY_PORT;

	//Bind address to TCP socket
	if (bind(m_socketHandle, (const sockaddr*)&address, sizeof(address)) == SOCKET_ERROR)
	{
		//Failed to bind address to TCP socket
		return false;
	}

	//Successfully opened TCP socket
	return true;
}

//Opens the TCP socket using the specified IPV4
const bool TCPSocket::Open(const IPV4& ipv4)
{
	//Create TCP socket
	if ((m_socketHandle = (int)socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		//Failed to open TCP socket
		return false;
	}

	//Create address
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(ipv4.GetAddress().c_str());
	address.sin_port = htons(ipv4.GetPort());

	//Bind address to TCP socket
	if (bind(m_socketHandle, (const sockaddr*)&address, sizeof(address)) == SOCKET_ERROR)
	{
		//Failed to bind address to TCP socket
		return false;
	}

	//Successfully opened TCP socket
	return true;
}

//Opens the TCP socket using any available IPV4 and the specified port
const bool TCPSocket::Open(const unsigned short port)
{
	//Create TCP socket
	if ((m_socketHandle = (int)socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		//Failed to open TCP socket
		return false;
	}

	//Create address
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	//Bind address to TCP socket
	if (bind(m_socketHandle, (const sockaddr*)&address, sizeof(address)) == SOCKET_ERROR)
	{
		//Failed to bind address to TCP socket
		return false;
	}

	//Successfully opened TCP socket
	return true;
}

//Opens the TCP socket using the specified IPV4 and any available port
const bool TCPSocket::Open(const string& ipv4)
{
	//Create TCP socket
	if ((m_socketHandle = (int)socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		//Failed to open TCP socket
		return false;
	}

	//Create address
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(ipv4.c_str());
	address.sin_port = IPV4_ANY_PORT;

	//Bind address to TCP socket
	if (bind(m_socketHandle, (const sockaddr*)&address, sizeof(address)) == SOCKET_ERROR)
	{
		//Failed to bind address to TCP socket
		return false;
	}

	//Successfully opened TCP socket
	return true;
}

//Opens the TCP socket using the specified IPV4 and port
const bool TCPSocket::Open(const string& ipv4, const unsigned short port)
{
	//Create TCP socket
	if ((m_socketHandle = (int)socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		//Failed to open TCP socket
		return false;
	}

	//Create address
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(ipv4.c_str());
	address.sin_port = htons(port);

	//Bind address to TCP socket
	if (bind(m_socketHandle, (const sockaddr*)&address, sizeof(address)) == SOCKET_ERROR)
	{
		//Failed to bind address to TCP socket
		return false;
	}

	//Successfully opened TCP socket
	return true;
}

//Accepts an incomming connection if one exists
const bool TCPSocket::AcceptConnection()
{
	//Create intermediary attributes
	sockaddr_in address;
	int addressLength = sizeof(address);

	//Accept connection
	int clientSocket = (int)accept(m_socketHandle, (sockaddr*)&address, &addressLength);

	//If the accepted connection is invalid
	if (clientSocket == INVALID_SOCKET)
	{
		//Failed to accept connection
		return false;
	}

	//Add the client to the connected clients list
	m_connectedClientsList.push_back(clientSocket);

	//Successfully accepted connection
	return true;
}

//Accepts an incomming connection if one exists and stores the clients public IPV4 address
const bool TCPSocket::AcceptConnection(IPV4& publicIPV4)
{
	//Create intermediary attributes
	sockaddr_in address;
	int addressLength = sizeof(address);

	//Accept connection
	int clientSocket = (int)accept(m_socketHandle, (sockaddr*)&address, &addressLength);

	//If the accepted connection is invalid
	if (clientSocket == INVALID_SOCKET)
	{
		//Failed to accept connection
		return false;
	}

	//Store cilents public IPV4 address in the specified IPV4
	publicIPV4.Set(inet_ntoa(address.sin_addr), ntohs(address.sin_port));

	//Add the client to the connected clients list
	m_connectedClientsList.push_back(clientSocket);

	//Successfully accepted connection
	return true;
}

//Accepts an incomming connection if one exists and stores the clients public and private IPV4 addresses
const bool TCPSocket::AcceptConnection(IPV4& publicIPV4, IPV4& privateIPV4)
{
	//Create intermediary attributes
	sockaddr_in address;
	int addressLength = sizeof(address);

	//Accept connection
	int clientSocket = (int)accept(m_socketHandle, (sockaddr*)&address, &addressLength);

	//If the accepted connection is invalid
	if (clientSocket == INVALID_SOCKET)
	{
		//Failed to accept connection
		return false;
	}

	//Store cilents public IPV4 address in the specified IPV4
	publicIPV4.Set(inet_ntoa(address.sin_addr), ntohs(address.sin_port));

	//Query sockets private IPV4
	getsockname(clientSocket, (sockaddr*)&address, &addressLength);
	
	//Store clients private IPV4 address in the specified IPV4
	privateIPV4.Set(inet_ntoa(address.sin_addr), ntohs(address.sin_port));

	//Add the client to the connected clients list
	m_connectedClientsList.push_back(clientSocket);

	//Successfully accepted connection
	return true;
}

//Closes the TCP socket instance
const bool TCPSocket::Close()
{
	//Close TCP socket
	if (closesocket(m_socketHandle) == NO_ERROR)
	{
		//Successfully closed TCP socket
		return true;
	}

	//Failed to close TCP socket
	return false;
}

//Connects the TCP socket to the specified host
void TCPSocket::ConnectTo(const IPV4& ipv4)
{
	//Create address
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(ipv4.GetAddress().c_str());
	address.sin_port = htons(ipv4.GetPort());

	//Connect to the specified host
	connect(m_socketHandle, (const sockaddr*)&address, sizeof(address));
}

//Connects the TCP socket to the specified host
//If the specified hostURL cannot resolve an IPV4 the host URL is used as an IPV4
void TCPSocket::ConnectTo(const URL& hostURL)
{
	//Create address
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(0);

	//Query host data
	hostent* hostData = gethostbyname(hostURL.GetHostname().c_str());

	//If the host data is valid
	if (hostData != nullptr)
	{
		//Use the specified hosts IPV4
		address.sin_addr.s_addr = *(u_long*)hostData->h_addr_list[0];
	}
	//Otherwise
	else
	{
		//Use the specified hostname converted to an IPV4
		address.sin_addr.s_addr = inet_addr(hostURL.GetHostname().c_str());
	}

	//Connect to the specified host
	connect(m_socketHandle, (const sockaddr*)&address, sizeof(address));
}

//Connects the TCP socket to the specified host
//If the specified hostname cannot resolve an IPV4 the hostname is used as an IPV4
void TCPSocket::ConnectTo(const string& hostname)
{
	//Create address
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(0);

	//Query host data
	hostent* hostData = gethostbyname(hostname.c_str());

	//If the host data is valid
	if (hostData != nullptr)
	{
		//Use the specified hosts IPV4
		address.sin_addr.s_addr = *(u_long*)hostData->h_addr_list[0];
	}
	//Otherwise
	else
	{
		//Use the specified hostname converted to an IPV4
		address.sin_addr.s_addr = inet_addr(hostname.c_str());
	}

	//Connect to the specified host
	connect(m_socketHandle, (const sockaddr*)&address, sizeof(address));
}

//Connects the TCP socket to the specified host and port
//If the specified hostURL cannot resolve an IPV4 the host URL is used as an IPV4
void TCPSocket::ConnectTo(const URL& hostURL, const unsigned short port)
{
	//Create address
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(port);

	//Query host data
	hostent* hostData = gethostbyname(hostURL.GetHostname().c_str());

	//If the host data is valid
	if (hostData != nullptr)
	{
		//Use the specified hosts IPV4
		address.sin_addr.s_addr = *(u_long*)hostData->h_addr_list[0];
	}
	//Otherwise
	else
	{
		//Use the specified hostname converted to an IPV4
		address.sin_addr.s_addr = inet_addr(hostURL.GetHostname().c_str());
	}

	//Connect to the specified host
	connect(m_socketHandle, (const sockaddr*)&address, sizeof(address));
}

//Connects the TCP socket to the specified host and port
//If the specified hostname cannot resolve an IPV4 the hostname is used as an IPV4
void TCPSocket::ConnectTo(const string& hostname, const unsigned short port)
{
	//Create address
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(port);

	//Query host data
	hostent* hostData = gethostbyname(hostname.c_str());

	//If the host data is valid
	if (hostData != nullptr)
	{
		//Use the specified hosts IPV4
		address.sin_addr.s_addr = *(u_long*)hostData->h_addr_list[0];
	}
	//Otherwise
	else
	{
		//Use the specified hostname converted to an IPV4
		address.sin_addr.s_addr = inet_addr(hostname.c_str());
	}

	//Connect to the specified host
	connect(m_socketHandle, (const sockaddr*)&address, sizeof(address));
}

//Returns a flag indicating whether the TCP socket is connected to a host
const bool TCPSocket::ConnectedToHost()
{
	//Create buffer
	char buffer;

	//Query connection status
	int receivedBytes = recv(m_socketHandle, &buffer, 1, MSG_PEEK);

	//If the socket is not connected to a host
	if (receivedBytes == SOCKET_ERROR || receivedBytes == 0)
	{
		//Socket is not connected to a host
		return false;
	}

	//Socket is connected to a host
	return true;
}

//Disables blocking by the TCP socket instance
const bool TCPSocket::DisableBlocking()
{
	//Create non-blocking flag
	DWORD nonBlocking = 1;

	//Disable blocking by the TCP socket
	if (ioctlsocket(m_socketHandle, FIONBIO, &nonBlocking) == NO_ERROR)
	{
		//Successfully disabled blocking
		return true;
	}

	//Failed to disable blocking
	return false;
}

//Disables TCP socket from listening for incomming connections
const bool TCPSocket::DisableIncommingConnections() const
{
	//Disable TCP socket from listening for incomming connections
	if (listen(m_socketHandle, 0) == SOCKET_ERROR)
	{
		//Failed to disable incomming connections
		return false;
	}

	//Successfully disabled incomming connections
	return true;
}

//Disconnects the TCP socket from the connected host
const bool TCPSocket::Disconnect()
{
	//Disconnect the TCP socket from the connected host
	if (shutdown(m_socketHandle, SD_SEND) == NO_ERROR)
	{
		//Successfully disconnected from the connected host
		return true;
	}

	//Failed to disconnect from the connected host
	return false;
}

//Disconnects the client at the specified index in the connected clients list
void TCPSocket::DisconnectClientAtIndex(const unsigned int index)
{
	//Erase the client at the specified index in the connect client list
	m_connectedClientsList.erase(m_connectedClientsList.begin() + index);
}

//Enables blocking by the TCP socket instance
const bool TCPSocket::EnableBlocking()
{
	//Create blocking flag
	DWORD blocking = 0;

	//Enable blocking by the TCP socket
	if (ioctlsocket(m_socketHandle, FIONBIO, &blocking) == NO_ERROR)
	{
		//Successfully enabled blocking
		return true;
	}

	//Failed to enable blocking
	return false;
}

//Enables TCP socket listening for incoming connections
const bool TCPSocket::EnableIncommingConnections() const
{
	//Enable TCP socket listening for incomming connections
	if (listen(m_socketHandle, SOMAXCONN) == SOCKET_ERROR)
	{
		//Failed to enable incomming connections
		return false;
	}

	//Successfully enabled incomming connections
	return true;
}

//Returns the number of clients connected to the TCP socket
const unsigned int TCPSocket::GetClientCount()
{
	//Return the number of clients connected to the TCP socket
	return (unsigned int)m_connectedClientsList.size();
}

//Returns the clients public IPV4 address at the specified index in the connected clients list
const IPV4 TCPSocket::GetClientPublicIPV4(const unsigned int index)
{
	//Create intermediary values
	sockaddr_in address;
	int addressLength = sizeof(address);

	//Query the client TCP sockets public address
	getpeername(m_connectedClientsList[index], (sockaddr*)&address, &addressLength);

	//Return the clients public IPV4
	return IPV4(inet_ntoa(address.sin_addr), ntohs(address.sin_port));
}

//Returns the clients private IPV4 address at the specified index in the connected clients list
const IPV4 TCPSocket::GetClientPrivateIPV4(const unsigned int index)
{
	//Create intermediary values
	sockaddr_in address;
	int addressLength = sizeof(address);

	//Query the client TCP sockets private address
	getsockname(m_connectedClientsList[index], (sockaddr*)&address, &addressLength);

	//Return the clients private IPV4
	return IPV4(inet_ntoa(address.sin_addr), ntohs(address.sin_port));
}

//Returns the TCP sockets public IPV4
const IPV4 TCPSocket::GetPublicIPV4()
{
	//Create intermediary values
	sockaddr_in address;
	int addressLength = sizeof(address);

	//Query the TCP sockets public address
	getpeername(m_socketHandle, (sockaddr*)&address, &addressLength);

	//Return the TCP sockets public IPV4
	return IPV4(inet_ntoa(address.sin_addr), ntohs(address.sin_port));
}

//Returns the TCP sockets private IPV4
const IPV4 TCPSocket::GetPrivateIPV4()
{
	//Create intermediary values
	sockaddr_in address;
	int addressLength = sizeof(address);

	//Query the TCP sockets private address
	getsockname(m_socketHandle, (sockaddr*)&address, &addressLength);

	//Return the TCP sockets private IPV4
	return IPV4(inet_ntoa(address.sin_addr), ntohs(address.sin_port));
}

//Receives a packet if one is available from the connected host
const bool TCPSocket::ReceivePacket(void* packetData, const int packetSize)
{
	//Receive packet
	int receivedBytes = recv(m_socketHandle, (char*)packetData, packetSize, 0);

	//If all the packet data was received
	if (receivedBytes == packetSize)
	{
		//Successfully received packet
		return true;
	}

	//Failed to receive packet
	return false;
}

//Receives a packet if one is available from the client at the specified index in the connected clients list
const bool TCPSocket::ReceivePacketFromClientAt(const unsigned int index, void* packetData, const int packetSize)
{
	//Receive packet from the client at the specified index in the connected clients list
	int receivedBytes = recv(m_connectedClientsList[index], (char*)packetData, packetSize, 0);

	//If all of the packet data was received
	if (receivedBytes == packetSize)
	{
		//Successfully received packet
		return true;
	}

	//Failed to receive packet
	return false;
}

//Sends a packet to the connected server
const bool TCPSocket::SendPacket(void* packetData, const int packetSize)
{
	//Send packet to connected server
	int sentBytes = send(m_socketHandle, (const char*)packetData, packetSize, 0);

	//If all of the packet sent
	if (sentBytes == packetSize)
	{
		//Successfully sent packet
		return true;
	}

	//Failed to send packet
	return false;
}

//Sends a packet to the client at the specified index in the connected clients list
const bool TCPSocket::SendPacketToClientAt(const unsigned int index, void* packetData, const int packetSize)
{
	//Send packet to the client at the specified index in the connected clients list
	int sentBytes = send(m_connectedClientsList[index], (const char*)packetData, packetSize, 0);

	//If all of the packet sent
	if (sentBytes == packetSize)
	{
		//successfully sent packet
		return true;
	}

	//Failed to send packet
	return false;
}