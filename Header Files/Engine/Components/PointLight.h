//Pragma comments
#pragma once

//Internal includes
#include "Component.h"

//External includes
#include <glm\glm.hpp>

//Using directives
using namespace glm;

//Object representing a point light in 3D space
class PointLight : public Component
{
public:
	//Creates and initializes a PointLight instance (Default constructor)
	PointLight();

	//Releases the point lights resources
	~PointLight();

	//Returns the position of the point light
	vec3 GetPosition();

	//Returns the color of the point light
	vec3 GetColor();

	//Returns the point lights intensity
	float GetIntensity();

	//Sets the position of the point light to the specified position
	void SetPosition(const vec3& position);

	//Sets the color of the point light to the specified color
	void SetColor(const vec3& color);

	//Sets the point lights intensity to the specified intensity
	void SetIntensity(const float intensity);

private:
	//The lights position
	vec3 m_position;

	//The lights color
	vec3 m_color;

	//The lights intensity
	float m_intensity;
};