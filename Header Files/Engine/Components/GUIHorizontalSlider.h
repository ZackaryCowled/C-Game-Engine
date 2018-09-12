//Pragma comments
#pragma once

//Internal includes
#include "Component.h"

//Forward declarations
class EventListener;
class GUIObject;

//Object to use for building horizontal GUI slider controls
class GUIHorizontalSlider : public Component
{
public:
	//Creates and initializes a GUIHorizontalSlider instance (Default constructor)
	GUIHorizontalSlider();

	//Releases GUIHorizontalSlider resources
	~GUIHorizontalSlider();

	//Returns the position of the horizontal slider
	vec2 GetPosition();

	//Returns the percentage of the slider
	float GetPercentage();
	
	//Sets the position of the horizontal slider
	void SetPosition(const vec2& position);

	//Sets the slider tracks scale to the specified scale
	void SetSliderTrackScale(const vec2& scale);

	//Sets the color of the slider track to the specified color
	void SetSliderTrackColor(const vec4& color);

	//Sets the color of the slider handle to the specified color
	void SetSliderHandleColor(const vec4& color);

	//Sets the slider percentage to the specified percentage
	void SetSliderPercentage(const float percentage);

	//Update the slider
	void Update();

private:
	//The GUISliders slider track GUI Object
	GUIObject* mp_sliderTrack;

	//The GUISliders slider handle
	GUIObject* mp_sliderHandle;

	//The position of the slider
	vec2 m_position;

	//The slider percentage
	float m_percentage;

	//The current state of the left mouse button
	bool m_currentLeftMouseButtonState;

	//The previous state of the left mouse button
	bool m_previousLeftMouseButtonState;

	//Whether the slider should follow the mouses x position
	bool m_followMouse;
};