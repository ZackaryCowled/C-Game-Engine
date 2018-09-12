//Pragma comments
#pragma once

//Singleton object that provides various functions for loading, using and terminating GLFW and GLEW
class WindowManager
{
public:
	//Initializes GLFW
	static void Initialize();

	//Terminates GLFW
	static void Terminate();

	//Creates a window with the specified properties
	//title - The title for the window
	//width - The width of the window in pixels
	//height - The height of the window in pixels
	//antialiasingSamples - The number of anitaliasing samples to use
	//fullscreen - Whether to create a fullscreen or windowed window
	static void CreateWindow(const char* title, const int width, const int height, const int anitialiasingSamples, bool fullscreen);

	//Returns true if the application window exists
	static bool WindowExists();

	//Processes the application windows messages
	static void ProcessMessages();

	//Swaps the windows back graphics buffer with its front
	static void SwapGraphicsBuffers();

	//Returns true if the application window should close
	static bool ShouldClose();

	//Clears the application windows back graphics buffer
	static void ClearGraphicsBuffer();

	//Returns a handle to the window
	static void* GetWindowHandle();

	//Returns the width of the windows client area in pixels
	static int GetWindowWidthi();

	//Returns the width of the windows client area in pixels
	static float GetWindowWidthf();

	//Returns the height of the windows client area in pixels
	static int GetWindowHeighti();

	//Returns the height of the windows client area in pixel
	static float GetWindowHeightf();

private:
	//Flag representing whether GLFW is initialized
	static bool m_glfwInitialized;

	//Flag representing whether GLEW is initialized
	static bool m_glewInitialized;

	//Pointer to the windows handle
	static void* mp_windowHandle;

	//The width of the window in pixels
	static int m_windowWidth;

	//The height of the window in pixels
	static int m_windowHeight;
};