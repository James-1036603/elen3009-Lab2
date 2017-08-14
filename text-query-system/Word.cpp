// -------------------------------------------
//					Word
// -------------------------------------------

#include "Word.h"

Word::Word(const string& word): _word{word}
{
	// throws an exception (in the form of WordContainsNoLetters object)
	// indicating that the word being constructed contains no letters
	if (_word.empty()) throw WordContainsNoLetters();
	if (!Word::ContainsLetters()) throw WordContainsNoLetters();
	if (Word::HasSpaces()) throw WordContainsSpace();
	// Note, we will cover exceptions in more detail later on in the course.
}

// overloads the equivalence operator which allows to Words to be compared using ==
bool Word::operator==(const Word& rhs) const
{
	if (_word == rhs._word)
		return true;
	else
		return false;
}

bool Word::isQueryable() const
{
	if(_word.length()>=3) return true;
	else return false;
}


bool Word::ContainsLetters() const//Check whether the word has at least one letter
{
	char ch;
        bool hasLetter = false;
        for(int i = 0; i<_word.length(); i++){
                ch = _word[i];
                if(((ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A'))){//Check each character if it is a letter, if it is, variable set to true and break
                hasLetter=true;
                break;
                }
        }
	return hasLetter;
}

bool Word::HasSpaces() const {
	bool hasSpaces = false;
	char ch;
	for(int i = 0; i<_word.length(); i++){
		ch = _word[i];
		if(ch == ' '){
			hasSpaces = true;
			break;
		}
	}
	return hasSpaces;
}

bool Word::isQueryableByCustomLength(int Custom_Length) const{
	if(_word.length()>= Custom_Length)return true;
	else return false;
}
