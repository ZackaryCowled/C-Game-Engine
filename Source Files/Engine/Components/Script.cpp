//Internal includes
#include "Script.h"
#include "Application.h"

//Creates and initializes a Script instance (Default constructor)
Script::Script()
{
	//Initialize Script
	SetType(COMPONENT_TYPE_SCRIPT);
	Awake();
	Start();
}

//Called on script creation
void Script::Awake(){}

//Called on script initialization
void Script::Start(){}

//Called once per frame
void Script::Update(){}

//Called at the end of each frame
void Script::LateUpdate(){}