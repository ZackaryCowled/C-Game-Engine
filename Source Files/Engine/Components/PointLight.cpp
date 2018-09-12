//Internal includes
#include "Application.h"

//Creates and initializes a PointLight instance (Default constructor)
PointLight::PointLight()
{
	//Initialize PointLight
	m_position = vec3(0.0f, 0.0f, 0.0f);
	m_color = vec3(1.0f, 1.0f, 1.0f);
	m_intensity = 1.0f;
	SetType(COMPONENT_TYPE_POINT_LIGHT);
	LightManager::RegisterPointLight(this);
}

//Releases the point lights resources
PointLight::~PointLight()
{
	//Unregister the point light
	LightManager::UnregisterPointLight(this);
}

//Returns the position of the point light
vec3 PointLight::GetPosition()
{
	//Return the position of the point light
	return m_position;
}

//Returns the color of the point light
vec3 PointLight::GetColor()
{
	//Return the color of the point light
	return m_color;
}

//Returns the point lights intensity
float PointLight::GetIntensity()
{
	//Return the intensity of the point light
	return m_intensity;
}

//Sets the position of the point light to the specified position
void PointLight::SetPosition(const vec3& position)
{
	//Set the position of the point light to the specified position
	m_position = position;
}

//Sets the color of the point light to the specified color
void PointLight::SetColor(const vec3& color)
{
	//Set the color of the point light to the specified color
	m_color = color;
}

//Sets the point lights intensity to the specified intensity
void PointLight::SetIntensity(const float intensity)
{
	//Set the point lights intensity to the specified intensity
	m_intensity = intensity;
}