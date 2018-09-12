//Pragma comments
#pragma once

//External includes
#include <glm\glm.hpp>
#include <map>
#include <string>
#include <vector>

//Using directives
using namespace glm;
using std::map;
using std::pair;
using std::string;
using std::vector;

//Structure encapsulating a shader uniform attribute
template<class DataType> class ShaderAttribute
{
public:
	//Creates and initializes a Shader attribute instance (Default constructor)
	ShaderAttribute() : uniformLocation(0), value(DataType()) {}

	//The location of the uniform attribute
	unsigned int uniformLocation;

	//Pointer to the uniform attribute value
	DataType value;
};

//Object providing a way to create and update a shader
class Shader
{
public:
	//Creates and initializes a Shader instance (Default constructor)
	Shader();

	//Creates and initializes a Shader instance
	//vertexShaderFilepath - The location, name and file extension to the vertex shader file
	//transformFeedbackAttributeNames - list of attributes to stream back from the shader
	Shader(const string& vertexShaderFilepath, vector<const char*> transformFeedbackAttributeNames);

	//Creates and initializes a Shader instance
	//vertexShaderFilepath - The location, name and file extension to the vertex shader file
	//fragmentShaderFilepath - The location, name and file extension to the fragment shader file
	Shader(const string& vertexShaderFilepath, const string& fragmentShaderFilepath);

	//Creates and initializes a Shader instance
	//vertexShaderFilepath - The location, name and file extension to the vertex shader file
	//geometryShaderFilepath - The location, name and file extension to the geometry shader file
	//fragmentShaderFilepath - The location, name and file extension to the fragment shader file
	Shader(const string& vertexShaderFilepath, const string& geometryShaderFilepath, const string& fragmentShaderFilepath);

	//Creates a float uniform attribute for the shader with the specified uniform attribute name
	//uniformAttributeName - The name of the uniform attribute to create
	void CreateAttributeFloat(const string& uniformAttributeName);

	//Creates a vector 2 uniform attribute for the shader with the specified uniform attribute name
	//uniformAttributeName - The name of the uniform attribute to create
	void CreateAttributeVector2(const string& uniformAttributeName);

	//Creates a vector 3 uniform attribute for the shader with the specified uniform attribute name
	//uniformAttributeName - The name of the uniform attribute to create
	void CreateAttributeVector3(const string& uniformAttributeName);

	//Creates a vector 4 uniform attribute for the shader with the specified uniform attribute name
	//uniformAttributeName - The name of the uniform attribute to create
	void CreateAttributeVector4(const string& uniformAttributeName);

	//Creates a matrix 3x3 uniform attribute for the shader with the specified uniform attribute name
	//uniformAttributeName - The name of the uniform attribute to create
	void CreateAttributeMatrix3x3(const string& uniformAttributeName);

	//Creates a matrix 4x4 uniform attribute for the shader with the specified uniform attribute name
	//uniformAttributeName - The name of the uniform attribute to create
	void CreateAttributeMatrix4x4(const string& uniformAttributeName);

	//Creates a texture sampler uniform attribute for the shader with the specified uniform attribute name
	//uniformAttributeName - The name of the uniform attribute to create
	void CreateAttributeTextureSampler(const string& uniformAttributeName);

	//Sets the float shader attribute with the specified uniform attribute name
	//uniformAttributeName - The name of the uniform attribute to set
	//value - The value to link to the uniform attribute
	void SetAttributeFloat(const string& uniformAttributeName, const float value);

	//Sets the vector 2 shader attribute with the specified uniform attribute name
	//uniformAttributeName - The name of the uniform attribute to set
	//value - The value to link to the uniform attribute
	void SetAttributeVector2(const string& uniformAttributeName, const vec2& value);

	//Sets the vector 3 shader attribute with the specified uniform attribute name
	//uniformAttributeName - The name of the uniform attribute to set
	//value - The value to link to the uniform attribute
	void SetAttributeVector3(const string& uniformAttributeName, const vec3& value);

	//Sets the vector 4 shader attribute with the specified uniform attribute name
	//uniformAttributeName - The name of the uniform attribute to set
	//value - The value to link to the uniform attribute
	void SetAttributeVector4(const string& uniformAttributeName, const vec4& value);

	//Sets the matrix 3x3 shader attribute with the specified uniform attribute name
	//uniformAttributeName - The name of the uniform attribute to set
	//value - The value to link to the uniform attribute
	void SetAttributeMatrix3x3(const string& uniformAttributeName, const mat3& value);

	//Sets the matrix 4x4 shader attribute with the specified uniform attribute name
	//uniformAttributeName - The name of the uniform attribute to set
	//value - The value to link to the uniform attribute
	void SetAttributeMatrix4x4(const string& uniformAttributeName, const mat4& value);

	//Sets the texture sampler shader attribute with the specified uniform attribute name
	//uniformAttributeName - The name of the uniform attribute to set
	//value - The value to link to the uniform attribute
	void SetAttributeTextureSampler(const string& uniformAttributeName, const unsigned int value);

	//Sets the shader as active for rendering
	void Use();

	//Updates the shaders uniform attributes values on GPU
	void UpdateUniformAttributesToGPU();

protected:
	//Returns a compiled shader
	//shaderFilepath - The location, name and file extension to the shader file
	//shaderType - The type of shader to create (vertex, geometry or fragment)
	unsigned int CreateShader(const string& shaderFilepath, const unsigned int shaderType);

	//Returns a shader progam with the specified vertex shader attached and linked
	//transformFeedbackAttributeNames - list of attributes to stream back from the shader
	unsigned int CreateShaderProgram(unsigned int vertexShader, vector<const char*> transformFeedbackAttributeNames);

	//Returns a shader program with the specified vertex and fragment shaders attached and linked
	//vertexShader - The vertex shader to attach and link with the shader program
	//fragmentShader - The fragment shader to attach and link with the shader program
	unsigned int CreateShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);

	//Returns a shader program with the specified vertex, geometry and fragment shaders attached and linked
	//vertexShader - The vertex shader to attach and link with the shader program
	//geometryShader - The geometry shader to attach and link with the shader program
	//fragmentShader - The fragment shader to attach and link with the shader program
	unsigned int CreateShaderProgram(unsigned int vertexShader, unsigned int geometryShader, unsigned int fragmentShader);

	//Destroys the specified shader
	//shader - The shader to destroy
	void DestroyShader(unsigned int shader);

	//Destroys the specified shader program
	//shaderProgam - Reference to the shader program to destroy
	void DestroyShaderProgram(unsigned int& shaderProgram);

private:
	//The shaders shader program id
	unsigned int m_shaderProgram;

	//Container for storing the shaders float uniform attributes
	map<const string, ShaderAttribute<float>> m_floatUniformAttributeContainer;

	//Container for storing the shaders vector 2 uniform attributes
	map<const string, ShaderAttribute<vec2>> m_vector2UniformAttributeContainer;

	//Container for storing the shaders vector 3 uniform attributes
	map<const string, ShaderAttribute<vec3>> m_vector3UniformAttributeContainer;

	//Container for storing the shaders vector 4 uniform attributes
	map<const string, ShaderAttribute<vec4>> m_vector4UniformAttributeContainer;

	//Container for storing the shaders matrix 3x3 uniform attributes
	map<const string, ShaderAttribute<mat3>> m_matrix3x3UniformAttributeContainer;

	//Container for storing the shaders matrix 4x4 uniform attributes
	map<const string, ShaderAttribute<mat4>> m_matrix4x4UniformAttributeContainer;

	//Container for storing the shaders texture sampler uniform attributes
	map<const string, ShaderAttribute<unsigned int>> m_textureSamplerUniformAttributeContainer;

	//Container storing texture sampler keys in the order they were inserted into the texture sampler uniform attribute container
	vector<string> m_orderedTextureSamplerKeyContainer;
};