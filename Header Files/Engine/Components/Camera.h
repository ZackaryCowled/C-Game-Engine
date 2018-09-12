//Pragma comments
#pragma once

//Internal includes
#include "Component.h"

//External includes
#include <glm\glm.hpp>
#include <vector>

//Using directives
using namespace glm;
using std::vector;

//Component used as an eye in 3D space
class Camera : public Component
{
public:
	//Creates and initializes a Camera component (Default constructor)
	Camera();

	//Releases the camera components resources
	~Camera();

	//Destroys the camera component
	void Destroy();

	//Updates the camera (Call before rendering)
	void Update();

	//Returns the frustum planes for the camera
	//frustumPlanesVector - Reference to a vector container to store the cameras frustum planes in
	void GetFrustumPlanes(vector<vec4>& frustumPlanesVector);

	//Returns the Cameras field of view
	const float GetFieldOfView() const;

	//Returns the Cameras near clipping plane
	const float GetNearClippingPlane() const;

	//Returns the Cameras draw distance
	const float GetDrawDistance() const;

	//Returns the left most position of the cameras clipping plane
	const float GetClippingPlaneLeft() const;

	//Returns the bottom most position of the cameras clipping plane
	const float GetClippingPlaneBottom() const;

	//Returns the right most position of the cameras clipping plane
	const float GetClippingPlaneRight() const;

	//Returns the top most position of the cameras clipping plane
	const float GetClippingPlaneTop() const;

	//Returns the cameras view matrix
	mat4 GetViewMatrix();

	//Returns the cameras projection matrix
	mat4 GetProjectionMatrix();

	//Sets the cameras field of view to the specified field of view
	//fieldOfView - The cameras field of view
	void SetFieldOfView(const float fieldOfView);

	//Sets the cameras near clipping plane to the specified near clipping plane
	//nearClippingPlane - The distance forward from the cameras position to clip before rendering
	void SetNearClippingPlane(const float nearClippingPlane);

	//Sets the cameras draw distance to the specified draw distance
	//drawDistance - The distance the camera can draw from its near clipping plane forward
	void SetDrawDistance(const float drawDistance);

	//Sets the cameras clipping plane region to use the specified values for viewport clipping
	//x - The left most position of the clipping plane
	//y - The bottom most position of the clipping plane
	//w - The right most position of the clipping plane
	//h - The top most position of the clipping plane
	void SetClippingPlaneRegion(const float x, const float y, const float w, const float h);

private:
	//The cameras field of view
	float m_fieldOfView;

	//The cameras near clipping plane
	float m_nearClippingPlane;

	//The cameras draw distance
	float m_drawDistance;

	//The left most position of the cameras clipping plane
	float m_clippingPlaneLeft;

	//The bottom most position of the cameras clipping plane
	float m_clippingPlaneBottom;

	//The right most position of the cameras clipping plane
	float m_clippingPlaneRight;

	//The top most position of the cameras clipping plane
	float m_clippingPlaneTop;

	//The cameras view matrix
	mat4 m_viewMatrix;

	//The cameras projection matrix
	mat4 m_projectionMatrix;
};