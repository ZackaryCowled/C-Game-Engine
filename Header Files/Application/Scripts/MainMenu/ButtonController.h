//Pragma comments
#pragma once

//Internal incldues
#include "Application.h"

//Button Controller Script
class ButtonController : public Script
{
public:
	//Called on initialization
	virtual void Awake();

	//Returns the button the button controller is controlling
	GUIObject* GetButton();

	//Returns the scale of the button
	const vec2 GetScale() const;

	//Returns the position of the button
	const vec2 GetPosition() const;

	//Returns the color of the button
	const vec4 GetColor() const;

	//Returns a flag representing whether the mouse is hovering over the button
	const bool IsMouseHovering() const;

	//Sets the buttons texture to the specified texture
	//textureFilepath - The location, name and file extension of the texture file
	void SetTexture(const string& textureFilepath);

	//Sets the scale of the button to the specified scale
	void SetScale(const vec2& scale);

	//Sets the position of the button to the specified position
	void SetPosition(const vec2& position);

	//Sets the color of the button to the specified color
	void SetColor(const vec4& color);

private:
	//The scripts parent
	GameObject* parent;

	//Button object
	GUIObject* button;
};