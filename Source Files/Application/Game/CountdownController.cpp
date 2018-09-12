//Internal includes
#include "ApplicationHeaders.h"

//Called on initialization
void CountdownController::Awake()
{
	//Initialize parent
	parent = GetParent();

	//Initialize number
	number = parent->AddComponent<GUIObject>();
	number->SetTextureMap("Textures/Countdown3.png");
	number->SetScale(GUIManager::CreateScaleFromReference(vec2(1920.0f, 1080.0f), vec2(115.0f, 173.0f)));
	number->SetPosition(GUIManager::CreatePositionFromReference(vec2(1920.0f, 1080.0f), vec2(902.5f, 453.5f)));
	number->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

	//Initialize state manager
	stateManager = shared_ptr<StateManager>(new StateManager());
	stateManager->SetState(COUNTDOWN_STATE_3);
}

//Performs countdown operation
//Function returns true if the countdown is finished
const bool CountdownController::Countdown()
{
	//Depending on the countdown state
	switch (stateManager->GetState())
	{
		//Countdown number 3
		case COUNTDOWN_STATE_3:
		{
			//Set number texture to countdown 3
			number->SetTextureMap("Textures/Countdown3.png");

			//Fade in number
			if (number->FadeIn(1.0f * Time::deltaTime))
			{
				//Set number alpha channel value to 0
				number->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

				//Set state to count down state 2
				stateManager->SetState(COUNTDOWN_STATE_2);
			}
			break;
		}

		//Countdown number 2
		case COUNTDOWN_STATE_2:
		{
			//Set number texture to countdown 2
			number->SetTextureMap("Textures/Countdown2.png");

			//Fade in number
			if (number->FadeIn(1.0f * Time::deltaTime))
			{
				//Set number alpha channel value to 0
				number->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

				//Set state to count down state 1
				stateManager->SetState(COUNTDOWN_STATE_1);
			}
			break;
		}

		//Countdown number 1
		case COUNTDOWN_STATE_1:
		{
			//Set number texture to countdown 1
			number->SetTextureMap("Textures/Countdown1.png");

			//Fade in number
			if (number->FadeIn(1.0f * Time::deltaTime))
			{
				//Set number alpha channel value to 0
				number->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.0f));

				//Set state to count down state finished
				stateManager->SetState(COUNTDOWN_STATE_FINISHED);
			}
			break;
		}

		//Countdown finished
		case COUNTDOWN_STATE_FINISHED:
		{
			//Set state to count down state 3
			stateManager->SetState(COUNTDOWN_STATE_3);

			//Countdown is finished
			return true;
		}
	}

	//Countdown is not finished
	return false;
}