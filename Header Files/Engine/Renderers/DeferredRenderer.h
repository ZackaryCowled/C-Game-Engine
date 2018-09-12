//Pragma comments
#pragma once

//Internal includes
#include "Shader.h"
#include "StaticMesh.h"

//Singleton class providing various methods for rendering a frame with post lighting (Multiple passes)
class DeferredRenderer
{
public:
	//Initializes the Deferred renderer
	static void Initialize();

	//Renders a frame to the windows back buffer
	static void RenderFrame();

private:
	//The shader to use for the geometry pass
	static Shader m_geometryPassShader;

	//The shader to use for the light pass
	static Shader m_lightPassShader;

	//The shader to use for the composite pass
	static Shader m_compositePassShader;

	//The shader to use for rendering particle systems
	static Shader m_particleDrawShader;

	//The shader tp use for updating particle systems
	static Shader m_particleUpdateShader;

	//The quad to render the composite frame
	static StaticMesh m_quad;

	//Frame buffer object to render geometry
	static unsigned int m_geometryFBO;

	//Diffuse texture sampler for geometry
	static unsigned int m_diffuseTextureSampler;

	//Position texture sampler for geometry
	static unsigned int m_positionTextureSampler;

	//Normal texture sampler for geometry
	static unsigned int m_normalTextureSampler;

	//Depth render buffer for geometry
	static unsigned int m_depthRenderBuffer;

	//Frame buffer object to render light
	static unsigned int m_lightFBO;

	//Light texture sampler for light
	static unsigned int m_lightTextureSampler;
};