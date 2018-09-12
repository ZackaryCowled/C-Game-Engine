//Internal includes
#include "WindowManager.h"
#include "Application.h"

//External includes
#include <GL\glew.h>
#include <GLFW\glfw3.h>

//Initialize static window manager attributes
bool WindowManager::m_glfwInitialized(false);
bool WindowManager::m_glewInitialized(false);
void* WindowManager::mp_windowHandle(nullptr);
int WindowManager::m_windowWidth(0);
int WindowManager::m_windowHeight(0);

//Initializes GLFW
void WindowManager::Initialize()
{
	//If GLFW is not already initialized
	if (!m_glfwInitialized)
	{
		//Initialize GLFW
		if (!glfwInit())
		{
			//Display error message window
			ErrorMessageWindow("Error", "GLFW failed to initialize!");

			//Quit the application
			Application::Quit();
		}

		//Set the GLFW initialized flag
		m_glfwInitialized = true;
	}
}

//Terminates GLFW
void WindowManager::Terminate()
{
	//If GLFW is initialized
	if (m_glfwInitialized)
	{
		//If the window exists
		if (!mp_windowHandle)
		{
			//Destroy the window
			glfwDestroyWindow((GLFWwindow*)mp_windowHandle);
		}

		//Terminate GLFW
		glfwTerminate();

		//Set the GLFW initialized flag
		m_glfwInitialized = false;
	}
}

//Creates a window with the specified properties
//title - The title for the window
//width - The width of the window in pixels
//height - The height of the window in pixels
//antialiasingSamples - The number of anitaliasing samples to use
//fullscreen - Whether to create a fullscreen or windowed window
void WindowManager::CreateWindow(const char* title, const int width, const int height, const int anitialiasingSamples, bool fullscreen)
{
	//If GLFW has not been initialized
	if (!m_glfwInitialized)
	{
		//Initialize the window manager
		Initialize();
	}

	//If a window already exists
	if (mp_windowHandle)
	{
		//Destroy the application window
		glfwDestroyWindow((GLFWwindow*)mp_windowHandle);
	}

	//Create required attributes
	GLint requiredMajorVersion = 4;
	GLint requiredMinorVersion = 5;

	//Configure window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, requiredMajorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, requiredMinorVersion);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, anitialiasingSamples);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	//Create application window
	mp_windowHandle = glfwCreateWindow(width, height, title, fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);

	//If the window failed to create
	if (!mp_windowHandle)
	{
		//Display error message window
		ErrorMessageWindow("Error", "Window creation failed!");

		//Quit the application
		Application::Quit();
	}

	//Make the application windows OpenGL context current
	glfwMakeContextCurrent((GLFWwindow*)mp_windowHandle);

	//If GLEW is not already initialized
	if (!m_glewInitialized)
	{
		//Enable experimental drivers
		glewExperimental = GL_TRUE;

		//Initialize GLEW
		if (glewInit() != GLEW_OK)
		{
			//Display error message window
			ErrorMessageWindow("Error", "GLEW failed to initialize!");

			//Quit the application
			Application::Quit();
		}

		//Set the GLEW initialized flag
		m_glewInitialized = true;
	}

	//Store the OpenGL major and minor version numbers
	GLint majorVersionNumber = 0;
	GLint minorVersionNumber = 0;
	glGetIntegerv(GL_MAJOR_VERSION, &majorVersionNumber);
	glGetIntegerv(GL_MINOR_VERSION, &minorVersionNumber);

	//If the OpenGL major and minor version numbers do not meet the minimum requirements
	if (majorVersionNumber < requiredMajorVersion || (majorVersionNumber == requiredMajorVersion && minorVersionNumber < requiredMinorVersion))
	{
		//Display error message window
		ErrorMessageWindow("Error", "OpenGL " + std::to_string(majorVersionNumber) + "." + std::to_string(minorVersionNumber) + "is not supported by your system!");

		//Quit the application
		Application::Quit();
	}

	//Disable mouse cursor
	glfwSetInputMode((GLFWwindow*)mp_windowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Disable frame cap
	glfwSwapInterval(0);

	//Enable alpha testing
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_ALWAYS, 0);

	//Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);

	//Enable face culling
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	//Store window attributes
	m_windowWidth = width;
	m_windowHeight = height;
}

//Returns whether a valid window exists
bool WindowManager::WindowExists()
{
	//If the pointer to the windows handle is a null pointer
	if (mp_windowHandle == nullptr)
	{
		//The application window does not exist
		return false;
	}

	//The application window exists
	return true;
}

//Processes the application windows messages
void WindowManager::ProcessMessages()
{
	//If glfw is initialized
	if (m_glfwInitialized)
	{
		//If an application window exists
		if (mp_windowHandle)
		{
			//Process window messages
			glfwPollEvents();
		}
	}
}

//Swaps the windows back graphics buffer with its front
void WindowManager::SwapGraphicsBuffers()
{
	//If glfw is initialized
	if (m_glfwInitialized)
	{
		//If an application window exists
		if (mp_windowHandle)
		{
			//Swap the windows graphics buffers
			glfwSwapBuffers((GLFWwindow*)mp_windowHandle);
		}
	}
}

//Returns true if the application window should close
bool WindowManager::ShouldClose()
{
	//If GLFW is initialized
	if (m_glfwInitialized)
	{
		//If an application window exists
		if (mp_windowHandle)
		{
			//If the application window should close
			if (glfwWindowShouldClose((GLFWwindow*)mp_windowHandle))
			{
				//The window should close
				return true;
			}
		}
	}

	//The window should not close
	return false;
}

//Clears the application windows back graphics buffer
void WindowManager::ClearGraphicsBuffer()
{
	//If an application window exists
	if (mp_windowHandle)
	{
		//If GLEW is initialized
		if (m_glewInitialized)
		{
			//Clear the windows back graphics buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		}
	}
}

//Returns a handle to the window
void* WindowManager::GetWindowHandle()
{
	//Return a handle to the applications window
	return mp_windowHandle;
}

//Returns the width of the windows client area in pixels
int WindowManager::GetWindowWidthi()
{
	//Return the width of the window in pixels
	return m_windowWidth;
}

//Returns the width of the windows client area in pixels
float WindowManager::GetWindowWidthf()
{
	//Return the width of the window in pixels
	return (float)m_windowWidth;
}

//Returns the height of the windows client area in pixels
int WindowManager::GetWindowHeighti()
{
	//Return the height of the window in pixels
	return m_windowHeight;
}

//Returns the height of the windows client area in pixel
float WindowManager::GetWindowHeightf()
{
	//Return the height of the window in pixels
	return (float)m_windowHeight;
}