//Pragma comments
#pragma once

//External includes
#include <vector>

//Using directives
using std::vector;

//Forward declarations
class DirectionalLight;
class PointLight;

//Singleton class for managing the applications lights
class LightManager
{
public:
	//Returns the directional light at the specified index
	static DirectionalLight* GetDirectionalLightAt(const unsigned int index);

	//Returns the point light at the specified index
	static PointLight* GetPointLightAt(const unsigned int index);

	//Returns the number of directional lights in the applications directional light container
	static const unsigned int GetDirectionalLightCount();

	//Returns the number of point lights in the applications point light container
	static const unsigned int GetPointLightCount();

	//Registers the specified directional light
	static void RegisterDirectionalLight(DirectionalLight* p_directionalLight);

	//Registers the specified point light
	static void RegisterPointLight(PointLight* p_pointLight);

	//Unregisters the specified directional light
	static void UnregisterDirectionalLight(DirectionalLight* p_directionalLight);

	//Unregisters the specified point light
	static void UnregisterPointLight(PointLight* p_pointLight);

private:
	//Container for storing the applications directional lights
	static vector<DirectionalLight*> m_directionalLightContainer;

	//Container for storing the applications point lights
	static vector<PointLight*> m_pointLightContainer;
};