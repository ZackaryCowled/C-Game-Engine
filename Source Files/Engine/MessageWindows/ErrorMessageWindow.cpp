//Internal includes
#include "ErrorMessageWindow.h"

//External includes
#include <Windows.h>

//Creates an error message window with the specified title and message
ErrorMessageWindow::ErrorMessageWindow(const string& title, const string& message)
{
	//Create and display error message window
	MessageBox(NULL, message.c_str(), title.c_str(), MB_ICONERROR);
}