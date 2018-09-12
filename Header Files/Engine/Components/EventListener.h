//Pragma comments
#pragma once

//Internal includes
#include "Component.h"

//Precompiler definitions
#define INPUT_DEVICE_NONE 0
#define INPUT_DEVICE_KEYBOARD 1
#define INPUT_DEVICE_MOUSE 2
#define INPUT_DEVICE_GAMEPAD 3
#define EVENT_TYPE_NONE 0
#define EVENT_TYPE_DOWN 1
#define EVENT_TYPE_UP 2
#define EVENT_TYPE_DOWN_REPEAT 3
#define EVENT_TYPE_UP_REPEAT 4
#define EVENT_TYPE_MOVE 5
#define EVENT_TRIGGER_NONE 0xFF
#define EVENT_TRIGGER_MOUSE_LEFT 0x01
#define EVENT_TRIGGER_MOUSE_RIGHT 0x02
#define EVENT_TRIGGER_MOUSE_MIDDLE 0x04
#define EVENT_TRIGGER_KEY_BACKSPACE 0x08
#define EVENT_TRIGGER_KEY_TAB 0x09
#define EVENT_TRIGGER_KEY_RETURN 0x0D
#define EVENT_TRIGGER_KEY_SHIFT 0x10
#define EVENT_TRIGGER_KEY_CONTROL 0x11
#define EVENT_TRIGGER_KEY_ALT 0x12
#define EVENT_TRIGGER_KEY_PAUSE 0x13
#define EVENT_TRIGGER_KEY_CAPSLOCK 0x14
#define EVENT_TRIGGER_KEY_ESCAPE 0x1B
#define EVENT_TRIGGER_KEY_SPACE 0x20
#define EVENT_TRIGGER_KEY_PAGEUP 0x21
#define EVENT_TRIGGER_KEY_PAGEDOWN 0x22
#define EVENT_TRIGGER_KEY_END 0x23
#define EVENT_TRIGGER_KEY_HOME 0x24
#define EVENT_TRIGGER_KEY_LEFT 0x25
#define EVENT_TRIGGER_KEY_UP 0x26
#define EVENT_TRIGGER_KEY_RIGHT 0x27
#define EVENT_TRIGGER_KEY_DOWN 0x28
#define EVENT_TRIGGER_KEY_PRINTSCREEN 0x2C
#define EVENT_TRIGGER_KEY_INSERT 0x2D
#define EVENT_TRIGGER_KEY_DELETE 0x2E
#define EVENT_TRIGGER_KEY_0 0x30
#define EVENT_TRIGGER_KEY_1 0x31
#define EVENT_TRIGGER_KEY_2 0x32
#define EVENT_TRIGGER_KEY_3 0x33
#define EVENT_TRIGGER_KEY_4 0x34
#define EVENT_TRIGGER_KEY_5 0x35
#define EVENT_TRIGGER_KEY_6 0x36
#define EVENT_TRIGGER_KEY_7 0x37
#define EVENT_TRIGGER_KEY_8 0x38
#define EVENT_TRIGGER_KEY_9 0x39
#define EVENT_TRIGGER_KEY_A 0x41
#define EVENT_TRIGGER_KEY_B 0x42
#define EVENT_TRIGGER_KEY_C 0x43
#define EVENT_TRIGGER_KEY_D 0x44
#define EVENT_TRIGGER_KEY_E 0x45
#define EVENT_TRIGGER_KEY_F 0x46
#define EVENT_TRIGGER_KEY_G 0x47
#define EVENT_TRIGGER_KEY_H 0x48
#define EVENT_TRIGGER_KEY_I 0x49
#define EVENT_TRIGGER_KEY_J 0x4A
#define EVENT_TRIGGER_KEY_K 0x4B
#define EVENT_TRIGGER_KEY_L 0x4C
#define EVENT_TRIGGER_KEY_M 0x4D
#define EVENT_TRIGGER_KEY_N 0x4E
#define EVENT_TRIGGER_KEY_O 0x4F
#define EVENT_TRIGGER_KEY_P 0x50
#define EVENT_TRIGGER_KEY_Q 0x51
#define EVENT_TRIGGER_KEY_R 0x52
#define EVENT_TRIGGER_KEY_S 0x53
#define EVENT_TRIGGER_KEY_T 0x54
#define EVENT_TRIGGER_KEY_U 0x55
#define EVENT_TRIGGER_KEY_V 0x56
#define EVENT_TRIGGER_KEY_W 0x57
#define EVENT_TRIGGER_KEY_X 0x58
#define EVENT_TRIGGER_KEY_Y 0x59
#define EVENT_TRIGGER_KEY_Z 0x5A
#define EVENT_TRIGGER_KEY_SUPER_LEFT 0x5B
#define EVENT_TRIGGER_KEY_SUPER_RIGHT 0x5C
#define EVENT_TRIGGER_KEY_SLEEP 0x5F
#define EVENT_TRIGGER_KEY_NUMPAD_0 0x60
#define EVENT_TRIGGER_KEY_NUMPAD_1 0x61
#define EVENT_TRIGGER_KEY_NUMPAD_2 0x62
#define EVENT_TRIGGER_KEY_NUMPAD_3 0x63
#define EVENT_TRIGGER_KEY_NUMPAD_4 0x64
#define EVENT_TRIGGER_KEY_NUMPAD_5 0x65
#define EVENT_TRIGGER_KEY_NUMPAD_6 0x66
#define EVENT_TRIGGER_KEY_NUMPAD_7 0x67
#define EVENT_TRIGGER_KEY_NUMPAD_8 0x68
#define EVENT_TRIGGER_KEY_NUMPAD_9 0x69
#define EVENT_TRIGGER_KEY_MULTIPLY 0x6A
#define EVENT_TRIGGER_KEY_ADD 0x6B
#define EVENT_TRIGGER_KEY_SEPARATOR 0x6C
#define EVENT_TRIGGER_KEY_SUBTRACT 0x6D
#define EVENT_TRIGGER_KEY_DECIMAL 0x6E
#define EVENT_TRIGGER_KEY_DIVIDE 0x6F
#define EVENT_TRIGGER_KEY_F1 0x70
#define EVENT_TRIGGER_KEY_F2 0x71
#define EVENT_TRIGGER_KEY_F3 0x72
#define EVENT_TRIGGER_KEY_F4 0x73
#define EVENT_TRIGGER_KEY_F5 0x74
#define EVENT_TRIGGER_KEY_F6 0x75
#define EVENT_TRIGGER_KEY_F7 0x76
#define EVENT_TRIGGER_KEY_F8 0x77
#define EVENT_TRIGGER_KEY_F9 0x78
#define EVENT_TRIGGER_KEY_F10 0x79
#define EVENT_TRIGGER_KEY_F11 0x7A
#define EVENT_TRIGGER_KEY_F12 0x7B
#define EVENT_TRIGGER_KEY_F13 0x7C
#define EVENT_TRIGGER_KEY_F14 0x7D
#define EVENT_TRIGGER_KEY_F15 0x7E
#define EVENT_TRIGGER_KEY_F16 0x7F
#define EVENT_TRIGGER_KEY_F17 0x80
#define EVENT_TRIGGER_KEY_F18 0x81
#define EVENT_TRIGGER_KEY_F19 0x82
#define EVENT_TRIGGER_KEY_F20 0x83
#define EVENT_TRIGGER_KEY_F21 0x84
#define EVENT_TRIGGER_KEY_F22 0x85
#define EVENT_TRIGGER_KEY_F23 0x86
#define EVENT_TRIGGER_KEY_F24 0x87
#define EVENT_TRIGGER_KEY_NUMLOCK 0x90
#define EVENT_TRIGGER_KEY_SCROLL 0x91
#define EVENT_TRIGGER_KEY_SHIFT_LEFT 0xA0
#define EVENT_TRIGGER_KEY_SHIFT_RIGHT 0xA1
#define EVENT_TRIGGER_KEY_CONTROL_LEFT 0xA2
#define EVENT_TRIGGER_KEY_CONTROL_RIGHT 0xA3
#define EVENT_TRIGGER_KEY_ALT_LEFT 0xA4
#define EVENT_TRIGGER_KEY_ALT_RIGHT 0xA5
#define EVENT_TRIGGER_KEY_COLON 0xBA
#define EVENT_TRIGGER_KEY_PLUS 0xBA
#define EVENT_TRIGGER_KEY_COMMA 0xBC
#define EVENT_TRIGGER_KEY_MINUS 0xBD
#define EVENT_TRIGGER_KEY_PERIOD 0xBE
#define EVENT_TRIGGER_KEY_FORWARDSLASH 0xBF
#define EVENT_TRIGGER_KEY_TILDA 0xC0
#define EVENT_TRIGGER_KEY_BRACKET_LEFT 0xDB
#define EVENT_TRIGGER_KEY_BACKSLASH 0xDC
#define EVENT_TRIGGER_KEY_BRACKET_RIGHT 0xDD
#define EVENT_TRIGGER_KEY_QUOTE 0xDE

//Default event listener callback function
static void DefaultCallbackFunction() {}

//Object used for listening for an event and doing something when the event occurs
class EventListener : public Component
{
public:
	//Creates and initializes a EventListener instance (Default constructor)
	EventListener();

	//Releases the EventListeners resources
	~EventListener();

	//Destroys the event listener
	void Destroy();

	//Executes the event listeners callback function
	void ExecuteCallbackFunction();

	//Returns the input device the event listener is listening to
	const unsigned int GetInputDevice();

	//Returns the event type the event listener is listening for
	const unsigned int GetEventType();

	//Returns the event trigger the event listener is listening for
	const unsigned int GetEventTrigger();

	//Sets the device the event listener is to listen to
	void SetInputDevice(const unsigned int inputDevice);

	//Sets the event type the event listener is to listen for
	void SetEventType(const unsigned int eventType);

	//Sets the event trigger that causes the event listener to execute its callback function
	void SetEventTrigger(const unsigned int eventTrigger);

	//Sets the callback function the event listener is to execute when it trigger occurs
	void SetCallbackFunction(void(*callbackFunction)(void));

	//Updates the event listener
	void Update();

protected:
	//Handles the currently occuring keyboard event
	void HandleKeyboardEvent();

	//Handles the currently occuring mouse event
	void HandleMouseEvent();

	//Handles the currently occuring gamepad event
	void HandleGamepadEvent();

	//Handles the currently occuring key down event
	void HandleKeyDownEvent();

	//Handles the currently occuring key up event
	void HandleKeyUpEvent();

	//Handles the currently occuring key down repeat event
	void HandleKeyDownRepeatEvent();

	//Handles the currently occuring key up repeat event
	void HandleKeyUpRepeatEvent();

	//Handle the currently occuring key move event
	void HandleKeyMoveEvent();

	//Handles the currently occuring mouse down event
	void HandleMouseDownEvent();

	//Handles the currently occuring mouse up event
	void HandleMouseUpEvent();

	//Handles the currently occuring mouse down repeat event
	void HandleMouseDownRepeatEvent();

	//Handles the currently occuring mouse up repeat event
	void HandleMouseUpRepeatEvent();

	//Handles the currently occuring mouse move event
	void HandleMouseMoveEvent();

	//Handles the currently occuring gamepad button down event
	void HandleGamepadButtonDownEvent();

	//Handles the currently occuring gamepad button up event
	void HandleGamepadButtonUpEvent();

	//Handles the currently occuring gamepad button down repeat event
	void HandleGamepadButtonDownRepeatEvent();

	//Handles the currently occuring gamepad button up repeat event
	void HandleGamepadButtonUpRepeatEvent();

	//Handles the currently occuring gamepad button move event
	void HandleGamepadButtonMoveEvent();

private:
	//The input device the event listener listens to
	unsigned int m_inputDevice;

	//The event type the event listener is listening for
	unsigned int m_eventType;

	//The event trigger the event listener is listening for
	unsigned int m_eventTrigger;

	//The event listeners callback function
	void(*m_callbackFunction)(void);

	//The current recorded state of the event listeners trigger
	bool m_currentState;

	//The previous recorded state of the event listeners trigger
	bool m_previousState;
};