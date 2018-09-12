//Pragma comments
#pragma once

//External includes
#include <vector>

//Using directives
using std::vector;

//Forward declarations
class Camera;

//Singleton object used for managing the applications camera components
class CameraManager
{
public:
	//Returns the camera at the specified index in the applications camera container
	static Camera* GetCameraAt(const unsigned int index);

	//Returns the number of camera components in the applications camera container
	static const unsigned int GetCameraCount();

	//Registers the specified camera
	static void RegisterCamera(Camera* p_camera);

	//Unregisters the specified camera
	static void UnregisterCamera(Camera* p_camera);

private:
	//Container for storing the applications camera components
	static vector<Camera*> m_cameraContainer;
};