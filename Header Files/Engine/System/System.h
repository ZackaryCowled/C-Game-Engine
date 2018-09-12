//Pragma comments
#pragma once

//External includes
#include <string>

//Using directives
using std::string;

//Singleton object with functions for querying and manipulating the system
class System
{
public:
	//Returns the name for the computer
	static string GetComputersName();

	//Returns the width of the computers primary monitor in pixels as a integer
	static int GetPrimaryMonitorWidthi();

	//Returns the width of the computers primary monitor in pixels as a float
	static float GetPrimaryMonitorWidthf();

	//Returns the height of the computers primary monitor in pixels as a integer
	static int GetPrimaryMonitorHeighti();

	//Returns the height of the computers primary monitor in pixels as a float
	static float GetPrimaryMonitorHeightf();
};