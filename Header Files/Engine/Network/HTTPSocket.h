//Pragma comments
#pragma once

//Internal includes
#include "IPV4.h"
#include "URL.h"

//External includes
#include <string>

//Using directives
using std::string;

//Object with various functions for transferring data on networks using the hypertext transfer protocol
class HTTPSocket
{
public:
	//Creates and initializes a HTTP socket instance
	HTTPSocket();

	//Opens the HTTP socket using any available IPV4 and port
	const bool Open();

	//Opens the HTTP socket using the specified IPV4
	const bool Open(const IPV4& ipv4);

	//Opens the HTTP socket using any available IPV4 and the specified port
	const bool Open(const unsigned short port);

	//Opens the HTTP socket using the specified IPV4 and any available port
	const bool Open(const string& ipv4);

	//Opens the HTTP socket using the specified IPV4 and port
	const bool Open(const string& ipv4, const unsigned short port);

	//Closes the HTTP socket instance
	const bool Close();

	//Connects the HTTP socket to the specified host
	void ConnectTo(const IPV4& ipv4);

	//Connects the HTTP socket to the specified host
	//If the specified hostURL cannot resolve an IPV4 the hostname is used as an IPV4
	void ConnectTo(const URL& hostURL);

	//Connects the HTTP socket to the specified host
	//If the specified hostname cannot resolve an IPV4 the hostname is used as an IPV4
	void ConnectTo(const string& hostname);

	//Returns a flag indicating whether the HTTP socket is connected to a host
	const bool ConnectedToHost();

	//Disables blocking by the HTTP socket instance
	const bool DisableBlocking();

	//Disconnects the HTTP socket from the connected host
	const bool Disconnect();

	//Enables blocking by the HTTP socket instance
	const bool EnableBlocking();

	//Returns the HTTP sockets public IPV4
	const IPV4 GetPublicIPV4();

	//Returns the HTTP sockets private IPV4
	const IPV4 GetPrivateIPV4();

	//Returns the body of the HTTP response
	const string GetResponseBody();

	//Returns the header of the HTTP response
	const string GetResponseHeader();

	//Sends the specified request to the connected host
	const bool SendRequest(const URL& url);

	//Receives a HTTP response from the connected host
	const bool ReceiveResponse();

protected:
	//Parses the specified HTTP response
	void ParseResponse(const string& response);

private:
	//HTTP socket handle
	int m_socketHandle;

	//HTTP response body
	string m_responseBody;

	//HTTP response header
	string m_responseHeader;
};