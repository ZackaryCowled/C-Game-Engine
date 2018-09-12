//Internal includes
#include "ApplicationHeaders.h"

//Called on initialization
void ButtonController::Awake()
{
	//Initialize parent
	parent = GetParent();

	//Initialize button
	button = parent->AddComponent<GUIObject>();
}

//Returns the button the button controller is controlling
GUIObject* ButtonController::GetButton()
{
	//Return the button the button controller is controlling
	return button;
}

//Returns the scale of the button
const vec2 ButtonController::GetScale() const
{
	//Return the scale of the button
	return button->GetScale();
}

//Returns the position of the button
const vec2 ButtonController::GetPosition() const
{
	//Return the position of the button
	return button->GetPosition();
}

//Returns the color of the button
const vec4 ButtonController::GetColor() const
{
	//Return the color of the button
	return button->GetColor();
}

//Returns a flag representing whether the mouse is hovering over the button
const bool ButtonController::IsMouseHovering() const
{
	//If the mouse is hovering over the button
	if (Input::GetMousePosition().x >= button->GetPosition().x && Input::GetMousePosition().x <= button->GetPosition().x + button->GetScale().x &&
		Input::GetMousePosition().y >= button->GetPosition().y && Input::GetMousePosition().y <= button->GetPosition().y + button->GetScale().y)
	{
		//The mouse is hovering over the button
		return true;
	}

	//The mouse is not hovering over the button
	return false;
}

//Sets the buttons texture to the specified texture
//textureFilepath - The location, name and file extension of the texture file
void ButtonController::SetTexture(const string& textureFilepath)
{
	//Set the buttons texture to the specified texture
	button->SetTextureMap(textureFilepath);
}

//Sets the scale of the button to the specified scale
void ButtonController::SetScale(const vec2& scale)
{
	//Set the buttons scale to the specified scale
	button->SetScale(scale);
}

//Sets the position of the button to the specified position
void ButtonController::SetPosition(const vec2& position)
{
	//Set the buttons position to the specified position
	button->SetPosition(position);
}

//Sets the color of the button to the specified color
void ButtonController::SetColor(const vec4& color)
{
	//Set the color of the button to the specified color
	button->SetColor(color);
}