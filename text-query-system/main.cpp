#include <iostream>
#include <cstring>
#include "Line.h"
#include "Word.h"

using namespace std;

int main(void){
	string thisStr;
	cin>>thisStr;
	Word first_word("World!");
	Word search_word(thisStr);
	if(first_word==search_word) cout<<1<<endl;
	else cout<<0<<endl;
	return 0;
}
