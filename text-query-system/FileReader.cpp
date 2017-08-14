// -------------------------------------------
//					FileReader
// -------------------------------------------

#include "FileReader.h"

FileReader::FileReader(const string& file_name): infile{file_name.c_str()}
{
	// in infile's constructor (called above in the memberwise initialisation list)
	// the input file stream is associated with a text file
	if ( !infile )
		throw FileCannotBeOpened();
}

void FileReader::readFileInto(Paragraph& file_receiver)
{
	string text_line;
	while (getline( infile, text_line, '\n' )) 	{
		Line word_line(text_line);
		file_receiver.addLine(word_line);
	}
}
