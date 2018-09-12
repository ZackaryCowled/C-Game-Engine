//Pragma comments
#pragma once

//External includes
#include <glm\glm.hpp>

//Using directives
using namespace glm;

//Precompiler definitions
#define MOUSE_AXIS_X 0
#define MOUSE_AXIS_Y 1

//Singleton object providing various functions for querying input events
class Input
{
public:
	//Initializes the Input class
	static void Initialize();

	//Updates the mouses position
	static void UpdateMousePosition();

	//Returns the value of the specified axis
	static float GetAxis(const unsigned int axis);

	//Returns the position of the virtual mouse
	static vec2 GetMousePosition();

	//Returns the position of the actual mouse
	static vec2 GetPhysicalMousePosition();

	//Returns the state of the specified key
	static bool GetKey(const unsigned int keycode);

	//Returns the state of the specified mouse button
	static bool GetMouseButton(const unsigned int button);

private:
	//The virtual position of the mouse
	static vec2 m_virtualMousePosition;

	//The current mouse position
	static vec2 m_currentMousePosition;

	//The previous mouse position
	static vec2 m_previousMousePosition;
};