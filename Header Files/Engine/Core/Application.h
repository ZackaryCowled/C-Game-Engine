//Pragma comments
#pragma once
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

//Internal includes
#include "Camera.h"
#include "CameraManager.h"
#include "Component.h"
#include "ComponentTypeList.h"
#include "DeferredRenderer.h"
#include "DirectionalLight.h"
#include "ErrorMessageWindow.h"
#include "EventListener.h"
#include "EventListenerManager.h"
#include "File.h"
#include "FileExporter.h"
#include "FileImporter.h"
#include "FontManager.h"
#include "ForwardRenderer.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "GUICharacter.h"
#include "GUIHorizontalSlider.h"
#include "GUIManager.h"
#include "GUIObject.h"
#include "GUIString.h"
#include "Input.h"
#include "LightManager.h"
#include "Material.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "ParticleSystemManager.h"
#include "PointLight.h"
#include "PostProcessManager.h"
#include "QuestionMessageWindow.h"
#include "Random.h"
#include "SceneManager.h"
#include "Script.h"
#include "Shader.h"
#include "StaticMesh.h"
#include "System.h"
#include "TextureManager.h"
#include "Time.h"
#include "Transform.h"
#include "WindowManager.h"

//External includes
#include <omp.h>

//Singleton object used for managing the application
class Application
{
public:
	//Starts the application
	static void Start();

	//Updates the application
	static void Update();

	//Quits the application
	static void Quit();
};