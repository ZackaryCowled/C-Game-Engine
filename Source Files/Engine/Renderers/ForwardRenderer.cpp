//Internal includes
#include "Application.h"

//External includes
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <vector>

//Using directives
using namespace glm;
using std::vector;

//Initialize static forward renderer attributes
Shader ForwardRenderer::m_physicallyBasedShader = Shader();
Shader ForwardRenderer::m_particleDrawShader = Shader();
Shader ForwardRenderer::m_particleUpdateShader = Shader();
Shader ForwardRenderer::m_guiObjectShader = Shader();
Shader ForwardRenderer::m_guiCharacterShader = Shader();
Shader ForwardRenderer::m_compositeShader = Shader();
StaticMesh ForwardRenderer::m_fullscreenQuad = StaticMesh();
unsigned int ForwardRenderer::m_frameBufferObject = 0;
unsigned int ForwardRenderer::m_frameBufferTexture = 0;
unsigned int ForwardRenderer::m_depthBuffer = 0;
unsigned int ForwardRenderer::m_previousFrameDrawCount = 0;

//Initializes the Forward renderer
void ForwardRenderer::Initialize()
{
	//Initialize ForwardRenderer
	m_physicallyBasedShader = Shader("Shaders/Standard.vs", "Shaders/Standard.fs");
	m_physicallyBasedShader.CreateAttributeMatrix4x4("projectionMatrix");
	m_physicallyBasedShader.CreateAttributeMatrix4x4("viewMatrix");
	m_physicallyBasedShader.CreateAttributeMatrix4x4("worldMatrix");
	m_physicallyBasedShader.CreateAttributeMatrix3x3("normalMatrix");
	m_physicallyBasedShader.CreateAttributeTextureSampler("diffuseMap");
	m_physicallyBasedShader.CreateAttributeTextureSampler("normalMap");
	m_physicallyBasedShader.CreateAttributeFloat("roughness");
	m_physicallyBasedShader.CreateAttributeFloat("reflectiveness");
	m_physicallyBasedShader.CreateAttributeVector3("directionalLightPosition");
	m_physicallyBasedShader.CreateAttributeVector3("directionalLightColor");
	m_physicallyBasedShader.CreateAttributeFloat("directionalLightIntensity");
	m_physicallyBasedShader.CreateAttributeVector3("pointLightPosition");
	m_physicallyBasedShader.CreateAttributeVector3("pointLightColor");
	m_physicallyBasedShader.CreateAttributeFloat("pointLightIntensity");
	m_particleDrawShader = Shader("Shaders/ParticleDraw.vs", "Shaders/ParticleDraw.gs", "Shaders/ParticleDraw.fs");
	m_particleDrawShader.CreateAttributeMatrix4x4("projectionMatrix");
	m_particleDrawShader.CreateAttributeMatrix4x4("viewMatrix");
	m_particleDrawShader.CreateAttributeMatrix4x4("worldMatrix");
	m_particleDrawShader.CreateAttributeFloat("sizeStart");
	m_particleDrawShader.CreateAttributeFloat("sizeEnd");
	m_particleDrawShader.CreateAttributeVector4("colorStart");
	m_particleDrawShader.CreateAttributeVector4("colorEnd");
	m_particleDrawShader.CreateAttributeTextureSampler("diffuseMap");
	m_particleUpdateShader = Shader("Shaders/ParticleUpdate.vs", { "position", "velocity", "lifetime", "lifespan" });
	m_particleUpdateShader.CreateAttributeFloat("time");
	m_particleUpdateShader.CreateAttributeFloat("deltaTime");
	m_particleUpdateShader.CreateAttributeVector3("emitterPosition");
	m_particleUpdateShader.CreateAttributeFloat("lifeMin");
	m_particleUpdateShader.CreateAttributeFloat("lifeMax");
	m_guiObjectShader = Shader("Shaders/GUIObject.vs", "Shaders/GUIObject.gs", "Shaders/GUIObject.fs");
	m_guiObjectShader.CreateAttributeFloat("screenWidth");
	m_guiObjectShader.CreateAttributeFloat("screenHeight");
	m_guiObjectShader.CreateAttributeTextureSampler("textureSampler");
	m_guiCharacterShader = Shader("Shaders/GUICharacter.vs", "Shaders/GUICharacter.gs", "Shaders/GUICharacter.fs");
	m_guiCharacterShader.CreateAttributeFloat("screenWidth");
	m_guiCharacterShader.CreateAttributeFloat("screenHeight");
	m_guiCharacterShader.CreateAttributeTextureSampler("textureSampler");
	m_compositeShader = Shader("Shaders/CompositePass.vs", "Shaders/CompositePass.fs");
	m_compositeShader.CreateAttributeFloat("time");
	m_compositeShader.CreateAttributeFloat("distort");
	m_compositeShader.CreateAttributeTextureSampler("textureSampler");
	m_fullscreenQuad.LoadMesh("Primitives/FullscreenQuad.model");
	glGenFramebuffers(1, &m_frameBufferObject);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferObject);
	glGenTextures(1, &m_frameBufferTexture);
	glBindTexture(GL_TEXTURE_2D, m_frameBufferTexture);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, (GLsizei)WindowManager::GetWindowWidthf(), (GLsizei)WindowManager::GetWindowHeightf());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_frameBufferTexture, 0);
	glGenRenderbuffers(1, &m_depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_frameBufferObject);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, (GLsizei)WindowManager::GetWindowWidthf(), (GLsizei)WindowManager::GetWindowHeightf());
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBuffer);
	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBuffers);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//Renders a frame to the windows back buffer
void ForwardRenderer::RenderFrame()
{
	//Number of GameObjects drawn this frame
	int drawCount = 0;

	//Bind the frame buffer object
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferObject);

	//Clear the frame buffer texture
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Use the physically based shader
	m_physicallyBasedShader.Use();

	//For each camera
	for (unsigned int cameraIndex = 0; cameraIndex < CameraManager::GetCameraCount(); ++cameraIndex)
	{
		//Store pointer to the Camera
		Camera* p_camera = CameraManager::GetCameraAt(cameraIndex);

		//Update camera
		p_camera->Update();

		//Store the cameras frustum planes
		vector<vec4> frustumPlaneContainer;
		p_camera->GetFrustumPlanes(frustumPlaneContainer);

		//Update physically based shader uniform attributes applicable to the Camera
		m_physicallyBasedShader.SetAttributeMatrix4x4("projectionMatrix", p_camera->GetProjectionMatrix());
		m_physicallyBasedShader.SetAttributeMatrix4x4("viewMatrix", p_camera->GetViewMatrix());

		//For 1 directional light
		for (unsigned int directionalLightIndex = 0; directionalLightIndex < 1 && directionalLightIndex < LightManager::GetDirectionalLightCount(); ++directionalLightIndex)
		{
			//Store pointer to the directional light
			DirectionalLight* p_directionalLight = LightManager::GetDirectionalLightAt(directionalLightIndex);

			//Update physically based shader uniform attributes applicable to the directional light
			m_physicallyBasedShader.SetAttributeVector3("directionalLightPosition", p_directionalLight->GetPosition());
			m_physicallyBasedShader.SetAttributeVector3("directionalLightColor", p_directionalLight->GetColor());
			m_physicallyBasedShader.SetAttributeFloat("directionalLightIntensity", p_directionalLight->GetIntensity());
		}

		//For 1 point light
		for (unsigned int pointLightIndex = 0; pointLightIndex < 1 && pointLightIndex < LightManager::GetPointLightCount(); ++pointLightIndex)
		{
			//Store point to the point light
			PointLight* p_pointLight = LightManager::GetPointLightAt(pointLightIndex);

			//Update physically based shader uniform attributes applicable to the point light
			m_physicallyBasedShader.SetAttributeVector3("pointLightPosition", p_pointLight->GetPosition());
			m_physicallyBasedShader.SetAttributeVector3("pointLightColor", p_pointLight->GetColor());
			m_physicallyBasedShader.SetAttributeFloat("pointLightIntensity", p_pointLight->GetIntensity());
		}

		//For each GameObject
		for (unsigned int gameObjectIndex = 0; gameObjectIndex < GameObjectManager::GetGameObjectCount(); ++gameObjectIndex)
		{
			//Store pointer to the GameObject
			GameObject* p_gameObject = GameObjectManager::GetGameObjectAt(gameObjectIndex);

			//Store pointers to the GameObjects applicable components
			Transform* p_transform = p_gameObject->GetComponent<Transform>();
			Material* p_material = p_gameObject->GetComponent<Material>();
			StaticMesh* p_mesh = p_gameObject->GetComponent<StaticMesh>();

			//If the GameObjects applicable components are valid
			if (p_transform && p_material && p_mesh)
			{
				//If the GameObjects bounding sphere is inside or intersecting with the view frustum
				if (IsSphereInsideFrustum(p_transform->GetPosition() + p_mesh->GetLocalBoundingSphereCentre(), p_mesh->GetBoundingSphereRadius(), frustumPlaneContainer))
				{
					//Update physically based shader uniform attributes applicable to the GameObject
					m_physicallyBasedShader.SetAttributeMatrix4x4("worldMatrix", p_transform->GetWorldMatrix());
					m_physicallyBasedShader.SetAttributeMatrix3x3("normalMatrix", p_transform->GetNormalMatrix(p_camera));
					m_physicallyBasedShader.SetAttributeTextureSampler("diffuseMap", p_material->GetDiffuseMapTextureSampler());
					m_physicallyBasedShader.SetAttributeTextureSampler("normalMap", p_material->GetNormalMapTextureSampler());
					m_physicallyBasedShader.SetAttributeFloat("roughness", p_material->GetRoughness());
					m_physicallyBasedShader.SetAttributeFloat("reflectiveness", p_material->GetReflectiveness());

					//Update the physically based shader uniform attributes to GPU
					m_physicallyBasedShader.UpdateUniformAttributesToGPU();

					//Render the GameObject
					p_mesh->Render();

					//Increment draw count
					drawCount++;
				}				
			}
		}
	}

	//Use the particle update shader
	m_particleUpdateShader.Use();

	//Update particle update shader uniform attributes applicable to time
	m_particleUpdateShader.SetAttributeFloat("time", Time::runTime);
	m_particleUpdateShader.SetAttributeFloat("deltaTime", Time::deltaTime);

	//Disable rasterization
	glEnable(GL_RASTERIZER_DISCARD);

	//For each particle system
	for (unsigned int particleSystemIndex = 0; particleSystemIndex < ParticleSystemManager::GetParticleSystemCount(); ++particleSystemIndex)
	{
		//Store pointer to the particle system
		ParticleSystem* p_particleSystem = ParticleSystemManager::GetParticleSystemAt(particleSystemIndex);

		//Store pointer to the particle systems parent GameObject
		GameObject* p_parent = p_particleSystem->GetParent();

		//If the particle systems parent is valid
		if (p_parent)
		{
			//Store pointer to the particle systems parent components that are applicable
			Transform* p_transform = p_parent->GetComponent<Transform>();

			//If the particle systems transform is valid
			if (p_transform)
			{
				//Update particle update shader uniform attributes applicable to the particle system
				m_particleUpdateShader.SetAttributeVector3("emitterPosition", p_transform->GetPosition());
				m_particleUpdateShader.SetAttributeFloat("lifeMin", p_particleSystem->GetMinLife());
				m_particleUpdateShader.SetAttributeFloat("lifeMax", p_particleSystem->GetMaxLife());

				//Update the particle update shader uniform attributes to GPU
				m_particleUpdateShader.UpdateUniformAttributesToGPU();

				//Update the particle system
				p_particleSystem->Update();
			}
		}
	}

	//Enable rasterization
	glDisable(GL_RASTERIZER_DISCARD);

	//Disable the depth mask
	glDepthMask(GL_FALSE);

	//Use the particle draw shader
	m_particleDrawShader.Use();

	//For each camera
	for (unsigned int cameraIndex = 0; cameraIndex < CameraManager::GetCameraCount(); ++cameraIndex)
	{
		//Store pointer to the Camera
		Camera* p_camera = CameraManager::GetCameraAt(cameraIndex);

		//Update camera
		p_camera->Update();

		//Update particle draw shader uniform attributes applicable to the Camera
		m_particleDrawShader.SetAttributeMatrix4x4("projectionMatrix", p_camera->GetProjectionMatrix());
		m_particleDrawShader.SetAttributeMatrix4x4("viewMatrix", p_camera->GetViewMatrix());

		//For each particle system
		for (unsigned int particleSystemIndex = 0; particleSystemIndex < ParticleSystemManager::GetParticleSystemCount(); ++particleSystemIndex)
		{
			//Store pointer to the particle system
			ParticleSystem* p_particleSystem = ParticleSystemManager::GetParticleSystemAt(particleSystemIndex);

			//Store pointer to the particle systems parent GameObject
			GameObject* p_parent = p_particleSystem->GetParent();

			//If the particle systems parent is valid
			if (p_parent)
			{
				//Store pointer to the particle systems parent components that are applicable
				Transform* p_transform = p_parent->GetComponent<Transform>();

				//If the particle systems transform is valid
				if (p_transform)
				{
					//Update particle draw shader uniform attributes applicable to the particle system
					m_particleDrawShader.SetAttributeMatrix4x4("worldMatrix", p_transform->GetWorldMatrix());
					m_particleDrawShader.SetAttributeFloat("sizeStart", p_particleSystem->GetStartSize());
					m_particleDrawShader.SetAttributeFloat("sizeEnd", p_particleSystem->GetEndSize());
					m_particleDrawShader.SetAttributeVector4("colorStart", p_particleSystem->GetStartColor());
					m_particleDrawShader.SetAttributeVector4("colorEnd", p_particleSystem->GetEndColor());
					m_particleDrawShader.SetAttributeTextureSampler("diffuseMap", p_particleSystem->GetDiffuseMapTextureSampler());

					//Update the particle draw shader uniform attributes to GPU
					m_particleDrawShader.UpdateUniformAttributesToGPU();

					//Render the particle system
					p_particleSystem->Render();
				}
			}
		}
	}

	//Enable the depth mask
	glDepthMask(GL_TRUE);

	//Disable depth testing
	glDisable(GL_DEPTH_TEST);

	//Update viewport to use the whole window
	glViewport(0, 0, (GLsizei)WindowManager::GetWindowWidthi(), (GLsizei)WindowManager::GetWindowHeighti());

	//Use the GUI object shader
	m_guiObjectShader.Use();

	//Update GUI object shader uniform attributes applicable to the window
	m_guiObjectShader.SetAttributeFloat("screenWidth", WindowManager::GetWindowWidthf());
	m_guiObjectShader.SetAttributeFloat("screenHeight", WindowManager::GetWindowHeightf());

	//For each GUIObject in the applications GUIObject container
	for (unsigned int guiObjectIndex = 0; guiObjectIndex < GUIManager::GetGUIObjectCount(); ++guiObjectIndex)
	{
		//Store pointer to the GUIObject
		GUIObject* p_guiObject = GUIManager::GetGUIObjectAt(guiObjectIndex);

		//Update GUI object shader uniform attributes applicable to the GUI object
		m_guiObjectShader.SetAttributeTextureSampler("textureSampler", p_guiObject->GetTextureMap());

		//Update the GUI object shader uniform attributes to GPU
		m_guiObjectShader.UpdateUniformAttributesToGPU();

		//Render the GUIObject
		p_guiObject->Render();
	}

	//Use the GUI character shader
	m_guiCharacterShader.Use();

	//Update GUI character shader uniform attributes applicable to the window
	m_guiCharacterShader.SetAttributeFloat("screenWidth", WindowManager::GetWindowWidthf());
	m_guiCharacterShader.SetAttributeFloat("screenHeight", WindowManager::GetWindowHeightf());

	//For each GUIString in the applications GUIString container
	for (unsigned int guiStringIndex = 0; guiStringIndex < GUIManager::GetGUIStringCount(); ++guiStringIndex)
	{
		//Store pointer to the GUIString
		GUIString* p_guiString = GUIManager::GetGUIStringAt(guiStringIndex);

		//For each character in the GUIStrings character container
		for (unsigned int guiCharacterIndex = 0; guiCharacterIndex < p_guiString->GetCharacterCount(); ++guiCharacterIndex)
		{
			//Store reference to the GUICharacter
			GUICharacter* p_guiCharacter = p_guiString->GetCharacterAt(guiCharacterIndex);

			//Update GUI character shader uniform attributes applicable to the GUI character
			m_guiCharacterShader.SetAttributeTextureSampler("textureSampler", p_guiCharacter->GetTextureMap());

			//Update the GUI character shader uniform attributes to GPU
			m_guiCharacterShader.UpdateUniformAttributesToGPU();

			//Render the GUICharacter
			p_guiCharacter->Render();
		}
	}

	//Enable depth testing
	glEnable(GL_DEPTH_TEST);

	//Bind the back buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//Use the composite shader
	m_compositeShader.Use();

	//Update composite shader uniform attributes
	m_compositeShader.SetAttributeFloat("time", Time::runTime);
	m_compositeShader.SetAttributeFloat("distort", PostProcessManager::GetDistort());
	m_compositeShader.SetAttributeTextureSampler("textureSampler", m_frameBufferTexture);

	//Update composite shader uniform attributes to GPU
	m_compositeShader.UpdateUniformAttributesToGPU();

	//Render fullscreen quad
	m_fullscreenQuad.Render();

	//Update previous frame draw count
	m_previousFrameDrawCount = drawCount;
}

//Returns the number of GameObjects that were drawn last frame
const unsigned int ForwardRenderer::GetPreviousFrameDrawCount()
{
	//Return the number of GameObjects that were drawn last frame
	return m_previousFrameDrawCount;
}

//Returns whether the sphere is inside the frustum
bool ForwardRenderer::IsSphereInsideFrustum(vec3& sphereCentre, float sphereRadius, vector<vec4>& frustum)
{
	//Cache distance attribute
	float distance = 0.0f;

	//For each of the frustum planes
	for(unsigned int frustumPlaneIndex = 0; frustumPlaneIndex < frustum.size(); ++frustumPlaneIndex)
	{
		//Calculate distance to frustum plane
		distance = dot(vec3(frustum[frustumPlaneIndex]), sphereCentre) + frustum[frustumPlaneIndex].w;
		
		//If the sphere is outside the frustum plane
		if(distance < -sphereRadius)
		{
			//The sphere is not inside the frustum plane
			return false;
		}
		//Otherwise if the sphere is intersecting with the frustum plane
		else if (distance < sphereRadius)
		{
			//The sphere is intersecting with the frustum plane
			return true;
		}
		//Otherwise
		else
		{
			//The sphere is inside the frustum plane
			return true;
		}
	}

	//Suppress warnings
	return true;
}