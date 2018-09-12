//Internal includes
#include "GameObject.h"
#include "Application.h"

//Creates and initializes a GameObject instance (Default constructor)
GameObject::GameObject()
{
	//Initialize GameObject
	GameObjectManager::RegisterGameObject(this);
	SetName("");
	SetTag("Untagged");
	m_componentContainer = vector<shared_ptr<Component>>();
	m_childContainer = vector<GameObject*>();
}

//Creates and initializes a GameObject instance with the specified name
//name - The name to give the GameObject instance
GameObject::GameObject(const string& name)
{
	//Initialize GameObject
	GameObjectManager::RegisterGameObject(this);
	SetName(name);
	SetTag("Untagged");
	mp_parent = nullptr;
	m_componentContainer = vector<shared_ptr<Component>>();
	m_childContainer = vector<GameObject*>();
}

//Creates and initializes a GameObject instance with the specified name and tag
//name - The name to give the GameObject instance
//tag - The tag to give the GameObject instance
GameObject::GameObject(const string& name, const string& tag)
{
	//Initialize GameObject
	GameObjectManager::RegisterGameObject(this);
	SetName(name);
	SetTag(tag);
	m_componentContainer = vector<shared_ptr<Component>>();
	m_childContainer = vector<GameObject*>();
}

//Adds the specified GameObject to the GameObjects child container
//p_childGameObject - The GameObject to child to this GameObject
void GameObject::AddChild(GameObject* p_childGameObject)
{
	//Add the specified GameObject as a child
	m_childContainer.push_back(p_childGameObject);

	//Set the childs parent to this GameObject
	p_childGameObject->mp_parent = this;

	//Get address of the child GameObjects transform and the parent GameObjects transform
	Transform* p_childTransform = p_childGameObject->GetComponent<Transform>();
	Transform* p_parentTransform = GetComponent<Transform>();

	//If both the childs transform and parents transform are valid
	if (p_childTransform != nullptr && p_parentTransform != nullptr)
	{
		//Calculate distance between child transform and parent transform on the x, y and z axis
		vec3 childPositionOffset = vec3(distance(p_childTransform->GetPosition().x, p_parentTransform->GetPosition().x),
										distance(p_childTransform->GetPosition().y, p_parentTransform->GetPosition().y),
										distance(p_childTransform->GetPosition().z, p_parentTransform->GetPosition().z));

		//Setup childs transform position relative to the parent transforms position
		p_childTransform->SetPosition(p_childTransform->GetPosition().x > p_parentTransform->GetPosition().x ? childPositionOffset.x : -childPositionOffset.x,
									  p_childTransform->GetPosition().y > p_parentTransform->GetPosition().y ? childPositionOffset.y : -childPositionOffset.y,
									  p_childTransform->GetPosition().z > p_parentTransform->GetPosition().z ? childPositionOffset.z : -childPositionOffset.z);
		
		//Setup childs transform rotation relative to the parent transform rotation
		p_childTransform->SetRotation(p_parentTransform->GetRotation() * p_childTransform->GetRotation());

		//Setup childs transform scale relative to the parent transform scale
		p_childTransform->SetScale(p_parentTransform->GetScale() * p_childTransform->GetScale());
	}
}

//Destroys the GameObject instance
void GameObject::Destroy()
{
	//While there are GameObjects in the GameObjects child container
	while(m_childContainer.size() > 0)
	{
		//Destroy the child GameObject
		m_childContainer[0]->Destroy();

		//Remove child from the GameObjects child container
		m_childContainer.erase(m_childContainer.begin());
	}

	//Destroy the GameObject
	GameObjectManager::UnregisterGameObject(this);
}

//Returns the GameObjects name
const string& GameObject::GetName()
{
	//Return the GameObjects name
	return m_name;
}

//Returns the GameObjects tag
const string& GameObject::GetTag()
{
	//Return the GameObjects tag
	return m_tag;
}

//Returns a pointer to the GameObjects parent
GameObject* GameObject::GetParent()
{
	//Return the GameObjects parent
	return mp_parent;
}

//Sets the GameObjects name to the specified name
//name - The name to give the GameObject instance
void GameObject::SetName(const string& name)
{
	//Set the GameObjects name to the specified name
	m_name = name;
}

//Sets the GameObjects tag to the specified tag
//tag - The tag to give the GameObject instance
void GameObject::SetTag(const string& tag)
{
	//Set the GameObjects tag to the specified tag
	m_tag = tag;
}

//Sets the GameObjects parent to the specified GameObject
//p_parentGameObject - The GameObject to use as this GameObjects parent
void GameObject::SetParent(GameObject* p_parentGameObject)
{
	//If the GameObject has a parent
	if (mp_parent != nullptr)
	{
		//Remove the GameObject from the parent
		mp_parent->RemoveChild(this);
	}

	//Set the GameObjects parent to the specified GameObject
	p_parentGameObject->AddChild(this);
}

//Updates the GameObject
void GameObject::Update()
{
	//For each component in the GameObjects component container
	for (unsigned int componentIndex = 0; componentIndex < m_componentContainer.size(); componentIndex++)
	{
		//Depending on the components type
		switch (m_componentContainer[componentIndex]->GetType())
		{
			//If the component is a script
			case COMPONENT_TYPE_SCRIPT:
			{
				//Get address of the script
				Script* script = (Script*)m_componentContainer[componentIndex].get();

				//Update the script
				script->Update();

				//Break out of the switch statement
				break;
			}
		}
	}
}

//Updates the GameObjects at the end of the frame
void GameObject::LateUpdate()
{
	//For each component in the GameObjects component container
	for (unsigned int componentIndex = 0; componentIndex < m_componentContainer.size(); componentIndex++)
	{
		//Depending on the components type
		switch (m_componentContainer[componentIndex]->GetType())
		{
			//If the component is a script
			case COMPONENT_TYPE_SCRIPT:
			{
				//Get address of the script
				Script* script = (Script*)m_componentContainer[componentIndex].get();

				//LateUpdate the script
				script->LateUpdate();

				//Break out of the switch statement
				break;
			}
		}
	}
}

//Removes the specified GameObject from the GameObjects child container
//p_childGameObject - The GameObject to remove from the child container
void GameObject::RemoveChild(GameObject* p_childGameObject)
{
	//For each child in the GameObjects child container
	for (unsigned int childIndex = 0; childIndex < m_childContainer.size(); childIndex++)
	{
		//If the GameObject is the child
		if (m_childContainer[childIndex] == p_childGameObject)
		{
			//Remove the child from the child container
			m_childContainer.erase(m_childContainer.begin() + childIndex);

			//Set the child GameObject parent to a null pointer
			p_childGameObject->mp_parent = nullptr;

			//Return from the function
			return;
		}
	}
}