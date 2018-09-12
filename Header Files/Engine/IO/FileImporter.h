//Pragma once
#pragma once

//External includes
#include <string>

//Using directives
using std::string;

//Singleton object that provides various input operation functions
class FileImporter
{
public:
	//Loads and returns the contents of the file at the filepath
	//filepath - The location, name and file extension of the shader file
	static string ImportFile(const string& filepath);
};