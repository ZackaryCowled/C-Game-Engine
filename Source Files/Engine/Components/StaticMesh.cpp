//Internal includes
#include "StaticMesh.h"
#include "Application.h"

//External includes
#include <GL\glew.h>
#include <vector>

//Using directives
using std::vector;

//Creates and initializes a StaticMesh instance (Default constructor)
StaticMesh::StaticMesh()
{
	//Initialize static mesh
	m_vertexArrayObject = 0;
	m_numberOfIndices = 0;
	m_boundingSphereRadius = 0.0f;
	m_boundingSphereCentre = vec3(0.0f);
	SetType(COMPONENT_TYPE_STATIC_MESH);
}

//Releases static mesh resources
StaticMesh::~StaticMesh()
{
	//Destroy the mesh
	Destroy();
}

//Destroys the mesh
void StaticMesh::Destroy()
{
	//If the mesh has a valid vertex array object
	if (m_vertexArrayObject != 0)
	{
		//Delete the vertex array object
		glDeleteVertexArrays(1, &m_vertexArrayObject);

		//Set the number of indices that make the mesh to zero
		m_numberOfIndices = 0;
	}
}

//Returns the meshes bounding sphere radius
float StaticMesh::GetBoundingSphereRadius()
{
	//Return the meshes bounding sphere radius
	return m_boundingSphereRadius;
}

//Returns the local bounding sphere centre for the mesh
vec3 StaticMesh::GetLocalBoundingSphereCentre()
{
	//Return the meshes local bounding sphere centre
	return m_boundingSphereCentre;
}

//Loads the specified mesh
//meshFilepath - The location, name and file extension for the mesh file
void StaticMesh::LoadMesh(const string& meshFilepath)
{
	//Load the mesh file
	File meshFile = FileImporter::ImportFile(meshFilepath);

	//Parse mesh file header attributes
	m_boundingSphereRadius = stof(meshFile.GetLine());
	m_boundingSphereCentre.x = stof(meshFile.GetLine());
	m_boundingSphereCentre.y = stof(meshFile.GetLine());
	m_boundingSphereCentre.z = stof(meshFile.GetLine());
	unsigned int numberOfVertices = (unsigned int)stoi(meshFile.GetLine());
	m_numberOfIndices = (unsigned int)stoi(meshFile.GetLine());

	//Create container for the vertex buffer objects data
	vector<float> vertexBufferDataContainer = vector<float>();
	vertexBufferDataContainer.reserve(numberOfVertices * 14);

	//Create container for the indice buffer objects data
	vector<unsigned int> indiceBufferDataContainer = vector<unsigned int>();
	indiceBufferDataContainer.reserve(m_numberOfIndices);

	//For each vertex that makes up the mesh
	for (unsigned int vertexIndex = 0; vertexIndex < numberOfVertices; vertexIndex++)
	{
		//Add the vertex data to the vertex buffer data object
		vertexBufferDataContainer.push_back(stof(meshFile.GetLine()));
		vertexBufferDataContainer.push_back(stof(meshFile.GetLine()));
		vertexBufferDataContainer.push_back(stof(meshFile.GetLine()));
		vertexBufferDataContainer.push_back(stof(meshFile.GetLine()));
		vertexBufferDataContainer.push_back(stof(meshFile.GetLine()));
		vertexBufferDataContainer.push_back(stof(meshFile.GetLine()));
		vertexBufferDataContainer.push_back(stof(meshFile.GetLine()));
		vertexBufferDataContainer.push_back(stof(meshFile.GetLine()));
		vertexBufferDataContainer.push_back(stof(meshFile.GetLine()));
		vertexBufferDataContainer.push_back(stof(meshFile.GetLine()));
		vertexBufferDataContainer.push_back(stof(meshFile.GetLine()));
		vertexBufferDataContainer.push_back(stof(meshFile.GetLine()));
		vertexBufferDataContainer.push_back(stof(meshFile.GetLine()));
		vertexBufferDataContainer.push_back(stof(meshFile.GetLine()));
	}

	//For each indice that makes up the mesh
	for (unsigned int indiceIndex = 0; indiceIndex < m_numberOfIndices; indiceIndex++)
	{
		//Add the indice data to the indice buffer data object
		indiceBufferDataContainer.push_back((unsigned int)stoi(meshFile.GetLine()));
	}

	//Destroy the mesh
	Destroy();

	//Create buffer objects
	unsigned int vertexBufferObject = 0;
	unsigned int indiceBufferObject = 0;

	//Generate buffer objects
	glGenBuffers(1, &vertexBufferObject);
	glGenBuffers(1, &indiceBufferObject);

	//Generate vertex array object
	glGenVertexArrays(1, &m_vertexArrayObject);

	//Bind vertex array object
	glBindVertexArray(m_vertexArrayObject);

	//Bind vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

	//Set vertex buffer object data
	glBufferData(GL_ARRAY_BUFFER, vertexBufferDataContainer.size() * sizeof(float), vertexBufferDataContainer.data(), GL_STATIC_DRAW);

	//Enable vertex buffer attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);

	//Specify memory layout of the vertex buffer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 14, (void*)(sizeof(float) * 0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 14, (void*)(sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 14, (void*)(sizeof(float) * 6));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 14, (void*)(sizeof(float) * 9));
	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 14, (void*)(sizeof(float) * 12));

	//Bind indice buffer object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiceBufferObject);

	//Set indice buffer object data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceBufferDataContainer.size() * sizeof(unsigned int), indiceBufferDataContainer.data(), GL_STATIC_DRAW);

	//Unbind the vertex array object
	glBindVertexArray(0);

	//Unbind buffer objects
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//Delete buffer objects
	glDeleteBuffers(1, &vertexBufferObject);
	glDeleteBuffers(1, &indiceBufferObject);
}

//Renders the mesh
void StaticMesh::Render()
{
	//If the mesh has a valid vertex array object
	if (m_vertexArrayObject != 0)
	{
		//Bind the meshes vertex array object
		glBindVertexArray(m_vertexArrayObject);

		//Draw the mesh
		glDrawElements(GL_TRIANGLES, m_numberOfIndices, GL_UNSIGNED_INT, 0);

		//Unbind the meshes vertex array object
		glBindVertexArray(0);
	}
}