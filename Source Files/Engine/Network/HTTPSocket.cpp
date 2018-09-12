//Precompiler definitions
#define _WINSOCK_DEPRECATED_NO_WARNINGS

//Internal includes
#include "HTTPSocket.h"

//External includes
#include <WinSock2.h>

//Creates and initializes a HTTP socket instance
HTTPSocket::HTTPSocket()
{
	//Initialize HTTP socket
	m_socketHandle = 0;
	m_responseBody = "";
	m_responseHeader = "";
}

//Opens the HTTP socket using any available IPV4 and port
const bool HTTPSocket::Open()
{
	//Create HTTP socket
	if ((m_socketHandle = (int)socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		//Failed to open HTTP socket
		return false;
	}

	//Create address
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = IPV4_ANY_PORT;

	//Bind address to HTTP socket
	if (bind(m_socketHandle, (const sockaddr*)&address, sizeof(address)) == SOCKET_ERROR)
	{
		//Failed to bind address to HTTP socket
		return false;
	}

	//Successfully opened HTTP socket
	return true;
}

//Opens the HTTP socket using the specified IPV4
const bool HTTPSocket::Open(const IPV4& ipv4)
{
	//Create HTTP socket
	if ((m_socketHandle = (int)socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		//Failed to open HTTP socket
		return false;
	}

	//Create address
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(ipv4.GetAddress().c_str());
	address.sin_port = htons(ipv4.GetPort());

	//Bind address to HTTP socket
	if (bind(m_socketHandle, (const sockaddr*)&address, sizeof(address)) == SOCKET_ERROR)
	{
		//Failed to bind address to HTTP socket
		return false;
	}

	//Successfully opened HTTP socket
	return true;
}

//Opens the HTTP socket using any available IPV4 and the specified port
const bool HTTPSocket::Open(const unsigned short port)
{
	//Create HTTP socket
	if ((m_socketHandle = (int)socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		//Failed to open HTTP socket
		return false;
	}

	//Create address
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	//Bind address to HTTP socket
	if (bind(m_socketHandle, (const sockaddr*)&address, sizeof(address)) == SOCKET_ERROR)
	{
		//Failed to bind address to HTTP socket
		return false;
	}

	//Successfully opened HTTP socket
	return true;
}

//Opens the HTTP socket using the specified IPV4 and any available port
const bool HTTPSocket::Open(const string& ipv4)
{
	//Create HTTP socket
	if ((m_socketHandle = (int)socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		//Failed to open HTTP socket
		return false;
	}

	//Create address
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(ipv4.c_str());
	address.sin_port = IPV4_ANY_PORT;

	//Bind address to HTTP socket
	if (bind(m_socketHandle, (const sockaddr*)&address, sizeof(address)) == SOCKET_ERROR)
	{
		//Failed to bind address to HTTP socket
		return false;
	}

	//Successfully opened HTTP socket
	return true;
}

//Opens the HTTP socket using the specified IPV4 and port
const bool HTTPSocket::Open(const string& ipv4, const unsigned short port)
{
	//Create HTTP socket
	if ((m_socketHandle = (int)socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		//Failed to open HTTP socket
		return false;
	}

	//Create address
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(ipv4.c_str());
	address.sin_port = htons(port);

	//Bind address to HTTP socket
	if (bind(m_socketHandle, (const sockaddr*)&address, sizeof(address)) == SOCKET_ERROR)
	{
		//Failed to bind address to HTTP socket
		return false;
	}

	//Successfully opened HTTP socket
	return true;
}

//Closes the HTTP socket instance
const bool HTTPSocket::Close()
{
	//Close HTTP socket
	if (closesocket(m_socketHandle) == NO_ERROR)
	{
		//Successfully closed HTTP socket
		return true;
	}

	//Failed to close HTTP socket
	return false;
}

//Connects the HTTP socket to the specified host
void HTTPSocket::ConnectTo(const IPV4& ipv4)
{
	//Create address
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(ipv4.GetAddress().c_str());
	address.sin_port = htons(80);

	//Connect to the specified host
	connect(m_socketHandle, (const sockaddr*)&address, sizeof(address));
}

//Connects the HTTP socket to the specified host
//If the specified hostURL cannot resolve an IPV4 the hostname is used as an IPV4
void HTTPSocket::ConnectTo(const URL& hostURL)
{
	//Create address
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(80);

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

//Connects the HTTP socket to the specified host
//If the specified hostname cannot resolve an IP the hostname is used as an IPV4
void HTTPSocket::ConnectTo(const string& hostname)
{
	//Create address
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(80);

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

//Returns a flag indicating whether the HTTP socket is connected to a host
const bool HTTPSocket::ConnectedToHost()
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

//Disables blocking by the HTTP socket instance
const bool HTTPSocket::DisableBlocking()
{
	//Create non-blocking flag
	DWORD nonBlocking = 1;

	//Disable blocking by the HTTP socket
	if (ioctlsocket(m_socketHandle, FIONBIO, &nonBlocking) == NO_ERROR)
	{
		//Successfully disabled blocking
		return true;
	}

	//Failed to disable blocking
	return false;
}

//Disconnects the HTTP socket from the connected host
const bool HTTPSocket::Disconnect()
{
	//Disconnect the HTTP socket from the connected host
	if (shutdown(m_socketHandle, SD_SEND) == NO_ERROR)
	{
		//Successfully disconnected from the connected host
		return true;
	}

	//Failed to disconnect from the connected host
	return false;
}

//Enables blocking by the HTTP socket instance
const bool HTTPSocket::EnableBlocking()
{
	//Create blocking flag
	DWORD blocking = 0;

	//Enable blocking by the HTTP socket
	if (ioctlsocket(m_socketHandle, FIONBIO, &blocking) == NO_ERROR)
	{
		//Successfully enabled blocking
		return true;
	}

	//Failed to enable blocking
	return false;
}

//Returns the HTTP sockets public IPV4
const IPV4 HTTPSocket::GetPublicIPV4()
{
	//Create intermediary values
	sockaddr_in address;
	int addressLength = sizeof(address);

	//Query the HTTP sockets public address
	getpeername(m_socketHandle, (sockaddr*)&address, &addressLength);

	//Return the HTTP sockets public IPV4
	return IPV4(inet_ntoa(address.sin_addr), ntohs(address.sin_port));
}

//Returns the HTTP sockets private IPV4
const IPV4 HTTPSocket::GetPrivateIPV4()
{
	//Create intermediary values
	sockaddr_in address;
	int addressLength = sizeof(address);

	//Query the HTTP sockets private address
	getsockname(m_socketHandle, (sockaddr*)&address, &addressLength);

	//Return the HTTP sockets private IPV4
	return IPV4(inet_ntoa(address.sin_addr), ntohs(address.sin_port));
}

//Returns the body of the HTTP response
const string HTTPSocket::GetResponseBody()
{
	//Return the response body
	return m_responseBody;
}

//Returns the header of the HTTP response
const string HTTPSocket::GetResponseHeader()
{
	//Return the response header
	return m_responseHeader;
}

//Sends the specified request to the connected host
const bool HTTPSocket::SendRequest(const URL& url)
{
	//Generate HTTP request
	string httpRequest = "GET " + url.GetPath() + " HTTP/1.1\r\n";
	httpRequest += "Host: " + url.GetHostname() + "\r\n";
	httpRequest += "Connection: close\r\n";
	httpRequest += "Accept: text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5\r\n";
	httpRequest += "Accept-Language: fr,fr-fr;q=0.8,en-us;q=0.5,en;q=0.3\r\n";
	httpRequest += "Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7\r\n";
	httpRequest += "User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; fr; rv:1.8.1.3) Gecko/20070309 Firefox/2.0.0.3\r\n";
	httpRequest += "\r\n";

	//Send HTTP request to the connected host
	int sentBytes = send(m_socketHandle, httpRequest.data(), (int)httpRequest.length(), 0);

	//If all of the packet sent
	if (sentBytes == (int)httpRequest.length())
	{
		//successfully sent HTTP request
		return true;
	}

	//Failed to send HTTP request
	return false;
}

//Receives a HTTP response from the connected host
const bool HTTPSocket::ReceiveResponse()
{
	//Create intermediary attributes
	char responseBuffer[1024];
	int responseLength = 0;
	int responseLengthIndex = 0;
	string response = "";

	//While receiving bytes from the connected host
	while ((responseLength = recv(m_socketHandle, responseBuffer, 1024, 0)) > 0)
	{
		//Append the bytes to the response
		response += string(responseBuffer).substr(0, responseLength);
	}

	//If the length of the response is bigger than zero
	if (response.length() > 0)
	{
		//Parse the HTTP response
		ParseResponse(response);

		//Successfully received HTTP response
		return true;
	}

	//Failed to receive HTTP response
	return false;
}

//Parses the specified HTTP response
void HTTPSocket::ParseResponse(const string& response)
{
	//Find response starting index
	size_t responseStartIndex = response.find("\r\n\r\n", 0);

	//If a valid response start index exists
	if (responseStartIndex != string::npos)
	{
		//Store HTTP response header
		m_responseHeader = response.substr(0, responseStartIndex);

		//Increment response start index
		responseStartIndex += 4;

		//If content start code exists
		if (response[responseStartIndex] == '4')
		{
			//Find the HTTP body start index
			size_t bodyStartIndex = response.find("\r\n", responseStartIndex);

			//If a valid body start index exists
			if (bodyStartIndex != string::npos)
			{
				//Increment body start index
				bodyStartIndex += 2;

				//Find the HTTP body end index
				size_t bodyEndIndex = response.find("</html>", responseStartIndex);

				//If a valid body end index exists
				if (bodyEndIndex != string::npos)
				{
					//Increment body end index
					bodyEndIndex += 7;

					//Store HTTP response body
					m_responseBody = response.substr(bodyStartIndex, bodyEndIndex - bodyStartIndex);
				}
				//Otherwise
				else
				{
					//Store HTTP response body
					m_responseBody = response.substr(bodyStartIndex, response.length() - bodyStartIndex);
				}
			}
			//Otherwise
			else
			{
				//Store HTTP response body
				m_responseBody = response.substr(responseStartIndex, response.length() - responseStartIndex);
			}
		}
		//Otherwise
		else
		{
			//Store HTTP response body
			m_responseBody = response.substr(responseStartIndex, response.length() - responseStartIndex);
		}
	}
	//Otherwise
	else
	{
		//Parse response
		m_responseHeader = "";
		m_responseBody = "";
	}
}