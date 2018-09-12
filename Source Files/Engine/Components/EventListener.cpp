//Internal includes
#include "Application.h"

//External includes
#include <Windows.h>

//Creates and initializes a EventListener instance (Default constructor)
EventListener::EventListener()
{
	//Initialize EventListener
	m_inputDevice = INPUT_DEVICE_NONE;
	m_eventType = EVENT_TYPE_NONE;
	m_eventTrigger = EVENT_TRIGGER_NONE;
	m_callbackFunction = DefaultCallbackFunction;
	m_currentState = false;
	m_previousState = false;
	SetType(COMPONENT_TYPE_EVENT_LISTENER);
	EventListenerManager::RegisterEventListener(this);
}

//Releases the EventListeners resources
EventListener::~EventListener()
{
	//Destroy the event listener
	Destroy();
}

//Destroys the event listener
void EventListener::Destroy()
{
	//Unregister the event listener
	EventListenerManager::UnregisterEventListener(this);
}

//Executes the event listeners callback function
void EventListener::ExecuteCallbackFunction()
{
	//Call the event listeners callback function
	m_callbackFunction();
}

//Returns the input device the event listener is listening to
const unsigned int EventListener::GetInputDevice()
{
	//Return the event listeners input device
	return m_inputDevice;
}

//Returns the event type the event listener is listening for
const unsigned int EventListener::GetEventType()
{
	//Return the event listeners event type
	return m_eventType;
}

//Returns the event trigger the event listener is listening for
const unsigned int EventListener::GetEventTrigger()
{
	//Return the event listeners event trigger
	return m_eventTrigger;
}

//Sets the device the event listener is to listen to
void EventListener::SetInputDevice(const unsigned int inputDevice)
{
	//Set the event listeners input device to the specified input device
	m_inputDevice = inputDevice;
}

//Sets the event type the event listener is to listen for
void EventListener::SetEventType(const unsigned int eventType)
{
	//Set the event listeners event type to the specified event type
	m_eventType = eventType;
}

//Sets the event trigger that causes the event listener to execute its callback function
void EventListener::SetEventTrigger(const unsigned int eventTrigger)
{
	//Set the event listeners event trigger to the specified event trigger
	m_eventTrigger = eventTrigger;
}

//Sets the callback function the event listener is to execute when it trigger occurs
void EventListener::SetCallbackFunction(void(*callbackFunction)(void))
{
	//Set the event listeners callback function to the specified callback function
	m_callbackFunction = callbackFunction;
}

//Updates the event listener
void EventListener::Update()
{
	//Synchronize previous event listener state
	m_previousState = m_currentState;

	//Depending on the input device the event listener is listening to
	switch (m_inputDevice)
	{
		//If the event listener is listening to the keyboard
		case INPUT_DEVICE_KEYBOARD: HandleKeyboardEvent();
			break;

		//If the event listener is listening to the mouse
		case INPUT_DEVICE_MOUSE: HandleMouseEvent();
			break;

		//If the event listener is listening to a Gamepad
		case INPUT_DEVICE_GAMEPAD: HandleGamepadEvent();
			break;
	}
}

//Handles the currently occuring keyboard event
void EventListener::HandleKeyboardEvent()
{
	//Depending on the event listeners event type
	switch (m_eventType)
	{
		//If the event listener is listening for a key down event
		case EVENT_TYPE_DOWN: HandleKeyDownEvent();
			break;

		//If the event listener is listening for a key up event
		case EVENT_TYPE_UP: HandleKeyUpEvent();
			break;

		//If the event listener is listening for a key down repeat event
		case EVENT_TYPE_DOWN_REPEAT: HandleKeyDownRepeatEvent();
			break;

		//If the event listener is listening for a key up repeat event
		case EVENT_TYPE_UP_REPEAT: HandleKeyUpRepeatEvent();
			break;

		//If the event listener is listening for a key move event
		case EVENT_TYPE_MOVE: HandleKeyMoveEvent();
			break;
	}
}

//Handles the currently occuring mouse event
void EventListener::HandleMouseEvent()
{
	//Depending on the event listeners event type
	switch (m_eventType)
	{
		//If the event listener is listening for a mouse down event
		case EVENT_TYPE_DOWN: HandleMouseDownEvent();
			break;

		//If the event listener is listening for a mouse up event
		case EVENT_TYPE_UP: HandleMouseUpEvent();
			break;

		//If the event listener is listening for a mouse down repeat event
		case EVENT_TYPE_DOWN_REPEAT: HandleMouseDownRepeatEvent();
			break;

		//If the event listener is listening for a mouse up repeat event
		case EVENT_TYPE_UP_REPEAT: HandleMouseUpRepeatEvent();
			break;

		//If the event listener is listening for a mouse move event
		case EVENT_TYPE_MOVE: HandleMouseMoveEvent();
			break;
	}
}

//Handles the currently occuring gamepad event
void EventListener::HandleGamepadEvent()
{
	//Depending on the event listeners event type
	switch (m_eventType)
	{
		//If the event listener is listening for a gamepad button down event
		case EVENT_TYPE_DOWN: HandleGamepadButtonDownEvent();
			break;

		//If the event listener is listening for a gamepad button up event
		case EVENT_TYPE_UP: HandleGamepadButtonUpEvent();
			break;

		//If the event listener is listening for a gamepad button down repeat event
		case EVENT_TYPE_DOWN_REPEAT: HandleGamepadButtonDownRepeatEvent();
			break;

		//If the event listener is listening for a gamepad button up repeat event
		case EVENT_TYPE_UP_REPEAT: HandleGamepadButtonUpRepeatEvent();
			break;

		//If the event listener is listening for a gamepad button move event
		case EVENT_TYPE_MOVE: HandleGamepadButtonMoveEvent();
			break;
	}
}

//Handles the currently occuring key down event
void EventListener::HandleKeyDownEvent()
{
	//If the event trigger is down
	if (GetAsyncKeyState(m_eventTrigger))
	{
		//Set the current state to true
		m_currentState = true;
	}
	//Otherwise
	else
	{
		//Set the current state to false
		m_currentState = false;
	}

	//If the event listeners previous state is equal to false and the current state true
	if (!m_previousState && m_currentState)
	{
		//Execute the event listeners callback function
		ExecuteCallbackFunction();
	}
}

//Handles the currently occuring key up event
void EventListener::HandleKeyUpEvent()
{
	//If the event trigger is down
	if (GetAsyncKeyState(m_eventTrigger))
	{
		//Set the current state to true
		m_currentState = true;
	}
	//Otherwise
	else
	{
		//Set the current state to false
		m_currentState = false;
	}

	//If the event listeners previous state is equal to true and the current state false
	if (m_previousState && !m_currentState)
	{
		//Execute the event listeners callback function
		ExecuteCallbackFunction();
	}
}

//Handles the currently occuring key down repeat event
void EventListener::HandleKeyDownRepeatEvent()
{
	//If the event trigger is down
	if (GetAsyncKeyState(m_eventTrigger))
	{
		//Set the current state to true
		m_currentState = true;
	}
	//Otherwise
	else
	{
		//Set the current state to false
		m_currentState = false;
	}

	//If the event listeners current state is true
	if (m_currentState)
	{
		//Execute the event listeners callback function
		ExecuteCallbackFunction();
	}
}

//Handles the currently occuring key up repeat event
void EventListener::HandleKeyUpRepeatEvent()
{
	//If the event trigger is down
	if (GetAsyncKeyState(m_eventTrigger))
	{
		//Set the current state to true
		m_currentState = true;
	}
	//Otherwise
	else
	{
		//Set the current state to false
		m_currentState = false;
	}

	//If the event listeners current state is false
	if (!m_currentState)
	{
		//Execute the event listeners callback function
		ExecuteCallbackFunction();
	}
}

//Handle the currently occuring key move event
void EventListener::HandleKeyMoveEvent()
{
	//If the event trigger is down
	if (GetAsyncKeyState(m_eventTrigger))
	{
		//Set the current state to true
		m_currentState = true;
	}
	//Otherwise
	else
	{
		//Set the current state to false
		m_currentState = false;
	}

	//If the event listeners current state is not the same as its previous state
	if (m_currentState != m_previousState)
	{
		//Execute the event listeners callback function
		ExecuteCallbackFunction();
	}
}

//Handles the currently occuring mouse down event
void EventListener::HandleMouseDownEvent()
{
	//If the event trigger is down
	if (GetAsyncKeyState(m_eventTrigger))
	{
		//Set the current state to true
		m_currentState = true;
	}
	//Otherwise
	else
	{
		//Set the current state to false
		m_currentState = false;
	}

	//If the event listeners previous state is equal to false and the current state true
	if (!m_previousState && m_currentState)
	{
		//Execute the event listeners callback function
		ExecuteCallbackFunction();
	}
}

//Handles the currently occuring mouse up event
void EventListener::HandleMouseUpEvent()
{
	//If the event trigger is down
	if (GetAsyncKeyState(m_eventTrigger))
	{
		//Set the current state to true
		m_currentState = true;
	}
	//Otherwise
	else
	{
		//Set the current state to false
		m_currentState = false;
	}

	//If the event listeners previous state is equal to true and the current state false
	if (m_previousState && !m_currentState)
	{
		//Execute the event listeners callback function
		ExecuteCallbackFunction();
	}
}

//Handles the currently occuring mouse down repeat event
void EventListener::HandleMouseDownRepeatEvent()
{
	//If the event trigger is down
	if (GetAsyncKeyState(m_eventTrigger))
	{
		//Set the current state to true
		m_currentState = true;
	}
	//Otherwise
	else
	{
		//Set the current state to false
		m_currentState = false;
	}

	//If the event listeners current state is true
	if (m_currentState)
	{
		//Execute the event listeners callback function
		ExecuteCallbackFunction();
	}
}

//Handles the currently occuring mouse up repeat event
void EventListener::HandleMouseUpRepeatEvent()
{
	//If the event trigger is down
	if (GetAsyncKeyState(m_eventTrigger))
	{
		//Set the current state to true
		m_currentState = true;
	}
	//Otherwise
	else
	{
		//Set the current state to false
		m_currentState = false;
	}

	//If the event listeners current state is false
	if (!m_currentState)
	{
		//Execute the event listeners callback function
		ExecuteCallbackFunction();
	}
}

//Handles the currently occuring mouse move event
void EventListener::HandleMouseMoveEvent()
{
	//If the event trigger is down
	if (GetAsyncKeyState(m_eventTrigger))
	{
		//Set the current state to true
		m_currentState = true;
	}
	//Otherwise
	else
	{
		//Set the current state to false
		m_currentState = false;
	}

	//If the event listeners previous state is equal to false and the current state true
	if (!m_previousState && m_currentState)
	{
		//Execute the event listeners callback function
		ExecuteCallbackFunction();
	}
}

//Handles the currently occuring gamepad button down event
void EventListener::HandleGamepadButtonDownEvent()
{

}

//Handles the currently occuring gamepad button up event
void EventListener::HandleGamepadButtonUpEvent()
{

}

//Handles the currently occuring gamepad button down repeat event
void EventListener::HandleGamepadButtonDownRepeatEvent()
{

}

//Handles the currently occuring gamepad button up repeat event
void EventListener::HandleGamepadButtonUpRepeatEvent()
{

}

//Handles the currently occuring gamepad button move event
void EventListener::HandleGamepadButtonMoveEvent()
{

}