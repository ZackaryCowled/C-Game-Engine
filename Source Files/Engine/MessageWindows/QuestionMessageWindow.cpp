//Internal includes
#include "QuestionMessageWindow.h"

//External includes
#include <Windows.h>

//Creates a question message window with the specified title and message
QuestionMessageWindow::QuestionMessageWindow(const string& title, const string& message)
{
	//If the user answers yes to the specified question message
	if (MessageBox(NULL, message.c_str(), title.c_str(), MB_YESNO | MB_ICONINFORMATION) == IDYES)
	{
		//Set the answer to true
		m_answer = true;
	}
	//Otherwise
	else
	{
		//Set the answer to false
		m_answer = false;
	}
}

//Returns the answer to the question
const bool QuestionMessageWindow::GetAnswer() const
{
	//Return the answer
	return m_answer;
}