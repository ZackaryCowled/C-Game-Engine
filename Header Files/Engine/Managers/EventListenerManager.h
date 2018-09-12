//Pragma comments
#pragma once

//External includes
#include <vector>

//Using directives
using std::vector;

//Forward declarations
class EventListener;

//Singleton object used for managing the applications EventListeners
class EventListenerManager
{
public:
	//Updates all registered event listeners
	static void UpdateAllEventListeners();

	//Registers the specified EventListener
	static void RegisterEventListener(EventListener* p_eventListener);

	//Unregisters the specified EventListener
	static void UnregisterEventListener(EventListener* p_eventListener);

private:
	//Container for storing the applications event listeners
	static vector<EventListener*> m_eventListenerContainer;
};