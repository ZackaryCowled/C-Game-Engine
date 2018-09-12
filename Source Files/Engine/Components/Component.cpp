//Internal includes
#include "Component.h"
#include "Application.h"

//Creates and initializes a Component instance (Default constructor)
Component::Component()
{
	//Initialize Component
	m_type = COMPONENT_TYPE_DEFAULT;
	mp_parent = nullptr;
}

//Returns the components type
const int Component::GetType() const
{
	//Return the components type
	return m_type;
}

//Returns a pointer to the components parent
GameObject* Component::GetParent()
{
	//Return the components parent
	return mp_parent;
}

//Sets the components parent to the specified GameObject
void Component::SetParent(GameObject* p_parent)
{
	//Set the components parent
	mp_parent = p_parent;
}

//Sets the components type
void Component::SetType(const int type)
{
	//Set the components type
	m_type = type;
}