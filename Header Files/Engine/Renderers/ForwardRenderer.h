//Pragma comments
#pragma once

//Internal includes
#include "GUIObject.h"
#include "Shader.h"
#include "StaticMesh.h"

//External includes
#include <vector>

//Using directives
using std::vector;

//Singleton class providing various methods for rendering a frame with a single pass
class ForwardRenderer
{
public:
	//Initializes the Forward renderer
	static void Initialize();

	//Renders a frame to the windows back buffer
	static void RenderFrame();

	//Returns the number of GameObjects that were drawn last frame
	static const unsigned int GetPreviousFrameDrawCount();

protected:
	//Returns whether the sphere is inside the frustum
	static bool IsSphereInsideFrustum(vec3& sphereCentre, float sphereRadius, vector<vec4>& frustum);

private:
	//The shader to use for rendering mesh
	static Shader m_physicallyBasedShader;

	//The shader to use for rendering particle systems
	static Shader m_particleDrawShader;

	//The shader to use for updating particle systems
	static Shader m_particleUpdateShader;

	//The shader to use for rendering GUI objects
	static Shader m_guiObjectShader;

	//The shader to use for rendering GUI characters
	static Shader m_guiCharacterShader;

	//The shader to user for rendering the final frame with post processing
	static Shader m_compositeShader;

	//The renderers fullscreen quad object
	static StaticMesh m_fullscreenQuad;

	//The renderers frame buffer object
	static unsigned int m_frameBufferObject;

	//The renderers frame buffer texture
	static unsigned int m_frameBufferTexture;

	//The renderers depth buffer
	static unsigned int m_depthBuffer;

	//The previous frames draw count
	static unsigned int m_previousFrameDrawCount;
};