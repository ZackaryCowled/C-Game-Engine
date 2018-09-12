//Pragma comments
#pragma once

//Forward declarations
class GameObject;

//Base object that provides additional functionality for GameObjects
class Component
{
public:
	//Creates and initializes a Component instance (Default constructor)
	Component();

	//Returns the components type
	const int GetType() const;

	//Returns a pointer to the components parent
	GameObject* GetParent();

	//Sets the components parent to the specified GameObject
	void SetParent(GameObject* p_parent);

protected:
	//Sets the components type
	void SetType(const int type);

private:
	//The components type
	int m_type;

	//The components parent
	GameObject* mp_parent;
};