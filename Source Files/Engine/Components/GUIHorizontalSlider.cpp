//Internal includes
#include "Application.h"

//Creates and initializes a GUIHorizontalSlider instance (Default constructor)
GUIHorizontalSlider::GUIHorizontalSlider()
{
	//Initialize GUIHorizontalSlider
	mp_sliderTrack = new GUIObject();
	mp_sliderHandle = new GUIObject();
	m_position = vec2(0.0f, 0.0f);
	m_percentage = 0.0f;
	m_currentLeftMouseButtonState = false;
	m_previousLeftMouseButtonState = false;
	m_followMouse = false;
	mp_sliderTrack->SetScale(vec2(137.0f, 7.0f));
	mp_sliderTrack->SetTextureMap("Textures/DefaultHorizontalSliderTrack.png");
	mp_sliderHandle->SetScale(vec2(14.0f, 25.0f));
	mp_sliderHandle->SetPosition(vec2(0.0f, -(mp_sliderHandle->GetScale().y * 0.5 - mp_sliderTrack->GetScale().y * 0.5)));
	mp_sliderHandle->SetTextureMap("Textures/DefaultHorizontalSliderHandle.png");
}

//Releases GUIHorizontalSlider resources
GUIHorizontalSlider::~GUIHorizontalSlider()
{
	//If the slider track is valid
	if (mp_sliderTrack)
	{
		//Delete the slider track
		delete mp_sliderTrack;
		mp_sliderTrack = nullptr;
	}

	//If the slider handle is valid
	if (mp_sliderHandle)
	{
		//Delete the slider handle
		delete mp_sliderHandle;
		mp_sliderHandle = nullptr;
	}
}

//Returns the position of the horizontal slider
vec2 GUIHorizontalSlider::GetPosition()
{
	//Return the position of the slider
	return m_position;
}

//Returns the percentage of the slider
float GUIHorizontalSlider::GetPercentage()
{
	//Return the percentage of the slider
	return m_percentage;
}

//Sets the position of the horizontal slider
void GUIHorizontalSlider::SetPosition(const vec2& position)
{
	//Calculate difference in current position and the specified position
	vec2 positionDifference = position - m_position;

	//Set the position of the slider to the specified position
	m_position = position;

	//Offset the slider track and slider handle positions by the position difference
	mp_sliderTrack->SetPosition(mp_sliderTrack->GetPosition() + positionDifference);
	mp_sliderHandle->SetPosition(mp_sliderHandle->GetPosition() + positionDifference);
}

//Sets the slider tracks scale to the specified scale
void GUIHorizontalSlider::SetSliderTrackScale(const vec2& scale)
{
	//Set the slider tracks scale to the specified scale
	mp_sliderTrack->SetScale(scale);
}

//Sets the color of the slider track to the specified color
void GUIHorizontalSlider::SetSliderTrackColor(const vec4& color)
{
	//Set the slider tracks color to the specified color
	mp_sliderTrack->SetColor(color);
}

//Sets the color of the slider handle to the specified color
void GUIHorizontalSlider::SetSliderHandleColor(const vec4& color)
{
	//Set the slider handles color to the specified color
	mp_sliderHandle->SetColor(color);
}

//Sets the slider percentage to the specified percentage
void GUIHorizontalSlider::SetSliderPercentage(const float percentage)
{
	//Set the slider percentage to the specified percentage
	m_percentage = percentage;

	//Calculate offset to make the slider track represent the percentage
	float offset = (mp_sliderTrack->GetScale().x - mp_sliderHandle->GetScale().x) * m_percentage;

	//Set slider handle position to reflect percentage
	mp_sliderHandle->SetPosition(vec2(m_position.x + offset, mp_sliderHandle->GetPosition().y));
}

//Update the slider
void GUIHorizontalSlider::Update()
{
	//Synchronize mouse input state
	m_previousLeftMouseButtonState = m_currentLeftMouseButtonState;
	m_currentLeftMouseButtonState = Input::GetMouseButton(EVENT_TRIGGER_MOUSE_LEFT);

	//If the horizontal slider is following the mouse
	if (m_followMouse)
	{
		//If the left mouse button is up
		if (!m_currentLeftMouseButtonState)
		{
			//Set the follow mouse flag to false
			m_followMouse = false;

			//return from the function
			return;
		}
		//Otherwise
		else
		{
			//Calculate position to set the slider handle to on the x-axis
			float newPositionX = Input::GetMousePosition().x;
			if (newPositionX < m_position.x) newPositionX = m_position.x;
			if (newPositionX > m_position.x + mp_sliderTrack->GetScale().x - mp_sliderHandle->GetScale().x) newPositionX = m_position.x + mp_sliderTrack->GetScale().x - mp_sliderHandle->GetScale().x;

			//Set slider percentage
			SetSliderPercentage((newPositionX - m_position.x) / (mp_sliderTrack->GetScale().x - mp_sliderHandle->GetScale().x));
		}
	}
	//Otherwise
	else
	{
		//Store the mouses position
		vec2 mousePosition = Input::GetMousePosition();

		//If the mouse is over the slider track on the x-axis
		if (mousePosition.x > mp_sliderHandle->GetPosition().x && mousePosition.x < mp_sliderHandle->GetPosition().x + mp_sliderHandle->GetScale().x)
		{
			//If the mouse is over the slider track on the y-axis
			if (mousePosition.y > mp_sliderHandle->GetPosition().y && mousePosition.y < mp_sliderHandle->GetPosition().y + mp_sliderHandle->GetScale().y)
			{
				//If the previous left mouse button state is up and the current left mouse button state is down
				if (!m_previousLeftMouseButtonState && m_currentLeftMouseButtonState)
				{
					//Set the follow mouse flag to true
					m_followMouse = true;
				}
			}
		}
	}
}