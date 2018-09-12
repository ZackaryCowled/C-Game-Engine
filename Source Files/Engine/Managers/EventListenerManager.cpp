//Internal includes
#include "Application.h"

//Initialize static event listener manager attributes
vector<EventListener*> EventListenerManager::m_eventListenerContainer = vector<EventListener*>();

//Updates all registered event listeners
void EventListenerManager::UpdateAllEventListeners()
{
	//For each event listener
	for (unsigned int enterFrameEventListenerIndex = 0; enterFrameEventListenerIndex < m_eventListenerContainer.size(); ++enterFrameEventListenerIndex)
	{
		//Update enter frame event listener
		m_eventListenerContainer[enterFrameEventListenerIndex]->Update();
	}
}

//Registers the specified EventListener
void EventListenerManager::RegisterEventListener(EventListener* p_eventListener)
{
	//Register event listener
	m_eventListenerContainer.push_back(p_eventListener);
}

//Unregisters the specified EventListener
void EventListenerManager::UnregisterEventListener(EventListener* p_eventListener)
{
	//For each event listener in the applications event listener container
	for (unsigned int eventListenerIndex = 0; eventListenerIndex < m_eventListenerContainer.size(); ++eventListenerIndex)
	{
		//If the event listener is the specified event listener
		if (m_eventListenerContainer[eventListenerIndex] == p_eventListener)
		{
			//Erase the event listener from the applications event listener container
			m_eventListenerContainer.erase(m_eventListenerContainer.begin() + eventListenerIndex);

			//Return from the function
			return;
		}
	}
}