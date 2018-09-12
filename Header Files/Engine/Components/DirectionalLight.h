//Pragma comments
#pragma once

//Internal includes
#include "Component.h"

//External includes
#include <glm\glm.hpp>

//Using directives
using namespace glm;

//Object representing a directional light in 3D space
class DirectionalLight : public Component
{
public:
	//Creates and initializes a DirectionalLight instance (Default constructor)
	DirectionalLight();

	//Releases the directional lights resources
	~DirectionalLight();

	//Returns the position of the directional light
	vec3 GetPosition();

	//Returns the color of the directional light
	vec3 GetColor();

	//Returns the intensity of the directional light
	float GetIntensity();

	//Sets the position of the directional light to the specified position
	void SetPosition(const vec3& position);

	//Sets the color of the directional light to the specified color
	void SetColor(const vec3& color);

	//Sets the directional lights intensity to the specified intensity
	void SetIntensity(const float intensity);

private:
	//The lights position
	vec3 m_position;

	//The lights color
	vec3 m_color;

	//The lights intensity
	float m_intensity;
};