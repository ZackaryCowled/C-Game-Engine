//Pragma comments
#pragma once

//Precompiler definitions
#define IPV4_ANY_ADDRESS "0.0.0.0"
#define IPV4_ANY_PORT 0

//Internal includes
#include "URL.h"

//External includes
#include <string>

//Using directives
using std::string;

//Object with various functions for controlling an setting and getting IPV4 attributes
class IPV4
{
public:
	//Creates and initializes an IPV4 instance
	IPV4();

	//Creates and initializes an IPV4 instance using the specified address and any available port
	IPV4(const string& address);

	//Creates and initializes an IPV4 instance using any available address and the specified port
	IPV4(const unsigned short port);

	//Creates and initializes an IPV4 using the specified address and port
	IPV4(const string& address, const unsigned short port);

	//Creates and initializes an IPV4 using the specified URL and any available port
	IPV4(const URL& url);

	//Creates and initializes an IPV4 using the specified URL and port
	IPV4(const URL& url, const unsigned short port);

	//Returns the IPV4 address value
	const string& GetAddress() const;

	//Returns the IPV4 port value
	const unsigned short GetPort() const;

	//Sets the IPV4 to the specified address and port
	void Set(const string& address, const unsigned short port);

	//Sets the IPV4 address to the specified address
	void SetAddress(const string& address);

	//Sets the IPV4 port to the specified port
	void SetPort(const unsigned short port);

private:
	//Address value
	string m_address;

	//Port value
	unsigned short m_port;
};