//Internal includes
#include "ApplicationHeaders.h"

//Called on initialization
void BackgroundController::Awake()
{
	//Initialize parent
	parent = GetParent();

	//Initialize smoke effect
	smokeEffect = parent->AddComponent<GUIObject>();
	smokeEffect->SetTextureMap("Textures/SmokeEffect.png");
	smokeEffect->SetScale(GUIManager::CreateScaleFromReference(vec2(1920.0f, 1080.0f), vec2(3840.0f, 1080.0f)));
	smokeEffect->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), vec2(0.0f, 0.0f)));
	smokeEffect->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

	//Initialize smoke effect speed
	smokeEffectSpeed = 0.05f;
}

//Updates the background the background controller is controlling
void BackgroundController::Update()
{
	//Update smoke effect
	smokeEffect->SetTextureOffset(smokeEffect->GetTextureOffset() + vec2(smokeEffectSpeed * Time::deltaTime, 0.0f));
}

//Returns the background the background controller is controlling
GUIObject* BackgroundController::GetBackground()
{
	//Return the background the background controller is controlling
	return smokeEffect;
}