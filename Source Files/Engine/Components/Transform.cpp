//Internal includes
#include "Transform.h"
#include "Application.h"

//Creates and initializes a Transform instance (Default constructor)
Transform::Transform()
{
	//Initialize Transform
	m_globalTranslationMatrix = mat4(1.0f);
	m_globalEulerAngles = vec3(0.0f);
	m_globalRotationMatrix = mat4(1.0f);
	m_globalScaleMatrix = mat4(1.0f);
	SetType(COMPONENT_TYPE_TRANSFORM);
}

//Returns the transforms local matrix
mat4 Transform::GetLocalMatrix()
{
	//Return the transforms local matrix
	return m_globalTranslationMatrix * m_globalRotationMatrix * m_globalScaleMatrix;
}

//Returns the transforms world matrix
mat4 Transform::GetWorldMatrix()
{
	//If the parent or the Transform component is a child
	if (GetParent() != nullptr && GetParent()->GetParent() != nullptr)
	{
		//Get address of the transform components parents parents transform
		Transform* p_parentTransform = GetParent()->GetParent()->GetComponent<Transform>();

		//If the transform components parents parents transform is valid
		if (p_parentTransform != nullptr)
		{
			//Return the transforms world matrix (Product of the parents parents world matrix and the parents local matrix)
			return p_parentTransform->GetWorldMatrix() * GetLocalMatrix();
		}
	}

	//Return the transforms local matrix
	return GetLocalMatrix();
}

//Returns the transforms normal matrix
//p_camera - Camera to use for generating the transforms normal matrix
mat3 Transform::GetNormalMatrix(Camera* p_camera)
{
	//Return the transforms normal matrix
	return inverseTranspose(p_camera->GetViewMatrix() * GetWorldMatrix());
}

//Returns the global position of the transform
vec3 Transform::GetPosition()
{
	//Return the transforms global position
	return vec3(m_globalTranslationMatrix[3][0], m_globalTranslationMatrix[3][1], m_globalTranslationMatrix[3][2]);
}

//Returns the global rotation of the transform
vec3 Transform::GetRotation()
{
	//Return the transforms global rotation
	return m_globalEulerAngles;
}

//Returns the global scale of the transform
vec3 Transform::GetScale()
{
	//Return the transforms global scale
	return vec3(m_globalScaleMatrix[0][0], m_globalScaleMatrix[1][1], m_globalScaleMatrix[2][2]);
}

//Returns the forward direction of the transform
vec3 Transform::GetForwardDirection()
{
	//Get the transforms world matrix
	mat4 worldMatrix = GetWorldMatrix();

	//Return the transforms forward direction
	return vec3(worldMatrix[2][0], worldMatrix[2][1], worldMatrix[2][2]);
}

//Returns the up direction of the transform
vec3 Transform::GetUpDirection()
{
	//Get the transforms world matrix
	mat4 worldMatrix = GetWorldMatrix();

	//Return the transforms up direction
	return vec3(worldMatrix[1][0], worldMatrix[1][1], worldMatrix[1][2]);
}

//Returns the right direction of the transform
vec3 Transform::GetRightDirection()
{
	//Get the transforms world direction
	mat4 worldMatrix = GetWorldMatrix();

	//Return the transforms right direction
	return vec3(worldMatrix[0][0], worldMatrix[0][1], worldMatrix[0][2]);
}

//Moves the transform by the specified translation
void Transform::Translate(const float x, const float y, const float z)
{
	//Move the transform by the specified translation
	m_globalTranslationMatrix[3][0] += x;
	m_globalTranslationMatrix[3][1] += y;
	m_globalTranslationMatrix[3][2] += z;
}

//Moves the transform by the specified translation
void Transform::Translate(const vec3& translation)
{
	//Move the transform by the specified translation
	m_globalTranslationMatrix[3][0] += translation.x;
	m_globalTranslationMatrix[3][1] += translation.y;
	m_globalTranslationMatrix[3][2] += translation.z;
}

//Rotates the transform by the specified rotation
void Transform::Rotate(const float x, const float y, const float z)
{
	//Rotate the transform by the specified transform
	m_globalEulerAngles += radians(vec3(x, y, z));
	quat globalQuaternion = quat(m_globalEulerAngles);
	m_globalRotationMatrix = mat4_cast(globalQuaternion);
}

//Rotates the transform by the specified rotation
void Transform::Rotate(const vec3& rotation)
{
	//Rotate the transform by the specified transform
	m_globalEulerAngles += radians(rotation);
	quat globalQuaternion = quat(m_globalEulerAngles);
	m_globalRotationMatrix = mat4_cast(globalQuaternion);
}

//Scale the transform by the specified scale
void Transform::Scale(const float x, const float y, const float z)
{
	//Scale the transform by the specified scale
	m_globalScaleMatrix[0][0] *= x;
	m_globalScaleMatrix[1][1] *= y;
	m_globalScaleMatrix[2][2] *= z;
}

//Scale the transform by the specified scale
void Transform::Scale(const vec3& scale)
{
	//Scale the transform by the specified scale
	m_globalScaleMatrix[0][0] *= scale.x;
	m_globalScaleMatrix[1][1] *= scale.y;
	m_globalScaleMatrix[2][2] *= scale.z;
}

//Sets the position of the transform to the specified position
void Transform::SetPosition(const float x, const float y, const float z)
{
	//Set the position of the transform to the specified position
	m_globalTranslationMatrix[3][0] = x;
	m_globalTranslationMatrix[3][1] = y;
	m_globalTranslationMatrix[3][2] = z;
}

//Sets the position of the transform to the specified position
void Transform::SetPosition(const vec3& position)
{
	//Set the position of the transform to the specified position
	m_globalTranslationMatrix[3][0] = position.x;
	m_globalTranslationMatrix[3][1] = position.y;
	m_globalTranslationMatrix[3][2] = position.z;
}

//Sets the rotation of the transform to the specified rotation
void Transform::SetRotation(const float x, const float y, const float z)
{
	//Set the rotation of the transform to the specified rotation
	m_globalEulerAngles = radians(vec3(x, y, z));
	quat globalQuaternion = quat(m_globalEulerAngles);
	m_globalRotationMatrix = mat4_cast(globalQuaternion);
}

//Sets the rotation of the transform to the specified rotation
void Transform::SetRotation(const vec3& rotation)
{
	//Set the rotation of the transform to the specified rotation
	m_globalEulerAngles = radians(rotation);
	quat globalQuaternion = quat(m_globalEulerAngles);
	m_globalRotationMatrix = mat4_cast(globalQuaternion);
}

//Sets the scale of the transform to the specified scale
void Transform::SetScale(const float x, const float y, const float z)
{
	//Set the scale of the transform to the specified scale
	m_globalScaleMatrix[0][0] = x;
	m_globalScaleMatrix[1][1] = y;
	m_globalScaleMatrix[2][2] = z;
}

//Sets the scale of the transform to the specified scale
void Transform::SetScale(const vec3& scale)
{
	//Set the scale of the transform to the specified scale
	m_globalScaleMatrix[0][0] = scale.x;
	m_globalScaleMatrix[1][1] = scale.y;
	m_globalScaleMatrix[2][2] = scale.z;
}