//Internal includes
#include "Application.h"

//Initialize static light manager attributes
vector<DirectionalLight*> LightManager::m_directionalLightContainer = vector<DirectionalLight*>();
vector<PointLight*> LightManager::m_pointLightContainer = vector<PointLight*>();

//Returns the directional light at the specified index
DirectionalLight* LightManager::GetDirectionalLightAt(const unsigned int index)
{
	//Return the directional light at the specified index in the applications directional light container
	return m_directionalLightContainer[index];
}

//Returns the point light at the specified index
PointLight* LightManager::GetPointLightAt(const unsigned int index)
{
	//Return the point light at the specified index in the applications point light container
	return m_pointLightContainer[index];
}

//Returns the number of directional lights in the applications directional light container
const unsigned int LightManager::GetDirectionalLightCount()
{
	//Return the number of directional lights in the applications directional light container
	return (unsigned int)m_directionalLightContainer.size();
}

//Returns the number of point lights in the applications point light container
const unsigned int LightManager::GetPointLightCount()
{
	//Return the number of point lights in the applications point light container
	return (unsigned int)m_pointLightContainer.size();
}

//Registers the specified directional light
void LightManager::RegisterDirectionalLight(DirectionalLight* p_directionalLight)
{
	//Register the specified directional light
	m_directionalLightContainer.push_back(p_directionalLight);
}

//Registers the specified point light
void LightManager::RegisterPointLight(PointLight* p_pointLight)
{
	//Register the specified point light
	m_pointLightContainer.push_back(p_pointLight);
}

//Unregisters the specified directional light
void LightManager::UnregisterDirectionalLight(DirectionalLight* p_directionalLight)
{
	//For each directional light in the applications directional light container
	for (unsigned int directionalLightIndex = 0; directionalLightIndex < m_directionalLightContainer.size(); ++directionalLightIndex)
	{
		//If the directional light is the specified light
		if (m_directionalLightContainer[directionalLightIndex] == p_directionalLight)
		{
			//Erase the directional light from the applications directional light container
			m_directionalLightContainer.erase(m_directionalLightContainer.begin() + directionalLightIndex);

			//Return from the function
			return;
		}
	}
}

//Unregisters the specified point light
void LightManager::UnregisterPointLight(PointLight* p_pointLight)
{
	//For each point light in the applications point light container
	for (unsigned int pointLightIndex = 0; pointLightIndex < m_pointLightContainer.size(); ++pointLightIndex)
	{
		//If the point light is the specified light
		if (m_pointLightContainer[pointLightIndex] == p_pointLight)
		{
			//Erase the point light from the applications point light container
			m_pointLightContainer.erase(m_pointLightContainer.begin() + pointLightIndex);

			//Return from the function
			return;
		}
	}
}