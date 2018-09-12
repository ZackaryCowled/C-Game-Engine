//Pragma comments
#pragma once

//External includes
#include <string>
#include <vector>

//Using directives
using std::string;
using std::vector;

//Dynamic object that uses the vector container to store the contents of a file
class File
{
public:
	//Creates and initializes a File instance (Default constructor)
	//fileText - The text for the file in a singular string (Use FileImporter to import files)
	File(const string& fileText);

	//Adds the specified line to the end of the file
	//line - The line to add to the end of the file
	void AddLine(const string& line);

	//Emptys the File object by erasing all lines
	void Empty();

	//Returns the line at the specified index in the files line container
	//lineIndex - The line to get from the file (line 1 is located at line index 0)
	string GetLine(const int lineIndex);

	//Returns the next line in the file
	string GetLine();

	//Returns the number of lines in the file
	int GetNumberOfLines();

private:
	//Container of lines from the file
	vector<string> m_lineContainer;

	//The next line to read
	int m_nextLineIndex;
};