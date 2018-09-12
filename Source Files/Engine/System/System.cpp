//Internal includes
#include "System.h"

//External includes
#include <Windows.h>

//Returns the name for the computer
string System::GetComputersName()
{
	//Create character buffer for storing the computers name
	TCHAR characterBuffer[MAX_COMPUTERNAME_LENGTH + 1];

	//Create buffer size attribute for storing the number of characters in the character buffer
	DWORD bufferSize = MAX_COMPUTERNAME_LENGTH + 1;

	//Store the computers name and name length in the character buffer and buffer size attribute
	GetComputerName(characterBuffer, &bufferSize);

	//Return the name of the computer
	return characterBuffer;
}

//Returns the width of the computers primary monitor in pixels as a integer
int System::GetPrimaryMonitorWidthi()
{
	//Return the width of the computers primary monitor
	return GetSystemMetrics(SM_CXSCREEN);
}

//Returns the width of the computers primary monitor in pixels as a float
float System::GetPrimaryMonitorWidthf()
{
	//Return the width of the computers primary monitor
	return (float)GetSystemMetrics(SM_CXSCREEN);
}

//Returns the height of the computers primary monitor in pixels as a integer
int System::GetPrimaryMonitorHeighti()
{
	//Return the height of the computers primary monitor
	return GetSystemMetrics(SM_CYSCREEN);
}

//Returns the height of the computers primary monitor in pixels as a float
float System::GetPrimaryMonitorHeightf()
{
	//Return the height of the computers primary monitor
	return (float)GetSystemMetrics(SM_CYSCREEN);
}