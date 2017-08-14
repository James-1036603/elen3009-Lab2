// -------------------------------------------
//					Line
// -------------------------------------------

#include "Line.h"
Line::Line(const string& line)
{

	// Hint: some of string's member functions might come in handy here
	// for extracting words.
	auto tempStr = new char [line.length()+1];
	strcpy(tempStr,line.c_str());
	auto ch = strtok(tempStr," ");
	while(ch!=0){
		Word tmpWord(ch);
		_line.push_back(tmpWord);
		ch = strtok(NULL," ");
	}
}

bool Line::contains(const Word& search_word) const
{
	
	auto found = false;
	if(search_word.isQueryable()){
	for(int i = 0; i<_line.size();i++){
		if(_line[i]==search_word) found = true;		
	}
	} 
	return found;
}
