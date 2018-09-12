//Internal includes
#include "CameraManager.h"
#include "Application.h"

//Initializes the camera managers camera container
vector<Camera*> InitializeCameraContainer()
{
	//Return an empty camera container
	return vector<Camera*>();
}

//Initialize static camera manager attributes
vector<Camera*> CameraManager::m_cameraContainer(InitializeCameraContainer());

//Returns the camera at the specified index in the applications camera container
Camera* CameraManager::GetCameraAt(const unsigned int index)
{
	//Return the camera at the specified index in the application camera container
	return m_cameraContainer[index];
}

//Returns the number of camera components in the applications camera container
const unsigned int CameraManager::GetCameraCount()
{
	//Return the number of camera components in the applications camera container
	return (unsigned int)m_cameraContainer.size();
}

//Registers the specified camera
void CameraManager::RegisterCamera(Camera* p_camera)
{
	//Register the specified camera
	m_cameraContainer.push_back(p_camera);
}

//Unregisters the specified camera
void CameraManager::UnregisterCamera(Camera* p_camera)
{
	//For each camera in the applications camera container
	for (unsigned int cameraIndex = 0; cameraIndex < m_cameraContainer.size(); cameraIndex++)
	{
		//If the camera is the specified camera
		if (m_cameraContainer[cameraIndex] == p_camera)
		{
			//Erase the camera from the applications camera container
			m_cameraContainer.erase(m_cameraContainer.begin() + cameraIndex);

			//Return from the function
			return;
		}
	}
}