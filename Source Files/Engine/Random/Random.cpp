//Internal includes
#include "Random.h"
#include "Application.h"

//Initializes Random
void Random::Initialize()
{
	//Initilaize random seed
	srand((unsigned int)time(NULL));
}

//Returns a random float between 0.0f and 1.0f
float Random::NormalizedFloat()
{
	//Return a float between 0.0f and 1.0f
	return (float)rand() / (RAND_MAX + 1.0f);
}

//Returns a random integer inside the range
int Random::IntegerInsideRange(const int min, const int max)
{
	//Return random integer inside the range
	return rand() % (max - min + 1) + min;
}

//Returns a random float inside the range
float Random::FloatInsideRange(const float min, const float max)
{
	//Return a random float between the min and max range
	return (max - min) * ((((float)rand()) / (float)RAND_MAX)) + min;
}

//Returns a random point inside a unit sphere
vec3 Random::PointInsideUnitSphere(const float sphereRadius)
{
	//Create temporary attributes for generating a random point inside the unit sphere
	vec3 point = vec3(FloatInsideRange(-sphereRadius, sphereRadius), FloatInsideRange(-sphereRadius, sphereRadius), FloatInsideRange(-sphereRadius, sphereRadius));
	float sphereRadiusSquared = sphereRadius * sphereRadius;

	//Until the point is inside the unit sphere
	while (point.x * point.x + point.y * point.y + point.z * point.z > sphereRadiusSquared)
	{
		//Get new random point
		point = vec3(FloatInsideRange(-sphereRadius, sphereRadius), FloatInsideRange(-sphereRadius, sphereRadius), FloatInsideRange(-sphereRadius, sphereRadius));
	}

	//Return the point
	return point;
}