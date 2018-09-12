//Internal includes
#include "Application.h"

//Initialize static post process manager attributes
float PostProcessManager::m_distort = 0.0f;

//Returns the distort value for post-processing
const float PostProcessManager::GetDistort()
{
	//Return the post-process distort value
	return m_distort;
}

//Sets the distort value for post-processing to the specified distort value
void PostProcessManager::SetDistort(const float distort)
{
	//Set the post-process distort value to the specified distort value
	m_distort = distort;
}