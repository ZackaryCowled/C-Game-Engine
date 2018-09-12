//Pragma comments
#pragma once

//External includes
#include <string>

//Using directives
using std::string;

//Object that displays a question to the user and stores the result for querying
class QuestionMessageWindow
{
public:
	//Creates a question message window with the specified title and message
	QuestionMessageWindow(const string& title, const string& message);

	//Returns the answer to the question
	const bool GetAnswer() const;

private:
	//The answer flag to the question
	bool m_answer;
};