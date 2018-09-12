//Internal includes
#include "Time.h"

//Initializes frame time stamps
std::chrono::time_point<std::chrono::steady_clock> InitializeTimeStamp()
{
	//Return the current high resolution time
	return std::chrono::high_resolution_clock::now();
}

//Initialize static time attributes
float Time::runTime(0.0f);
float Time::deltaTime(0.0f);
std::chrono::time_point<std::chrono::steady_clock> Time::m_frameStartTime(InitializeTimeStamp());
std::chrono::time_point<std::chrono::steady_clock> Time::m_frameEndTime(InitializeTimeStamp());

//Updates the applications time attributes
void Time::UpdateTimeAttributes()
{
	//Set the frame end time
	m_frameEndTime = std::chrono::high_resolution_clock::now();

	//Update delta time
	deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(m_frameEndTime - m_frameStartTime).count();

	//Update run time
	runTime += deltaTime;

	//Set the frame start time to the frame end time
	m_frameStartTime = m_frameEndTime;
}