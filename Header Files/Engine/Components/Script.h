//Pragma comments
#pragma once

//Internal includes
#include "Component.h"

//Polymorphic object with a set of callback functions that can be overrided
class Script : public Component
{
public:
	//Creates and initializes a Script instance (Default constructor)
	Script();

	//Called on script creation
	virtual void Awake();

	//Called on script initialization
	virtual void Start();

	//Called once per frame
	virtual void Update();

	//Called at the end of each frame
	virtual void LateUpdate();

	//Adds a component of the component type to the GameObject with this script attached
	template<class ComponentType> ComponentType* AddComponent()
	{
		//Add a component of the component type to the GameObject with this script attached
		return GetParent()->AddComponent<ComponentType>();
	}

	//Returns the scripts first component of the specified component type
	//If no component of the specified component type exists the function returns a null pointer
	template<class ComponentType> ComponentType* GetComponent()
	{
		//Return the first component of the specified component type of a null pointer
		return GetParent()->GetComponent<ComponentType>();
	}
};