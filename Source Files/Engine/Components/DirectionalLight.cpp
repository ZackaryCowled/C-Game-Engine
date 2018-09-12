//Internal includes
#include "Application.h"

//Creates and initializes a DirectionalLight instance (Default constructor)
DirectionalLight::DirectionalLight()
{
	//Initialize DirectionalLight
	m_position = vec3(-50.0f, 30.0f, 0.0f);
	m_color = vec3(1.0f, 1.0f, 1.0f);
	m_intensity = 1.0f;
	SetType(COMPONENT_TYPE_DIRECTIONAL_LIGHT);
	LightManager::RegisterDirectionalLight(this);
}

//Releases the directional lights resources
DirectionalLight::~DirectionalLight()
{
	//Unregister the directional light
	LightManager::UnregisterDirectionalLight(this);
}

//Returns the position of the directional light
vec3 DirectionalLight::GetPosition()
{
	//Return the position of the directional light
	return m_position;
}

//Returns the color of the directional light
vec3 DirectionalLight::GetColor()
{
	//Return the color of the directional light
	return m_color;
}

//Returns the intensity of the directional light
float DirectionalLight::GetIntensity()
{
	//Return the intensity of the directional light
	return m_intensity;
}

//Sets the position of the directional light to the specified position
void DirectionalLight::SetPosition(const vec3& position)
{
	//Set the directional lights position to the specified position
	m_position = position;
}

//Sets the color of the directional light to the specified color
void DirectionalLight::SetColor(const vec3& color)
{
	//Set the color of the directional light to the specified color
	m_color = color;
}

//Sets the directional lights intensity to the specified intensity
void DirectionalLight::SetIntensity(const float intensity)
{
	//Set the intensity of the directional light to the specified intensity
	m_intensity = intensity;
}