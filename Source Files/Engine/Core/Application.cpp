//Internal includes
#include "Application.h"
#include "ApplicationHeaders.h"

//Using directives
using std::to_string;

//Starts the application
void Application::Start()
{
	//Use the maximum number of threads supported by the system
	omp_set_num_threads(omp_get_num_procs());

	//Load the ApplicationSettings.config files text
	File applicationSettingsFile = FileImporter::ImportFile("ApplicationSettings.config");

	//Get the computer name
	string computerName = System::GetComputersName();

	//If the name of the computer name is different to the computer name in the ApplicationSettings.config file
	if (computerName != applicationSettingsFile.GetLine(0))
	{
		//If the user answers yes to having settings automatically optimized
		if (QuestionMessageWindow("Question", "This appears to be the first time you are playing from this computer.\nDo you want to automatically optimize settings?").GetAnswer())
		{
			//Erase the contents of the application settings file
			applicationSettingsFile.Empty();

			//Add the name of the computer to the application settings file
			applicationSettingsFile.AddLine(computerName);

			//Add the native resolution of the computers primary monitor to the application settings file
			applicationSettingsFile.AddLine(to_string(System::GetPrimaryMonitorWidthi()));
			applicationSettingsFile.AddLine(to_string(System::GetPrimaryMonitorHeighti()));

			//Save optimizations
			FileExporter::ExportFile(applicationSettingsFile, "ApplicationSettings.config");
		}
	}

	//Initialize window manager
	WindowManager::Initialize();

	//Create application window
	WindowManager::CreateWindow("Online Pong", stoi(applicationSettingsFile.GetLine(1)), stoi(applicationSettingsFile.GetLine(2)), 8, true);

	//Initialize Random module
	Random::Initialize();

	//Initialize Input
	Input::Initialize();

	//Initialize the font manager
	FontManager::Initialize();

	//Load fonts
	FontManager::LoadFont("Fonts/arial.ttf", 24);

	//Initialize the renderer
	ForwardRenderer::Initialize();

	//Load textures
	TextureManager::LoadTexture("Textures/ArphenionLogo.png");
	TextureManager::LoadTexture("Textures/SmokeEffect.png");
	TextureManager::LoadTexture("Textures/PongLabel.png");
 	TextureManager::LoadTexture("Textures/SingleplayerLabelSelected.png");
	TextureManager::LoadTexture("Textures/SingleplayerLabelUnselected.png");
	TextureManager::LoadTexture("Textures/MultiplayerLabelSelected.png");
	TextureManager::LoadTexture("Textures/MultiplayerLabelUnselected.png");
	TextureManager::LoadTexture("Textures/OptionsLabelSelected.png");
	TextureManager::LoadTexture("Textures/OptionsLabelUnselected.png");
	TextureManager::LoadTexture("Textures/ExitLabelSelected.png");
	TextureManager::LoadTexture("Textures/ExitLabelUnselected.png");
	TextureManager::LoadTexture("Textures/Paddle.png");
	TextureManager::LoadTexture("Textures/Ball.png");
	TextureManager::LoadTexture("Textures/BallEffect.png");
	TextureManager::LoadTexture("Textures/Countdown3.png");
	TextureManager::LoadTexture("Textures/Countdown2.png");
	TextureManager::LoadTexture("Textures/Countdown1.png");
	TextureManager::LoadTexture("Textures/Score0.png");
	TextureManager::LoadTexture("Textures/Score1.png");
	TextureManager::LoadTexture("Textures/Score2.png");
	TextureManager::LoadTexture("Textures/Score3.png");
	TextureManager::LoadTexture("Textures/Score-.png");
	TextureManager::LoadTexture("Textures/ConnectingToServerLabel.png");
	TextureManager::LoadTexture("Textures/WaitingForGameLabel.png");
	TextureManager::LoadTexture("Textures/LoadingIcon01.png");
	TextureManager::LoadTexture("Textures/LoadingIcon02.png");
	TextureManager::LoadTexture("Textures/LoadingIcon03.png");
	TextureManager::LoadTexture("Textures/LoadingIcon04.png");
	TextureManager::LoadTexture("Textures/LoadingIcon05.png");
	TextureManager::LoadTexture("Textures/LoadingIcon06.png");
	TextureManager::LoadTexture("Textures/LoadingIcon07.png");
	TextureManager::LoadTexture("Textures/LoadingIcon08.png");
	TextureManager::LoadTexture("Textures/DefaultMouse.png");
	TextureManager::LoadTexture("Textures/Button.png");
	TextureManager::LoadTexture("Textures/DefaultHorizontalSliderHandle.png");
	TextureManager::LoadTexture("Textures/DefaultHorizontalSliderTrack.png");

	//Load MainMenu scene
	SceneManager::LoadScene<IntroductionScene>();
}

//Updates the application
void Application::Update()
{
	//Until the application window receives a close message
	while (!WindowManager::ShouldClose())
	{
		//Process window messages
		WindowManager::ProcessMessages();

		//Update time attributes
		Time::UpdateTimeAttributes();

		//Update mouse position
		Input::UpdateMousePosition();

		//Update event listeners
		EventListenerManager::UpdateAllEventListeners();

		//Update all GameObjects
		GameObjectManager::UpdateAllGameObjects();

		//Clear the windows graphics buffer
		WindowManager::ClearGraphicsBuffer();

		//Render frame
		ForwardRenderer::RenderFrame();

		//Swap the windows graphics buffers
		WindowManager::SwapGraphicsBuffers();
	}
}

//Quits the application
void Application::Quit()
{
	//Destroy all GameObjects
	GameObjectManager::DestroyAllGameObjects();

	//Destroy all GUI elements
	GUIManager::DestroyAllGUIElements();

	//Destroy all textures
	TextureManager::DestroyAllTextures();

	//Shutdown the font manager
	FontManager::Shutdown();

	//Terminate the window manager
	WindowManager::Terminate();

	//Terminate the application
	exit(0);
}