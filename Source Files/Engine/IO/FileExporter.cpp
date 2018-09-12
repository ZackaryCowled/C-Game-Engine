//Internal includes
#include "FileExporter.h"

//External includes
#include <fstream>

//Using directives
using std::ofstream;

//Exports the specified file to the specified filepath
//file - The file to export
//filepath - The location, name and file extension to give the exported file
void FileExporter::ExportFile(File& file, const string& filepath)
{
	//Create output file stream
	ofstream outputFileStream;

	//Open the specified filepath
	outputFileStream.open(filepath, std::ios::out);

	//Find the last line index in the file
	int lastLineIndex = file.GetNumberOfLines() - 1;

	//For each line in the file
	for (int lineIndex = 0; lineIndex < lastLineIndex; lineIndex++)
	{
		//Output line from file
		outputFileStream << file.GetLine(lineIndex) << '\n';
	}

	//Output last line from the file
	outputFileStream << file.GetLine(lastLineIndex);

	//Close the specified filepath
	outputFileStream.close();
}