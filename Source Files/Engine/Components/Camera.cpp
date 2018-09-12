//Internal includes
#include "Camera.h"
#include "Application.h"

//External includes
#include <GL\glew.h>

//Creates and initializes a Camera component (Default constructor)
Camera::Camera()
{
	//Initialize Camera
	SetFieldOfView(60.0f);
	SetNearClippingPlane(0.1f);
	SetDrawDistance(1000.0f);
	SetClippingPlaneRegion(0.0f, 0.0f, 1.0f, 1.0f);
	m_viewMatrix = mat4(1.0f);
	m_projectionMatrix = mat4(1.0f);
	SetType(COMPONENT_TYPE_CAMERA);
	CameraManager::RegisterCamera(this);
}

//Releases the camera components resources
Camera::~Camera()
{
	//Destroy the camera
	Destroy();
}

//Destroys the camera component
void Camera::Destroy()
{
	//Unregister the camera
	CameraManager::UnregisterCamera(this);
}

//Updates the camera (Call before rendering)
void Camera::Update()
{
	//If the camera has a valid parent
	if (GetParent() != nullptr)
	{
		//Create a reference to the cameras parents transform
		Transform* parentTransform = GetParent()->GetComponent<Transform>();

		//If the cameras parents transform is valid
		if (parentTransform != nullptr)
		{
			//Get the cameras world matrix
			mat4 worldMatrix = parentTransform->GetWorldMatrix();

			//Calculate view matrix based of the cameras parents transform
			m_viewMatrix = lookAtLH(vec3(worldMatrix[3][0], worldMatrix[3][1], worldMatrix[3][2]),
									vec3(worldMatrix[3][0], worldMatrix[3][1], worldMatrix[3][2]) + vec3(worldMatrix[2][0], worldMatrix[2][1], worldMatrix[2][2]),
									vec3(worldMatrix[1][0], worldMatrix[1][1], worldMatrix[1][2]));
		}
		//Otherwise
		else
		{
			//Flag representing whether the camera has been updated
			bool updatedFlag = false;

			//Pointer to the next parent GameObject
			GameObject* p_parent = GetParent();

			//While the GameObject pointer is valid
			while (p_parent != nullptr)
			{
				//Get the parents transform
				parentTransform = p_parent->GetComponent<Transform>();

				//If the parents transform is valid
				if (parentTransform != nullptr)
				{
					//Get the cameras world matrix
					mat4 worldMatrix = parentTransform->GetWorldMatrix();

					//Calculate view matrix based of the cameras parents transform
					m_viewMatrix = lookAtLH(vec3(worldMatrix[3][0], worldMatrix[3][1], worldMatrix[3][2]),
											vec3(worldMatrix[3][0], worldMatrix[3][1], worldMatrix[3][2]) + vec3(worldMatrix[2][0], worldMatrix[2][1], worldMatrix[2][2]),
											vec3(worldMatrix[1][0], worldMatrix[1][1], worldMatrix[1][2]));

					//Set the updated flag
					updatedFlag = true;

					//Break out of the loop
					break;
				}

				//Set the parent to the parents parent
				p_parent = p_parent->GetParent();
			}

			//If the view matrix has not been set
			if (!updatedFlag)
			{
				//Calculate view matrix from origin looking directly down the positive z-axis
				m_viewMatrix = lookAtLH(vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0), vec3(0.0, 1.0, 0.0));
			}
		}
	}
	//Otherwise
	else
	{
		//Calculate view matrix from origin looking directly down the positive z-axis
		m_viewMatrix = lookAtLH(vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0), vec3(0.0, 1.0, 0.0));
	}

	//Calculate the projection matrix
	m_projectionMatrix = perspectiveLH(GetFieldOfView(), WindowManager::GetWindowWidthf() / WindowManager::GetWindowHeightf(), GetNearClippingPlane(), GetNearClippingPlane() + GetDrawDistance());

	//Update the cameras viewport
	glViewport((GLint)(WindowManager::GetWindowWidthf() * GetClippingPlaneLeft()),
			   (GLint)(WindowManager::GetWindowHeightf() * GetClippingPlaneBottom()),
			   (GLsizei)(WindowManager::GetWindowWidthf() * GetClippingPlaneRight()),
			   (GLsizei)(WindowManager::GetWindowHeightf() * GetClippingPlaneTop()));
}

//Returns the frustum planes for the camera
//frustumPlanesVector - Reference to a vector container to store the cameras frustum planes in
void Camera::GetFrustumPlanes(vector<vec4>& frustumPlanesVector)
{
	//Store the view world matrix
	mat4 viewProjectionMatrix = GetProjectionMatrix() * GetViewMatrix();

	//Reserve space in the frustum planes vector for storing the cameras frustum planes
	frustumPlanesVector.reserve(6);

	//Store the right frustum plane
	frustumPlanesVector.push_back(vec4(viewProjectionMatrix[0][3] - viewProjectionMatrix[0][0],
									   viewProjectionMatrix[1][3] - viewProjectionMatrix[1][0],
									   viewProjectionMatrix[2][3] - viewProjectionMatrix[2][0],
									   viewProjectionMatrix[3][3] - viewProjectionMatrix[3][0]));

	//Store the left frustum plane
	frustumPlanesVector.push_back(vec4(viewProjectionMatrix[0][3] + viewProjectionMatrix[0][0],
									   viewProjectionMatrix[1][3] + viewProjectionMatrix[1][0],
									   viewProjectionMatrix[2][3] + viewProjectionMatrix[2][0],
									   viewProjectionMatrix[3][3] + viewProjectionMatrix[3][0]));

	//Store the top plane
	frustumPlanesVector.push_back(vec4(viewProjectionMatrix[0][3] - viewProjectionMatrix[0][1],
									   viewProjectionMatrix[1][3] - viewProjectionMatrix[1][1],
									   viewProjectionMatrix[2][3] - viewProjectionMatrix[2][1],
									   viewProjectionMatrix[3][3] - viewProjectionMatrix[3][1]));

	//Store the bottom frustum plane
	frustumPlanesVector.push_back(vec4(-viewProjectionMatrix[0][3] + viewProjectionMatrix[0][1],
									   -viewProjectionMatrix[1][3] + viewProjectionMatrix[1][1],
									   -viewProjectionMatrix[2][3] + viewProjectionMatrix[2][1],
									   -viewProjectionMatrix[3][3] + viewProjectionMatrix[3][1]));

	//Store the far frustum plane
	frustumPlanesVector.push_back(vec4(-viewProjectionMatrix[0][3] - viewProjectionMatrix[0][2],
									   -viewProjectionMatrix[1][3] - viewProjectionMatrix[1][2],
									   -viewProjectionMatrix[2][3] - viewProjectionMatrix[2][2],
									   -viewProjectionMatrix[3][3] - viewProjectionMatrix[3][2]));

	//Store the near frustum plane
	frustumPlanesVector.push_back(vec4(viewProjectionMatrix[0][3] + viewProjectionMatrix[0][2],
									   viewProjectionMatrix[1][3] + viewProjectionMatrix[1][2],
									   viewProjectionMatrix[2][3] + viewProjectionMatrix[2][2],
									   viewProjectionMatrix[3][3] + viewProjectionMatrix[3][2]));

	//Plane normalisation, based on length of normal
	for (unsigned int planeIndex = 0; planeIndex < frustumPlanesVector.size(); ++planeIndex)
	{
		//Normalize plane
		float d = glm::length(vec3(frustumPlanesVector[planeIndex]));
		frustumPlanesVector[planeIndex] /= d;
	}
}

//Returns the Cameras field of view
const float Camera::GetFieldOfView() const
{
	//Return the cameras field of view
	return m_fieldOfView;
}

//Returns the Cameras near clipping plane
const float Camera::GetNearClippingPlane() const
{
	//Return the cameras near clipping plane
	return m_nearClippingPlane;
}

//Returns the Cameras draw distance
const float Camera::GetDrawDistance() const
{
	//Return the cameras draw distance
	return m_drawDistance;
}

//Returns the left most position of the cameras clipping plane
const float Camera::GetClippingPlaneLeft() const
{
	//Return the cameras clipping planes left most position
	return m_clippingPlaneLeft;
}

//Returns the bottom most position of the cameras clipping plane
const float Camera::GetClippingPlaneBottom() const
{
	//Return the cameras clipping planes bottom most position
	return m_clippingPlaneBottom;
}

//Returns the right most position of the cameras clipping plane
const float Camera::GetClippingPlaneRight() const
{
	//Return the cameras clipping planes right most position
	return m_clippingPlaneRight;
}

//Returns the top most position of the cameras clipping plane
const float Camera::GetClippingPlaneTop() const
{
	//Return the cameras clipping planes top most position
	return m_clippingPlaneTop;
}

//Returns the cameras view matrix
mat4 Camera::GetViewMatrix()
{
	//Return the cameras view matrix
	return m_viewMatrix;
}

//Returns the cameras projection matrix
mat4 Camera::GetProjectionMatrix()
{
	//Return the cameras projection matrix
	return m_projectionMatrix;
}

//Sets the cameras field of view to the specified field of view
//fieldOfView - The cameras field of view
void Camera::SetFieldOfView(const float fieldOfView)
{
	//Set the cameras field of view to the specified field of view
	m_fieldOfView = radians(fieldOfView);
}

//Sets the cameras near clipping plane to the specified near clipping plane
//nearClippingPlane - The distance forward from the cameras position to clip before rendering
void Camera::SetNearClippingPlane(const float nearClippingPlane)
{
	//Set the cameras near clipping plane to the specified near clipping plane
	m_nearClippingPlane = nearClippingPlane;
}

//Sets the cameras draw distance to the specified draw distance
//drawDistance - The distance the camera can draw from its near clipping plane forward
void Camera::SetDrawDistance(const float drawDistance)
{
	//Set the cameras draw distance
	m_drawDistance = drawDistance;
}

//Sets the cameras clipping plane region to use the specified values for viewport clipping
//x - The left most position of the clipping plane
//y - The bottom most position of the clipping plane
//w - The right most position of the clipping plane
//h - The top most position of the clipping plane
void Camera::SetClippingPlaneRegion(const float x, const float y, const float w, const float h)
{
	//Set the cameras clipping plane region to the specified clipping plane region
	m_clippingPlaneLeft = x;
	m_clippingPlaneBottom = y;
	m_clippingPlaneRight = w;
	m_clippingPlaneTop = h;
}