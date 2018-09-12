//Internal includes
#include "URL.h"

//Creates and initializes a URL instance
URL::URL()
{
	//Initialize URL
	m_hostname = "";
	m_path = "/";
}

//Creates and initializes a URL instance with the specified URL
URL::URL(const string& url)
{
	//Initialize URL
	Set(url);
}

//Returns the URL hostname
const string URL::GetHostname() const
{
	//Return the URL hostname
	return m_hostname;
}

//Returns the URL path
const string URL::GetPath() const
{
	//Return the URL path
	return m_path;
}

//Sets the URL to the specified URL
void URL::Set(const string& url)
{
	//Find the path starting index in the specified URL
	size_t pathStartIndex = url.find('/', 0);

	//If the specified URL has a valid path
	if (pathStartIndex != string::npos)
	{
		//Parse URL
		m_hostname = url.substr(0, pathStartIndex);
		m_path = url.substr(pathStartIndex, url.length() - pathStartIndex);
	}
	//Otherwise
	else
	{
		//Parse URL
		m_hostname = url;
		m_path = "/";
	}
}

//Sets the URL hostname to the specified hostname
void URL::SetHostname(const string& hostname)
{
	//Set the URL hostname to the specified hostname
	m_hostname = hostname;
}

//Sets the URL path to the specified path
void URL::SetPath(const string& path)
{
	//Set the URL path to the specified path
	m_path = path;
}