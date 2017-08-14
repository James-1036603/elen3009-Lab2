#ifndef PARAGRAPH_H
#define PARAGRAPH_H

#include <vector>
#include "Word.h"
#include "Line.h"
using namespace std;

class Paragraph
{
public:
	// DO NOT MODIFY THE PUBLIC INTERFACE OF THIS CLASS

	// no need for constructor
	void addLine(const Line& line);
	// return true if the word is found in the paragraph; false otherwise
	// accepts and populates a vector with the line numbers at which the search word is found
	// if the search word is not found an empty vector is returned
	bool contains(const Word& search_word, vector<int>& line_numbers) const;	

private:	

};

#endif

