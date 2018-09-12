//Internal includes
#include "ApplicationHeaders.h"

//Called on initialization
void PongLabelController::Awake()
{
	//Initialize parent
	parent = GetParent();

	//Initialize pong label
	pongLabel = parent->AddComponent<GUIObject>();
	pongLabel->SetTextureMap("Textures/PongLabel.png");
	pongLabel->SetScale(GUIManager::CreateScaleFromReference(vec2(1920.0f, 1080.0f), vec2(358.0f, 109.0f)));
	pongLabel->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), vec2(781.0f, 153.6f)));
	pongLabel->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));
}

//Returns the pong label the pong label controller is controlling
GUIObject* PongLabelController::GetPongLabel()
{
	//Return the pong label the pong label controller is controlling
	return pongLabel;
}