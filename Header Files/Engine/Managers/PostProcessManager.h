//Pragma comments
#pragma once

//Singleton class providing various functions for altering the way the applications post-processing is applied
class PostProcessManager
{
public:
	//Returns the distort value for post-processing
	static const float GetDistort();

	//Sets the distort value for post-processing to the specified distort value
	static void SetDistort(const float distort);

private:
	//Distort value (Wave like effect)
	static float m_distort;
};