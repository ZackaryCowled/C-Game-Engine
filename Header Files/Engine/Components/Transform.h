//Pragma comments
#pragma once

//Internal includes
#include "Component.h"

//External includes
#include <glm\glm.hpp>
#include <glm\gtc\matrix_inverse.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\quaternion.hpp>

//Using directives
using namespace glm;

//Forward directives
class Camera;

//Object used for representing an Objects position, rotation and scale in 3D space
class Transform : public Component
{
public:
	//Creates and initializes a Transform instance (Default constructor)
	Transform();

	//Returns the transforms local matrix
	mat4 GetLocalMatrix();

	//Returns the transforms world matrix
	mat4 GetWorldMatrix();

	//Returns the transforms normal matrix
	//p_camera - Camera to use for generating the transforms normal matrix
	mat3 GetNormalMatrix(Camera* p_camera);

	//Returns the global position of the transform
	vec3 GetPosition();

	//Returns the global rotation of the transform
	vec3 GetRotation();

	//Returns the global scale of the transform
	vec3 GetScale();

	//Returns the forward direction of the transform
	vec3 GetForwardDirection();

	//Returns the up direction of the transform
	vec3 GetUpDirection();

	//Returns the right direction of the transform
	vec3 GetRightDirection();

	//Moves the transform by the specified translation
	void Translate(const float x, const float y, const float z);

	//Moves the transform by the specified translation
	void Translate(const vec3& translation);

	//Rotates the transform by the specified rotation
	void Rotate(const float x, const float y, const float z);

	//Rotates the transform by the specified rotation
	void Rotate(const vec3& rotation);

	//Scale the transform by the specified scale
	void Scale(const float x, const float y, const float z);

	//Scale the transform by the specified scale
	void Scale(const vec3& scale);

	//Sets the position of the transform to the specified position
	void SetPosition(const float x, const float y, const float z);

	//Sets the position of the transform to the specified position
	void SetPosition(const vec3& position);

	//Sets the rotation of the transform to the specified rotation
	void SetRotation(const float x, const float y, const float z);

	//Sets the rotation of the transform to the specified rotation
	void SetRotation(const vec3& rotation);

	//Sets the scale of the transform to the specified scale
	void SetScale(const float x, const float y, const float z);

	//Sets the scale of the transform to the specified scale
	void SetScale(const vec3& scale);

private:
	//Global translation matrix
	mat4 m_globalTranslationMatrix;

	//Global euler angles
	vec3 m_globalEulerAngles;

	//Global rotation matrix
	mat4 m_globalRotationMatrix;

	//Global scale matrix
	mat4 m_globalScaleMatrix;
};