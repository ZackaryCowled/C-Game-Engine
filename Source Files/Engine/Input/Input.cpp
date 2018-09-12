//Internal includes
#include "Application.h"

//External includes
#include <Windows.h>
#include <GLFW\glfw3.h>

//Initialize static Input attributes
vec2 Input::m_virtualMousePosition = vec2(0.0f, 0.0f);
vec2 Input::m_currentMousePosition = vec2(0.0f, 0.0f);
vec2 Input::m_previousMousePosition = vec2(0.0f, 0.0f);

//Initializes the Input class
void Input::Initialize()
{
	//Initialize Input
	m_virtualMousePosition = GetPhysicalMousePosition();
	m_currentMousePosition = m_virtualMousePosition;
	m_previousMousePosition = m_virtualMousePosition;
}

//Updates the mouses position
void Input::UpdateMousePosition()
{
	//Update mouse position
	m_previousMousePosition = m_currentMousePosition;
	m_currentMousePosition = GetPhysicalMousePosition();
	m_virtualMousePosition += vec2(GetAxis(MOUSE_AXIS_X), GetAxis(MOUSE_AXIS_Y));

	//Fix virtual mouse position
	if (m_virtualMousePosition.x < 0.0f) m_virtualMousePosition.x = 0.0f;
	if (m_virtualMousePosition.x > WindowManager::GetWindowWidthf()) m_virtualMousePosition.x = WindowManager::GetWindowWidthf();
	if (m_virtualMousePosition.y < 0.0f) m_virtualMousePosition.y = 0.0f;
	if (m_virtualMousePosition.y > WindowManager::GetWindowHeightf()) m_virtualMousePosition.y = WindowManager::GetWindowHeightf();
}

//Returns the value of the specified axis
float Input::GetAxis(const unsigned int axis)
{
	//Depending on the axis
	switch (axis)
	{
		//Return the mouse axis x value
		case MOUSE_AXIS_X: return m_currentMousePosition.x - m_previousMousePosition.x;

		//Return the mouse axis y value
		case MOUSE_AXIS_Y: return m_currentMousePosition.y - m_previousMousePosition.y;
	}

	//The specified axis does not exist
	return 0.0f;
}

//Returns the position of the virtual mouse
vec2 Input::GetMousePosition()
{
	//Return the position of the virtual mouse
	return m_virtualMousePosition;
}

//Returns the position of the actual mouse
vec2 Input::GetPhysicalMousePosition()
{
	//Store the mouses position
	double mousePositionX;
	double mousePositionY;
	glfwGetCursorPos((GLFWwindow*)WindowManager::GetWindowHandle(), &mousePositionX, &mousePositionY);

	//Return the mouses position
	return vec2((float)mousePositionX, (float)mousePositionY);
}

//Returns the state of the specified key
bool Input::GetKey(const unsigned int keycode)
{
	//Return the state of the specified key
	if (GetAsyncKeyState(keycode))
	{
		//The specified key is down
		return true;
	}

	//The specified key is not down
	return false;
}

//Returns the state of the specified mouse button
bool Input::GetMouseButton(const unsigned int button)
{
	//Return the state of the specified mouse button
	if (GetAsyncKeyState(button))
	{
		//The specified mouse button is down
		return true;
	}

	//The specified mouse buttton is not down
	return false;
}