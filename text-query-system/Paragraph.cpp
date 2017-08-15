// -------------------------------------------
//					Paragraph
// -------------------------------------------

#include "Paragraph.h"

void Paragraph::addLine(const Line& line)
{
	_theParagraph.push_back(line);
}

bool Paragraph::contains(const Word& search_word, vector<int>& line_numbers) const
{	
	auto itContains = false;
	for(int i = 0; i< _theParagraph.size(); i++){
		if(_theParagraph.at(i).contains(search_word)){ itContains = true; line_numbers.push_back(i+1); };
		
	}
	return itContains;
}
