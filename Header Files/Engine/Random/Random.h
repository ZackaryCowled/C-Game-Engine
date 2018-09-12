//Pragma comments
#pragma once

//External includes
#include <glm/glm.hpp>

//Using directives
using namespace glm;

//Singleton class providing various functions for retrieving random values
class Random
{
public:
	//Initializes Random
	static void Initialize();

	//Returns a random float between 0.0f and 1.0f
	static float NormalizedFloat();

	//Returns a random integer inside the range
	static int IntegerInsideRange(const int min, const int max);

	//Returns a random float inside the range
	static float FloatInsideRange(const float min, const float max);

	//Returns a random point inside a unit sphere
	static vec3 PointInsideUnitSphere(const float sphereRadius);
};