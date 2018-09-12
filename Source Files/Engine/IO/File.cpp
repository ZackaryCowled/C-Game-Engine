//Internal includes
#include "File.h"

//External includes
#include <sstream>

//Using directives
using std::getline;
using std::istringstream;

//Creates and initializes a File instance (Default constructor)
//fileText - The text for the file in a singular string (Use FileImporter to import files)
File::File(const string& fileText)
{
	//Initialize File
	m_lineContainer = vector<string>();
	m_nextLineIndex = 0;

	//Create line buffer for storing lines of text
	string lineBuffer;

	//Create input string stream linked to the specified file text
	istringstream inputStringStream = istringstream(fileText);

	//For each line in the input string stream
	while(getline(inputStringStream, lineBuffer))
	{
		//Add the line to the file
		m_lineContainer.push_back(lineBuffer);
	}
}

//Adds the specified line to the end of the file
//line - The line to add to the end of the file
void File::AddLine(const string& line)
{
	//Add a copy of the specified line to the file
	m_lineContainer.push_back(line);
}

//Emptys the File object by erasing all lines
void File::Empty()
{
	//Erase every line in the files line container
	for (; m_lineContainer.size() != 0; m_lineContainer.erase(m_lineContainer.begin()));
}

//Returns the line at the specified index in the files line container
//lineIndex - The line to get from the file (line 1 is located at line index 0)
string File::GetLine(const int lineIndex)
{
	//Set the next line index
	m_nextLineIndex = lineIndex + 1;

	//If the line index is a valid line index
	if (lineIndex < (int)m_lineContainer.size())
	{
		//Return the line at the specified line index in the files line container
		return m_lineContainer[lineIndex];
	}

	//The line is not valid
	return "";
}

//Returns the next line in the file
string File::GetLine()
{
	//Increment the next line index
	++m_nextLineIndex;

	//Return the line
	return GetLine(m_nextLineIndex - 1);
}

//Returns the number of lines in the file
int File::GetNumberOfLines()
{
	//Return the number of lines in the file
	return (unsigned int)m_lineContainer.size();
}