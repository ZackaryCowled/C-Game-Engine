//Pragma comments
#pragma once

//External includes
#include <memory>
#include <string>
#include <vector>

//Using directives
using std::shared_ptr;
using std::string;
using std::vector;
using std::weak_ptr;

//Forward declarations
class Component;

//Object used for grouping various objects and components together in 3D space
class GameObject
{
public:
	//Creates and initializes a GameObject instance (Default constructor)
	GameObject();

	//Creates and initializes a GameObject instance with the specified name
	//name - The name to give the GameObject instance
	GameObject(const string& name);

	//Creates and initializes a GameObject instance with the specified name and tag
	//name - The name to give the GameObject instance
	//tag - The tag to give the GameObject instance
	GameObject(const string& name, const string& tag);

	//Adds the specified GameObject to the GameObjects child container
	//p_childGameObject - The GameObject to child to this GameObject
	void AddChild(GameObject* p_childGameObject);

	//Destroys the GameObject instance
	void Destroy();

	//Returns the GameObjects name
	const string& GetName();
	
	//Returns the GameObjects tag
	const string& GetTag();

	//Returns a pointer to the GameObjects parent
	GameObject* GetParent();

	//Sets the GameObjects name to the specified name
	//name - The name to give the GameObject instance
	void SetName(const string& name);

	//Sets the GameObjects tag to the specified tag
	//tag - The tag to give the GameObject instance
	void SetTag(const string& tag);

	//Sets the GameObjects parent to the specified GameObject
	//p_parentGameObject - The GameObject to use as this GameObjects parent
	void SetParent(GameObject* p_parentGameObject);

	//Updates the GameObjects components
	void Update();

	//Updates the GameObjects at the end of the frame
	void LateUpdate();

	//Removes the specified GameObject from the GameObjects child container
	//p_childGameObject - The GameObject to remove from the child container
	void RemoveChild(GameObject* p_childGameObject);

public:
	//Adds a component of the component type to the GameObject instance
	template<class ComponentType> ComponentType* AddComponent()
	{
		//Add new component to the GameObjects component container
		m_componentContainer.push_back(shared_ptr<ComponentType>(new ComponentType));
		m_componentContainer.back()->SetParent(this);

		//If the new component is a script
		if (m_componentContainer.back()->GetType() == COMPONENT_TYPE_SCRIPT)
		{
			//Get address of the script
			Script* p_script = (Script*)m_componentContainer.back().get();

			//Call the scripts awake and start functions
			p_script->Awake();
			p_script->Start();
		}

		//Return a pointer to the new component
		return (ComponentType*)m_componentContainer.back().get();
	}

	//Returns a pointer to the first component attached to the GameObject that matches the component type
	//If there are no components attached to the GameObject that match the component type a null pointer is returned
	template<class ComponentType> ComponentType* GetComponent()
	{
		//Create temporary component of the specified component type
		ComponentType temporaryComponent = ComponentType();

		//Cache the specified component type
		const int specifiedComponentType = temporaryComponent.GetType();

		//For each component in the GameObjects component container
		for (unsigned int componentIndex = 0; componentIndex < m_componentContainer.size(); ++componentIndex)
		{
			//If the component at the component index in the component container is the same component type as the one specified
			if (m_componentContainer[componentIndex]->GetType() == specifiedComponentType)
			{
				//Return a pointer to the component
				return (ComponentType*)m_componentContainer[componentIndex].get();
			}
		}

		//There are no components of the component type attached to the GameObject
		return nullptr;
	}

private:
	//The GameObjects name
	string m_name;

	//The GameObjects tag
	string m_tag;

	//Pointer to the GameObjects parent
	GameObject* mp_parent;

	//Container for stroing the GameObjects components
	vector<shared_ptr<Component>> m_componentContainer;

	//Container for storing the GameObjects children
	vector<GameObject*> m_childContainer;
};