//Precompiler definitions
#define _WINSOCK_DEPRECATED_NO_WARNINGS

//Internal includes
#include "IPV4.h"

//External includes
#include <cstring>
#include <WinSock2.h>

//Precompiler undefines
#undef SetPort

//Creates and initializes an IPV4 instance
IPV4::IPV4()
{
	//Initialize IPV4
	m_address = IPV4_ANY_ADDRESS;
	m_port = IPV4_ANY_PORT;
}

//Creates and initializes an IPV4 instance using the specified address and any available port
IPV4::IPV4(const string& address)
{
	//Initialize IPV4
	m_address = address;
	m_port = IPV4_ANY_PORT;
}

//Creates and initializes an IPV4 instance using any available address and the specified port
IPV4::IPV4(const unsigned short port)
{
	//Initialize IPV4
	m_address = IPV4_ANY_ADDRESS;
	m_port = port;
}

//Creates and initializes an IPV4 using the specified address and port
IPV4::IPV4(const string& address, const unsigned short port)
{
	//Initialize IPV4
	m_address = address;
	m_port = port;
}

//Creates and initializes an IPV4 using the specified URL and any available port
IPV4::IPV4(const URL& url)
{
	//Query host data
	hostent* hostData = gethostbyname(url.GetHostname().c_str());

	//If the host data query was successful
	if (hostData != nullptr)
	{
		//Create address
		sockaddr_in address;
		address.sin_addr.s_addr = *(u_long*)hostData->h_addr_list[0];

		//Initialize IPV4
		m_address = inet_ntoa(address.sin_addr);
		m_port = IPV4_ANY_PORT;
	}
	//Otherwise
	else
	{
		//Initialize IPV4
		m_address = IPV4_ANY_ADDRESS;
		m_port = IPV4_ANY_PORT;
	}
}

//Creates and initializes an IPV4 using the specified URL and port
IPV4::IPV4(const URL& url, const unsigned short port)
{
	//Query host data
	hostent* hostData = gethostbyname(url.GetHostname().c_str());

	//If the host data query was successful
	if (hostData != nullptr)
	{
		//Create address
		sockaddr_in address;
		address.sin_addr.s_addr = *(u_long*)hostData->h_addr_list[0];

		//Initialize IPV4
		m_address = inet_ntoa(address.sin_addr);
		m_port = port;
	}
	//Otherwise
	else
	{
		//Initialize IPV4
		m_address = IPV4_ANY_ADDRESS;
		m_port = port;
	}
}

//Returns the IPV4 address value
const string& IPV4::GetAddress() const
{
	//Return the IPV4 address value
	return m_address;
}

//Returns the IPV4 port value
const unsigned short IPV4::GetPort() const
{
	//Return the IPV4 port value
	return m_port;
}

//Sets the IPV4 to the specified address and port
void IPV4::Set(const string& address, const unsigned short port)
{
	//Set the IPV4 address and port to the specified address and port
	m_address = address;
	m_port = port;
}

//Sets the IPV4 address to the specified address
void IPV4::SetAddress(const string& address)
{
	//Set the IPV4 address to the specified address
	m_address = address;
}

//Sets the IPV4 port to the specified port
void IPV4::SetPort(const unsigned short port)
{
	//Set the IPV4 port to the specified port
	m_port = port;
}