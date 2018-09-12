//Pragma comments
#pragma once

//Internal includes
#include "File.h"

//External includes
#include <string>

//Using directives
using std::string;

//Singleton object that provides various output operation functions
class FileExporter
{
public:
	//Exports the specified file to the specified filepath
	//file - The file to export
	//filepath - The location, name and file extension to give the exported file
	static void ExportFile(File& file, const string& filepath);
};