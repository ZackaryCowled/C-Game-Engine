//Internal includes
#include "Application.h"

//External incldues
#include <GL\glew.h>

//Creates and initializes a Shader instance (Default constructor)
Shader::Shader()
{
	//Initialize Shader
	m_shaderProgram = 0;
	m_floatUniformAttributeContainer = map<const string, ShaderAttribute<float>>();
	m_vector2UniformAttributeContainer = map<const string, ShaderAttribute<vec2>>();
	m_vector3UniformAttributeContainer = map<const string, ShaderAttribute<vec3>>();
	m_vector4UniformAttributeContainer = map<const string, ShaderAttribute<vec4>>();
	m_matrix3x3UniformAttributeContainer = map<const string, ShaderAttribute<mat3>>();
	m_matrix4x4UniformAttributeContainer = map<const string, ShaderAttribute<mat4>>();
	m_textureSamplerUniformAttributeContainer = map<const string, ShaderAttribute<unsigned int>>();
	m_orderedTextureSamplerKeyContainer = vector<string>();
}

//Creates and initializes a Shader instance
//vertexShaderFilepath - The location, name and file extension to the vertex shader file
//transformFeedbackAttributeNames - list of attributes to stream back from the shader
Shader::Shader(const string& vertexShaderFilepath, vector<const char*> transformFeedbackAttributeNames)
{
	//Initialize Shader
	unsigned int vertexShader = CreateShader(vertexShaderFilepath, GL_VERTEX_SHADER);
	m_shaderProgram = CreateShaderProgram(vertexShader, transformFeedbackAttributeNames);
	m_floatUniformAttributeContainer = map<const string, ShaderAttribute<float>>();
	m_vector2UniformAttributeContainer = map<const string, ShaderAttribute<vec2>>();
	m_vector3UniformAttributeContainer = map<const string, ShaderAttribute<vec3>>();
	m_vector4UniformAttributeContainer = map<const string, ShaderAttribute<vec4>>();
	m_matrix3x3UniformAttributeContainer = map<const string, ShaderAttribute<mat3>>();
	m_matrix4x4UniformAttributeContainer = map<const string, ShaderAttribute<mat4>>();
	m_textureSamplerUniformAttributeContainer = map<const string, ShaderAttribute<unsigned int>>();
	m_orderedTextureSamplerKeyContainer = vector<string>();
	DestroyShader(vertexShader);
}

//Creates and initializes a Shader instance
//vertexShaderFilepath - The location, name and file extension to the vertex shader file
//fragmentShaderFilepath - The location, name and file extension to the fragment shader file
Shader::Shader(const string& vertexShaderFilepath, const string& fragmentShaderFilepath)
{
	//Initialize Shader
	unsigned int vertexShader = CreateShader(vertexShaderFilepath, GL_VERTEX_SHADER);
	unsigned int fragmentShader = CreateShader(fragmentShaderFilepath, GL_FRAGMENT_SHADER);
	m_shaderProgram = CreateShaderProgram(vertexShader, fragmentShader);
	m_floatUniformAttributeContainer = map<const string, ShaderAttribute<float>>();
	m_vector2UniformAttributeContainer = map<const string, ShaderAttribute<vec2>>();
	m_vector3UniformAttributeContainer = map<const string, ShaderAttribute<vec3>>();
	m_vector4UniformAttributeContainer = map<const string, ShaderAttribute<vec4>>();
	m_matrix3x3UniformAttributeContainer = map<const string, ShaderAttribute<mat3>>();
	m_matrix4x4UniformAttributeContainer = map<const string, ShaderAttribute<mat4>>();
	m_textureSamplerUniformAttributeContainer = map<const string, ShaderAttribute<unsigned int>>();
	m_orderedTextureSamplerKeyContainer = vector<string>();
	DestroyShader(vertexShader);
	DestroyShader(fragmentShader);
}

//Creates and initializes a Shader instance
//vertexShaderFilepath - The location, name and file extension to the vertex shader file
//geometryShaderFilepath - The location, name and file extension to the geometry shader file
//fragmentShaderFilepath - The location, name and file extension to the fragment shader file
Shader::Shader(const string& vertexShaderFilepath, const string& geometryShaderFilepath, const string& fragmentShaderFilepath)
{
	//Initialize Shader
	unsigned int vertexShader = CreateShader(vertexShaderFilepath, GL_VERTEX_SHADER);
	unsigned int geometryShader = CreateShader(geometryShaderFilepath, GL_GEOMETRY_SHADER);
	unsigned int fragmentShader = CreateShader(fragmentShaderFilepath, GL_FRAGMENT_SHADER);
	m_shaderProgram = CreateShaderProgram(vertexShader, geometryShader, fragmentShader);
	m_floatUniformAttributeContainer = map<const string, ShaderAttribute<float>>();
	m_vector2UniformAttributeContainer = map<const string, ShaderAttribute<vec2>>();
	m_vector3UniformAttributeContainer = map<const string, ShaderAttribute<vec3>>();
	m_vector4UniformAttributeContainer = map<const string, ShaderAttribute<vec4>>();
	m_matrix3x3UniformAttributeContainer = map<const string, ShaderAttribute<mat3>>();
	m_matrix4x4UniformAttributeContainer = map<const string, ShaderAttribute<mat4>>();
	m_textureSamplerUniformAttributeContainer = map<const string, ShaderAttribute<unsigned int>>();
	m_orderedTextureSamplerKeyContainer = vector<string>();
	DestroyShader(vertexShader);
	DestroyShader(geometryShader);
	DestroyShader(fragmentShader);
}

//Creates a float uniform attribute for the shader with the specified uniform attribute name
//uniformAttributeName - The name of the uniform attribute to create
void Shader::CreateAttributeFloat(const string& uniformAttributeName)
{
	//Create float uniform shader attribute
	ShaderAttribute<float> floatUniformShaderAttribute = ShaderAttribute<float>();
	floatUniformShaderAttribute.uniformLocation = glGetUniformLocation(m_shaderProgram, uniformAttributeName.c_str());

	//Add float uniform shader attribute in the shaders float uniform attribute container
	m_floatUniformAttributeContainer.insert(pair<const string, ShaderAttribute<float>>(uniformAttributeName, floatUniformShaderAttribute));
}

//Creates a vector 2 uniform attribute for the shader with the specified uniform attribute name
//uniformAttributeName - The name of the uniform attribute to create
void Shader::CreateAttributeVector2(const string& uniformAttributeName)
{
	//Create vector 2 uniform shader attribute
	ShaderAttribute<vec2> vector2UniformShaderAttribute = ShaderAttribute<vec2>();
	vector2UniformShaderAttribute.uniformLocation = glGetUniformLocation(m_shaderProgram, uniformAttributeName.c_str());

	//Add vector 2 uniform shader attribute in the shaders vector 2 uniform attribute container
	m_vector2UniformAttributeContainer.insert(pair<const string, ShaderAttribute<vec2>>(uniformAttributeName, vector2UniformShaderAttribute));
}

//Creates a vector 3 uniform attribute for the shader with the specified uniform attribute name
//uniformAttributeName - The name of the uniform attribute to create
void Shader::CreateAttributeVector3(const string& uniformAttributeName)
{
	//Create vector 3 uniform shader attribute
	ShaderAttribute<vec3> vector3UniformShaderAttribute = ShaderAttribute<vec3>();
	vector3UniformShaderAttribute.uniformLocation = glGetUniformLocation(m_shaderProgram, uniformAttributeName.c_str());

	//Add vector 3 uniform shader attribute in the shaders vector 3 uniform attribute container
	m_vector3UniformAttributeContainer.insert(pair<const string, ShaderAttribute<vec3>>(uniformAttributeName, vector3UniformShaderAttribute));
}

//Creates a vector 4 uniform attribute for the shader with the specified uniform attribute name
//uniformAttributeName - The name of the uniform attribute to create
void Shader::CreateAttributeVector4(const string& uniformAttributeName)
{
	//Create vector 4 uniform shader attribute
	ShaderAttribute<vec4> vector4UniformShaderAttribute = ShaderAttribute<vec4>();
	vector4UniformShaderAttribute.uniformLocation = glGetUniformLocation(m_shaderProgram, uniformAttributeName.c_str());

	//Add vector 4 uniform shader attribute in the shaders vector 4 uniform attribute container
	m_vector4UniformAttributeContainer.insert(pair<const string, ShaderAttribute<vec4>>(uniformAttributeName, vector4UniformShaderAttribute));
}

//Creates a matrix 3x3 uniform attribute for the shader with the specified uniform attribute name
//uniformAttributeName - The name of the uniform attribute to create
void Shader::CreateAttributeMatrix3x3(const string& uniformAttributeName)
{
	//Create matrix 3x3 uniform shader attribute
	ShaderAttribute<mat3> matrix3x3UniformShaderAttribute = ShaderAttribute<mat3>();
	matrix3x3UniformShaderAttribute.uniformLocation = glGetUniformLocation(m_shaderProgram, uniformAttributeName.c_str());

	//Add matrix 3x3 uniform shader attribute in the shaders matrix 3x3 uniform attribute container
	m_matrix3x3UniformAttributeContainer.insert(pair<const string, ShaderAttribute<mat3>>(uniformAttributeName, matrix3x3UniformShaderAttribute));
}

//Creates a matrix 4x4 uniform attribute for the shader with the specified uniform attribute name
//uniformAttributeName - The name of the uniform attribute to create
void Shader::CreateAttributeMatrix4x4(const string& uniformAttributeName)
{
	//Create matrix 4x4 uniform shader attribute
	ShaderAttribute<mat4> matrix4x4UniformShaderAttribute = ShaderAttribute<mat4>();
	matrix4x4UniformShaderAttribute.uniformLocation = glGetUniformLocation(m_shaderProgram, uniformAttributeName.c_str());

	//Add matrix 4x4 uniform shader attribute in the shaders matrix 4x4 uniform attribute container
	m_matrix4x4UniformAttributeContainer.insert(pair<const string, ShaderAttribute<mat4>>(uniformAttributeName, matrix4x4UniformShaderAttribute));
}

//Creates a texture sampler uniform attribute for the shader with the specified uniform attribute name
//uniformAttributeName - The name of the uniform attribute to create
void Shader::CreateAttributeTextureSampler(const string& uniformAttributeName)
{
	//Create texture sampler uniform shader attribute
	ShaderAttribute<unsigned int> textureSamplerUniformShaderAttribute = ShaderAttribute<unsigned int>();
	textureSamplerUniformShaderAttribute.uniformLocation = glGetUniformLocation(m_shaderProgram, uniformAttributeName.c_str());

	//Add texture sampler uniform shader attribute in the shaders texture sampler uniform attribute container
	m_textureSamplerUniformAttributeContainer.insert(pair<const string, ShaderAttribute<unsigned int>>(uniformAttributeName, textureSamplerUniformShaderAttribute));

	//Add texture sampler key to the ordered texture sampler key container
	m_orderedTextureSamplerKeyContainer.push_back(uniformAttributeName);
}

//Sets the float shader attribute with the specified uniform attribute name
//uniformAttributeName - The name of the uniform attribute to set
//value - The value to link to the uniform attribute
void Shader::SetAttributeFloat(const string& uniformAttributeName, const float value)
{
	//Set the specified uniform attribute to the specified float value
	m_floatUniformAttributeContainer[uniformAttributeName].value = value;
}

//Sets the vector 2 shader attribute with the specified uniform attribute name
//uniformAttributeName - The name of the uniform attribute to set
//value - The value to link to the uniform attribute
void Shader::SetAttributeVector2(const string& uniformAttributeName, const vec2& value)
{
	//Set the specified uniform attribute to the specified vector 2 value
	m_vector2UniformAttributeContainer[uniformAttributeName].value = value;
}

//Sets the vector 3 shader attribute with the specified uniform attribute name
//uniformAttributeName - The name of the uniform attribute to set
//value - The value to link to the uniform attribute
void Shader::SetAttributeVector3(const string& uniformAttributeName, const vec3& value)
{
	//Set the specified uniform attribute to the specified vector 3 value
	m_vector3UniformAttributeContainer[uniformAttributeName].value = value;
}

//Sets the vector 4 shader attribute with the specified uniform attribute name
//uniformAttributeName - The name of the uniform attribute to set
//value - The value to link to the uniform attribute
void Shader::SetAttributeVector4(const string& uniformAttributeName, const vec4& value)
{
	//Set the specified uniform attribute to the specified vector 4 value
	m_vector4UniformAttributeContainer[uniformAttributeName].value = value;
}

//Sets the matrix 3x3 shader attribute with the specified uniform attribute name
//uniformAttributeName - The name of the uniform attribute to set
//value - The value to link to the uniform attribute
void Shader::SetAttributeMatrix3x3(const string& uniformAttributeName, const mat3& value)
{
	//Set the specified uniform attribute to the specified matrix 3x3 value
	m_matrix3x3UniformAttributeContainer[uniformAttributeName].value = value;
}

//Sets the matrix 4x4 shader attribute with the specified uniform attribute name
//uniformAttributeName - The name of the uniform attribute to set
//value - The value to link to the uniform attribute
void Shader::SetAttributeMatrix4x4(const string& uniformAttributeName, const mat4& value)
{
	//Set the specified uniform attribute to the specified matrix 4x4 value
	m_matrix4x4UniformAttributeContainer[uniformAttributeName].value = value;
}

//Sets the texture sampler shader attribute with the specified uniform attribute name
//uniformAttributeName - The name of the uniform attribute to set
//value - The value to link to the uniform attribute
void Shader::SetAttributeTextureSampler(const string& uniformAttributeName, const unsigned int value)
{
	//Set the specified uniform attribute to the specified texture sampler
	m_textureSamplerUniformAttributeContainer[uniformAttributeName].value = value;
}

//Sets the shader as active for rendering
void Shader::Use()
{
	//Bind the shader program
	glUseProgram(m_shaderProgram);
}

//Updates the shaders uniform attributes values on GPU
void Shader::UpdateUniformAttributesToGPU()
{
	//For each float uniform attribute
	for (auto floatUniformAttribute : m_floatUniformAttributeContainer)
	{
		//Bind float uniform attribute
		glUniform1f(floatUniformAttribute.second.uniformLocation, floatUniformAttribute.second.value);
	}

	//For each vector 2 uniform attribute
	for (auto vector2UniformAttribute : m_vector2UniformAttributeContainer)
	{
		//Bind vector 2 uniform attribute
		glUniform2fv(vector2UniformAttribute.second.uniformLocation, 1, value_ptr(vector2UniformAttribute.second.value));
	}

	//For each vector 3 uniform attribute
	for (auto vector3UniformAttribute : m_vector3UniformAttributeContainer)
	{
		//Bind vector 3 uniform attribute
		glUniform3fv(vector3UniformAttribute.second.uniformLocation, 1, value_ptr(vector3UniformAttribute.second.value));
	}

	//For each vector 4 uniform attribute
	for (auto vector4UniformAttribute : m_vector4UniformAttributeContainer)
	{
		//Bind vector 4 uniform attribute
		glUniform4fv(vector4UniformAttribute.second.uniformLocation, 1, value_ptr(vector4UniformAttribute.second.value));
	}

	//For each matrix 3x3 uniform attribute
	for (auto matrix3x3UniformAttribute : m_matrix3x3UniformAttributeContainer)
	{
		//Bind matrix 3x3 uniform attribute
		glUniformMatrix3fv(matrix3x3UniformAttribute.second.uniformLocation, 1, GL_FALSE, value_ptr(matrix3x3UniformAttribute.second.value));
	}

	//For each matrix 4x4 uniform attribute
	for (auto matrix4x4UniformAttribute : m_matrix4x4UniformAttributeContainer)
	{
		//Bind matrix 4x4 uniform attribute
		glUniformMatrix4fv(matrix4x4UniformAttribute.second.uniformLocation, 1, GL_FALSE, value_ptr(matrix4x4UniformAttribute.second.value));
	}

	//For each texture sampler key
	for (unsigned int textureSamplerKeyIndex = 0; textureSamplerKeyIndex < m_orderedTextureSamplerKeyContainer.size(); ++textureSamplerKeyIndex)
	{
		//Set the active texture
		glActiveTexture(GL_TEXTURE0 + textureSamplerKeyIndex);

		//Bind the texture
		glBindTexture(GL_TEXTURE_2D, m_textureSamplerUniformAttributeContainer[m_orderedTextureSamplerKeyContainer[textureSamplerKeyIndex]].value);

		//Bind the texture sampler uniform attribute
		glUniform1i(m_textureSamplerUniformAttributeContainer[m_orderedTextureSamplerKeyContainer[textureSamplerKeyIndex]].uniformLocation, (GLint)textureSamplerKeyIndex);
	}
}

//Returns a compiled shader
//shaderFilepath - The location, name and file extension to the shader file
//shaderType - The type of shader to create (vertex, geometry or fragment)
unsigned int Shader::CreateShader(const string& shaderFilepath, const unsigned int shaderType)
{
	//Load the shader file
	string shaderFile = FileImporter::ImportFile(shaderFilepath);

	//Create pointer to the shader files source code
	const char* shaderSource = shaderFile.c_str();

	//Create shader
	unsigned int shader = glCreateShader(shaderType);

	//Set the shaders source
	glShaderSource(shader, 1, &shaderSource, NULL);

	//Compile the shader
	glCompileShader(shader);

	//Return the shader
	return shader;
}

//Returns a shader progam with the specified vertex shader attached and linked
//transformFeedbackAttributeNames - list of attributes to stream back from the shader
unsigned int Shader::CreateShaderProgram(unsigned int vertexShader, vector<const char*> transformFeedbackAttributeNames)
{
	//Create shader program
	unsigned int shaderProgram = glCreateProgram();

	//Attach the vertex and fragment shaders to the shader program
	glAttachShader(shaderProgram, vertexShader);

	//Specify the data to stream back from the shader
	glTransformFeedbackVaryings(shaderProgram, (GLsizei)transformFeedbackAttributeNames.size(), transformFeedbackAttributeNames.data(), GL_INTERLEAVED_ATTRIBS);

	//Link the shader program
	glLinkProgram(shaderProgram);

	//If the application is in debug mode
	#ifdef _DEBUG
		//Create attribute for checking the shader programs link status
		GLint linkStatus = 0;

		//Query the shader programs link status
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkStatus);

		//If the shader program failed to link
		if (!linkStatus)
		{
			//Create attribute for storing the shader programs info log
			GLchar infoLog[512];

			//Retrieve the shader programs info log
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);

			//Output info log in an error message window
			ErrorMessageWindow("Shader link error", infoLog);

			//Quit the application
			Application::Quit();
		}
	#endif

	//Return the shader program
	return shaderProgram;
}

//Returns a shader program with the specified vertex and fragment shaders attached and linked
//vertexShader - The vertex shader to attach and link with the shader program
//fragmentShader - The fragment shader to attach and link with the shader program
unsigned int Shader::CreateShaderProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
	//Create shader program
	unsigned int shaderProgram = glCreateProgram();

	//Attach the vertex and fragment shaders to the shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	//Link the shader program
	glLinkProgram(shaderProgram);

	//If the application is in debug mode
	#ifdef _DEBUG
		//Create attribute for checking the shader programs link status
		GLint linkStatus = 0;

		//Query the shader programs link status
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkStatus);

		//If the shader program failed to link
		if (!linkStatus)
		{
			//Create attribute for storing the shader programs info log
			GLchar infoLog[512];

			//Retrieve the shader programs info log
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);

			//Output info log in an error message window
			ErrorMessageWindow("Shader link error", infoLog);

			//Quit the application
			Application::Quit();
		}
	#endif

	//Return the shader program
	return shaderProgram;
}

//Returns a shader program with the specified vertex, geometry and fragment shaders attached and linked
//vertexShader - The vertex shader to attach and link with the shader program
//geometryShader - The geometry shader to attach and link with the shader program
//fragmentShader - The fragment shader to attach and link with the shader program
unsigned int Shader::CreateShaderProgram(unsigned int vertexShader, unsigned int geometryShader, unsigned int fragmentShader)
{
	//Create shader program
	unsigned int shaderProgram = glCreateProgram();

	//Attach the vertex, geometry and fragment shaders to the shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, geometryShader);
	glAttachShader(shaderProgram, fragmentShader);

	//Link the shader program
	glLinkProgram(shaderProgram);

	//If the application is in debug mode
	#ifdef _DEBUG
		//Create attribute for checking the shader programs link status
		GLint linkStatus = 0;

		//Query the shader programs link status
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkStatus);

		//If the shader program failed to link
		if (!linkStatus)
		{
			//Create attribute for storing the shader programs info log
			GLchar infoLog[512];

			//Retrieve the shader programs info log
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);

			//Output info log in an error message window
			ErrorMessageWindow("Shader link error", infoLog);

			//Quit the application
			Application::Quit();
		}
	#endif

	//Return the shader program
	return shaderProgram;
}

//Destroys the specified shader
//shader - The shader to destroy
void Shader::DestroyShader(unsigned int shader)
{
	//If the shader is valid
	if (shader)
	{
		//Destroy the shader
		glDeleteShader(shader);
	}
}

//Destroys the specified shader program
//shaderProgam - Reference to the shader program to destroy
void Shader::DestroyShaderProgram(unsigned int& shaderProgram)
{
	//If the shader program is valid
	if (shaderProgram)
	{
		//Destroy the shader program
		glDeleteProgram(shaderProgram);
	}
}