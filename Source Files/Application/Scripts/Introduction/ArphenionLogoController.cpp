//Internal includes
#include "ApplicationHeaders.h"

//Called on initialization
void ArphenionLogoController::Awake()
{
	//Initialize parent
	parent = GetParent();

	//Initialize arphenion logo
	arphenionLogo = parent->AddComponent<GUIObject>();
	arphenionLogo->SetTextureMap("Textures/ArphenionLogo.png");
	arphenionLogo->SetScale(GUIManager::CreateScaleFromReference(vec2(1920.0f, 1080.0f), vec2(1920.0f, 1080.0f)));
	arphenionLogo->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), vec2(0.0f, 0.0f)));
	arphenionLogo->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));
}

//Returns the arphenion logo the arphenion logo controller is controlling
GUIObject* ArphenionLogoController::GetArphenionLogo()
{
	//Return the arphenion logo the arphenion logo controller is controlling
	return arphenionLogo;
}