//Internal includes
#include "Application.h"

//External includes
#include <GL\glew.h>

//Initialize static deferred renderer attributes
Shader DeferredRenderer::m_geometryPassShader = Shader();
Shader DeferredRenderer::m_lightPassShader = Shader();
Shader DeferredRenderer::m_compositePassShader = Shader();
Shader DeferredRenderer::m_particleDrawShader = Shader();
Shader DeferredRenderer::m_particleUpdateShader = Shader();
StaticMesh DeferredRenderer::m_quad = StaticMesh();
unsigned int DeferredRenderer::m_geometryFBO = 0;
unsigned int DeferredRenderer::m_diffuseTextureSampler = 0;
unsigned int DeferredRenderer::m_positionTextureSampler = 0;
unsigned int DeferredRenderer::m_normalTextureSampler = 0;
unsigned int DeferredRenderer::m_depthRenderBuffer = 0;
unsigned int DeferredRenderer::m_lightFBO = 0;
unsigned int DeferredRenderer::m_lightTextureSampler = 0;

//Initializes the Deferred renderer
void DeferredRenderer::Initialize()
{
	//Initialize DeferredRenderer
	m_geometryPassShader = Shader("Shaders/GeometryPass.vs", "Shaders/GeometryPass.fs");
	m_geometryPassShader.CreateAttributeMatrix4x4("projectionMatrix");
	m_geometryPassShader.CreateAttributeMatrix4x4("viewMatrix");
	m_geometryPassShader.CreateAttributeMatrix4x4("worldMatrix");
	m_geometryPassShader.CreateAttributeMatrix3x3("normalMatrix");
	m_geometryPassShader.CreateAttributeTextureSampler("diffuseMap");
	m_geometryPassShader.CreateAttributeTextureSampler("normalMap");
	m_lightPassShader = Shader("Shaders/LightPass.vs", "Shaders/LightPass.fs");
	m_lightPassShader.CreateAttributeMatrix4x4("viewMatrix");
	m_lightPassShader.CreateAttributeTextureSampler("positionMap");
	m_lightPassShader.CreateAttributeTextureSampler("normalMap");
	m_compositePassShader = Shader("Shaders/CompositePass.vs", "Shaders/CompositePass.fs");
	m_compositePassShader.CreateAttributeTextureSampler("diffuseMap");
	m_compositePassShader.CreateAttributeTextureSampler("lightMap");
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
	m_quad.LoadMesh("Primitives/FullscreenQuad.model");
	glGenFramebuffers(1, &m_geometryFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_geometryFBO);
	glGenTextures(1, &m_diffuseTextureSampler);
	glBindTexture(GL_TEXTURE_2D, m_diffuseTextureSampler);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, (GLsizei)WindowManager::GetWindowWidthi(), (GLsizei)WindowManager::GetWindowHeighti());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glGenTextures(1, &m_positionTextureSampler);
	glBindTexture(GL_TEXTURE_2D, m_positionTextureSampler);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB32F, (GLsizei)WindowManager::GetWindowWidthi(), (GLsizei)WindowManager::GetWindowHeighti());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glGenTextures(1, &m_normalTextureSampler);
	glBindTexture(GL_TEXTURE_2D, m_normalTextureSampler);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB32F, (GLsizei)WindowManager::GetWindowWidthi(), (GLsizei)WindowManager::GetWindowHeighti());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glGenRenderbuffers(1, &m_depthRenderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_geometryFBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, (GLsizei)WindowManager::GetWindowWidthi(), (GLsizei)WindowManager::GetWindowHeighti());
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_diffuseTextureSampler, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_positionTextureSampler, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, m_normalTextureSampler, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthRenderBuffer);
	GLenum geometryTargets[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, geometryTargets);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glGenFramebuffers(1, &m_lightFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_lightFBO);
	glGenTextures(1, &m_lightTextureSampler);
	glBindTexture(GL_TEXTURE_2D, m_lightTextureSampler);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, (GLsizei)WindowManager::GetWindowWidthi(), (GLsizei)WindowManager::GetWindowHeighti());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_lightTextureSampler, 0);
	GLenum lightTargets[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, lightTargets);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//Renders a frame to the windows back buffer
void DeferredRenderer::RenderFrame()
{
	//Enable depth testing
	glEnable(GL_DEPTH_TEST);

	//Bind and setup the geometry framebuffer object
	glBindFramebuffer(GL_FRAMEBUFFER, m_geometryFBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Use the geometry pass shader
	m_geometryPassShader.Use();

	//For each camera
	for (unsigned int cameraIndex = 0; cameraIndex < CameraManager::GetCameraCount(); ++cameraIndex)
	{
		//Store pointer to the camera
		Camera* p_camera = CameraManager::GetCameraAt(cameraIndex);

		//Update the camera
		p_camera->Update();

		//Store the cameras frustum planes
		vector<vec4> frustumPlaneContainer;
		p_camera->GetFrustumPlanes(frustumPlaneContainer);

		//Update geometry pass shader uniform attributes applicable to the Camera
		m_geometryPassShader.SetAttributeMatrix4x4("projectionMatrix", p_camera->GetProjectionMatrix());
		m_geometryPassShader.SetAttributeMatrix4x4("viewMatrix", p_camera->GetViewMatrix());

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
				//For each of the cameras frustum planes
				for (unsigned int frustumPlaneIndex = 0; frustumPlaneIndex < frustumPlaneContainer.size(); ++frustumPlaneIndex)
				{
					//Calculate intermediary value
					float d = dot(vec3(frustumPlaneContainer[frustumPlaneIndex]), p_transform->GetPosition() + p_mesh->GetLocalBoundingSphereCentre()) + frustumPlaneContainer[frustumPlaneIndex].w;

					//If the GameObject is behind the frustum plane
					if (d < -p_mesh->GetBoundingSphereRadius())
					{
						//Continue to the next GameObject
						break;
					}
					//Otherwise if the sphere radius is touching the frustum plane
					else if (d < p_mesh->GetBoundingSphereRadius())
					{
						//Update geometry pass shader uniform attributes applicable to the GameObject
						m_geometryPassShader.SetAttributeMatrix4x4("worldMatrix", p_transform->GetWorldMatrix());
						m_geometryPassShader.SetAttributeMatrix3x3("normalMatrix", p_transform->GetNormalMatrix(p_camera));
						m_geometryPassShader.SetAttributeTextureSampler("diffuseMap", p_material->GetDiffuseMapTextureSampler());
						m_geometryPassShader.SetAttributeTextureSampler("normalMap", p_material->GetNormalMapTextureSampler());

						//Update the geometry pass shader uniform attributes to GPU
						m_geometryPassShader.UpdateUniformAttributesToGPU();

						//Render the GameObject
						p_mesh->Render();

						//Continue to the next GameObject
						break;
					}
					//Otherwise the GameObject is full visible
					else
					{
						//Update geometry pass shader uniform attributes applicable to the GameObject
						m_geometryPassShader.SetAttributeMatrix4x4("worldMatrix", p_transform->GetWorldMatrix());
						m_geometryPassShader.SetAttributeMatrix3x3("normalMatrix", p_transform->GetNormalMatrix(p_camera));
						m_geometryPassShader.SetAttributeTextureSampler("diffuseMap", p_material->GetDiffuseMapTextureSampler());
						m_geometryPassShader.SetAttributeTextureSampler("normalMap", p_material->GetNormalMapTextureSampler());

						//Update the geometry pass shader uniform attributes to GPU
						m_geometryPassShader.UpdateUniformAttributesToGPU();

						//Render the GameObject
						p_mesh->Render();

						//Continue to the next GameObject
						break;
					}
				}
			}
		}
	}

	//Bind and setup the light framebuffer object
	glBindFramebuffer(GL_FRAMEBUFFER, m_lightFBO);
	glClear(GL_COLOR_BUFFER_BIT);

	//Disable depth testing
	glDisable(GL_DEPTH_TEST);

	//Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);

	//Use the light pass shader
	m_lightPassShader.Use();

	//Update light pass shader uniform attributes
	m_lightPassShader.SetAttributeTextureSampler("positionMap", m_positionTextureSampler);
	m_lightPassShader.SetAttributeTextureSampler("normalMap", m_normalTextureSampler);

	//For each camera
	for (unsigned int cameraIndex = 0; cameraIndex < CameraManager::GetCameraCount(); ++cameraIndex)
	{
		//Store pointer to the camera
		Camera* p_camera = CameraManager::GetCameraAt(cameraIndex);

		//Update the camera
		p_camera->Update();

		//Update geometry pass shader uniform attributes applicable to the Camera
		m_lightPassShader.SetAttributeMatrix4x4("viewMatrix", p_camera->GetViewMatrix());

		//Update the light pass shader uniform attributes to GPU
		m_lightPassShader.UpdateUniformAttributesToGPU();

		//Render fullscreen quad
		m_quad.Render();
	}

	//Disable blending
	glDisable(GL_BLEND);

	//Bind and setup the back bufer framebuffer object
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//Use the composite pass shader
	m_compositePassShader.Use();

	//Update composite pass shader uniform attributes
	m_compositePassShader.SetAttributeTextureSampler("diffuseMap", m_diffuseTextureSampler);
	m_compositePassShader.SetAttributeTextureSampler("lightMap", m_lightTextureSampler);

	//Update the composite pass shader uniform attributes to GPU
	m_compositePassShader.UpdateUniformAttributesToGPU();

	//Draw fullscreen quad
	m_quad.Render();
}