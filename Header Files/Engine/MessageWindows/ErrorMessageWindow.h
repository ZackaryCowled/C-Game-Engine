//Pragma comments
#pragma once

//External includes
#include <string>

//Using directives
using std::string;

//Object that displays information in a system window about an error that occured
class ErrorMessageWindow
{
public:
	//Creates an error message window with the specified title and message
	ErrorMessageWindow(const string& title, const string& message);
};