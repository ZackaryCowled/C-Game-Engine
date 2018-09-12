//Internal includes
#include "FileImporter.h"
#include "Application.h"

//External includes
#include <fstream>

//Using directives
using std::getline;
using std::ifstream;
using std::to_string;

//Loads and returns the contents of the file at the filepath
//filepath - The location, name and file extension of the shader file
string FileImporter::ImportFile(const string& filepath)
{
	//Create attribute for storing lines of text
	string line = "";

	//Create attribute for storing the content of the file
	string text = "";

	//Create input file stream and open the file
	ifstream inputFileStream(filepath, std::ios::in);

	//If the file opened successfully
	if (inputFileStream.is_open())
	{
		//While there are lines to read in the file
		while (std::getline(inputFileStream, line))
		{
			//Read the line and insert it into the text
			text += line + "\n";
		}

		//Close the input file stream
		inputFileStream.close();
	}
	//Otherwise
	else
	{
		//Create and display error message window describing the error that occured
		ErrorMessageWindow errorMessageWindow = ErrorMessageWindow("ERROR", "ERROR: " + filepath + " failed to import!");

		//Quit the application
		Application::Quit();
	}

	//Return the text
	return text;
}