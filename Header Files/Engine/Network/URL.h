//Pragma comments
#pragma once

//External includes
#include <string>

//Using directives
using std::string;

//Object with various functions for setting and getting URL attributes
class URL
{
public:
	//Creates and initializes a URL instance
	URL();

	//Creates and initializes a URL instance with the specified URL
	URL(const string& url);

	//Returns the URL hostname
	const string GetHostname() const;

	//Returns the URL path
	const string GetPath() const;

	//Sets the URL to the specified URL
	void Set(const string& url);

	//Sets the URL hostname to the specified hostname
	void SetHostname(const string& hostname);

	//Sets the URL path to the specified path
	void SetPath(const string& path);

private:
	//Hostname
	string m_hostname;

	//Path
	string m_path;
};