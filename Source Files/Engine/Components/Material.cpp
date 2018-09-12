//Internal includes
#include "Material.h"
#include "Application.h"

//Creates and initializes a Material instance (Default constructor)
Material::Material()
{
	//Initialize Material
	m_diffuseMapTextureSampler = 0;
	m_normalMapTextureSampler = 0;
	m_roughness = 0.05f;
	m_reflectiveness = 0.99f;
	SetType(COMPONENT_TYPE_MATERIAL);
}

//Returns the materials diffuse map texture sampler
const unsigned int Material::GetDiffuseMapTextureSampler()
{
	//Return the materials diffuse map texture sampler
	return m_diffuseMapTextureSampler;
}

//Returns the materials normal map texture sampler
const unsigned int Material::GetNormalMapTextureSampler()
{
	//Return the materials normal map texture sampler
	return m_normalMapTextureSampler;
}

//Returns the materials roughness
const float Material::GetRoughness()
{
	//Return the materials roughness
	return m_roughness;
}

//Returns the materials reflectiveness
const float Material::GetReflectiveness()
{
	//Return the materials reflectiveness
	return m_reflectiveness;
}

//Sets the materials diffuse map texture sampler to use the specified texture
//textureFilepath - The location, name and file extension of the texture
void Material::SetDiffuseMapTextureSampler(const string& textureFilepath)
{
	//Load the specified texture
	m_diffuseMapTextureSampler = TextureManager::LoadTexture(textureFilepath);
}

//Sets the materials normal map texture sampler to use the specified texture
//textureFilepath - The location, name and file extension of the texture
void Material::SetNormalMapTextureSampler(const string& textureFilepath)
{
	//Load the specified texture
	m_normalMapTextureSampler = TextureManager::LoadTexture(textureFilepath);
}

//Sets the materials roughness to the specified roughness
void Material::SetRoughness(const float roughness)
{
	//Set the materials roughness to the specified roughness
	m_roughness = roughness;
}

//Sets the materials reflectiveness to the specified reflectiveness
void Material::SetReflectiveness(const float reflectiveness)
{
	//Set the materials reflectiveness to the specified reflectiveness
	m_reflectiveness = reflectiveness;
}