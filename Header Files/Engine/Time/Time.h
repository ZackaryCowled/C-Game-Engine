//Pragma comments
#pragma once

//External includes
#include <chrono>

//Singleton object with various functions for querying and updating the applications time information
class Time
{
public:
	//The amount of time the application has been running
	static float runTime;

	//The number of nanoseconds the previous frame used
	static float deltaTime;

	//Updates the applications time attributes
	static void UpdateTimeAttributes();

private:
	//Time stamp that is recorded at the beginning of each frame
	static std::chrono::time_point<std::chrono::steady_clock> m_frameStartTime;

	//Time stamp that is recorded at the end of each frame
	static std::chrono::time_point<std::chrono::steady_clock> m_frameEndTime;
};