#ifndef WORD_H
#define WORD_H

#include <string>
#include <algorithm>
using namespace std;

// empty classes to represent different exceptions
class WordContainsNoLetters {};
class WordContainsSpace {};


class Word
{
public:
	// DO NOT MODIFY THE PUBLIC INTERFACE OF THIS CLASS
	
	// constructor
	Word(const string& word);		
	// overloads is-equal-to (or equivalence) operator - this is very useful for testing, 
	// as we can compare words directly
	bool operator==(const Word& rhs) const;			
	// returns true if queryable, false otherwise
	// (according to the brief, words less than 3 characters are not queryable)
	bool isQueryable() const;
	//Check if the word is querable by custom length
        bool isQueryableByCustomLength(int Custom_Length) const;

	
	
private:

	string _word;	
	
	//Check if the word contains only letters
        bool ContainsLetters() const;

        //Check if the word contains any spaces
        bool HasSpaces() const;

};

#endif

