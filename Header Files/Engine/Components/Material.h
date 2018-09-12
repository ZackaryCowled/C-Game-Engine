//Pragma comments
#pragma once

//Internal includes
#include "Component.h"

//External includes
#include <glm\glm.hpp>
#include <string>

//Using directives
using namespace glm;
using std::string;

//Object with various functions for setting up how an object is to be shaded
class Material : public Component
{
public:
	//Creates and initializes a Material instance (Default constructor)
	Material();

	//Returns the materials diffuse map texture sampler
	const unsigned int GetDiffuseMapTextureSampler();

	//Returns the materials normal map texture sampler
	const unsigned int GetNormalMapTextureSampler();

	//Returns the materials roughness
	const float GetRoughness();

	//Returns the materials reflectiveness
	const float GetReflectiveness();

	//Sets the materials diffuse map texture sampler to use the specified texture
	//textureFilepath - The location, name and file extension of the texture
	void SetDiffuseMapTextureSampler(const string& textureFilepath);

	//Sets the materials normal map texture sampler to use the specified texture
	//textureFilepath - The location, name and file extension of the texture
	void SetNormalMapTextureSampler(const string& textureFilepath);

	//Sets the materials roughness to the specified roughness
	void SetRoughness(const float roughness);

	//Sets the materials reflectiveness to the specified reflectiveness
	void SetReflectiveness(const float reflectiveness);

private:
	//Diffuse map texture sampler
	unsigned int m_diffuseMapTextureSampler;

	//Normal map texture sampler
	unsigned int m_normalMapTextureSampler;

	//Materials roughness
	float m_roughness;

	//Materials reflectiveness
	float m_reflectiveness;
};