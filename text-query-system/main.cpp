#include <iostream>
#include <string>
#include <vector>

#include "Line.h"
#include "Word.h"
#include "Paragraph.h"
#include "FileReader.h"

using namespace std;

void DisplayLineNumbers(vector<int> inVec){
        for(int i = 0; i<inVec.size();i++){
                cout<<"Word found in line: "<<inVec[i]<<endl;
        }


}

void WordSearch(string inFileName, string sWord){
	FileReader file_reader(inFileName);
        Paragraph theParagraph;
        file_reader.readFileInto(theParagraph);
        Word search_word(sWord);
        vector<int> line_numbers;
        if(theParagraph.contains(search_word, line_numbers)) DisplayLineNumbers(line_numbers);
        else cout<<"Word not found."<<endl;
}

int main(void){
	string fileName;
	cout<<"Please enter the file name:";
	cin>>fileName;
	string sWord;
	while(true){
		cout<<"Please enter the search word, or '.' to quit:";
		cin>>sWord;
		if(sWord==".") break;
		else{
		WordSearch(fileName,sWord);
		}
	}
}
