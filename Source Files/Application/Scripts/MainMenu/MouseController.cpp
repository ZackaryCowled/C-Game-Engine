//Internal includes
#include "ApplicationHeaders.h"

//Called on initialization
void MouseController::Awake()
{
	//Initialize parent
	parent = GetParent();

	//Initialize mouse
	mouse = parent->AddComponent<GUIObject>();
	mouse->SetTextureMap("Textures/DefaultMouse.png");
	mouse->SetScale(GUIManager::CreateScaleFromReference(vec2(1920.0f, 1080.0f), vec2(55.0f, 61.0f)));
	mouse->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), vec2(932.5f, 509.5f)));
	mouse->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));
}

//Updates the mouse the mouse controller is controlling
void MouseController::Update()
{
	//Update mouse position
	mouse->SetPosition(Input::GetMousePosition());
}

//Returns the mouse the mouse controller is controlling
GUIObject* MouseController::GetMouse()
{
	//Return the mouse the mouse controller is controlling
	return mouse;
}