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

//Object used for storing a GameObjects mesh data
class StaticMesh : public Component
{
public:
	//Creates and initializes a StaticMesh instance (Default constructor)
	StaticMesh();

	//Releases static mesh resources
	~StaticMesh();

	//Destroys the mesh
	void Destroy();

	//Returns the meshes bounding sphere radius
	float GetBoundingSphereRadius();

	//Returns the local bounding sphere centre for the mesh
	vec3 GetLocalBoundingSphereCentre();

	//Loads the specified mesh
	//meshFilepath - The location, name and file extension for the mesh file
	void LoadMesh(const string& meshFilepath);

	//Renders the mesh
	void Render();

private:
	//The meshes vertex array object
	unsigned int m_vertexArrayObject;

	//The number of indices that make up the mesh
	unsigned int m_numberOfIndices;

	//The radius of the mesh bounding sphere
	float m_boundingSphereRadius;

	//The centre of the mesh bounding sphere
	vec3 m_boundingSphereCentre;
};