#include<algorithm>
#include<string>
#include<iostream>

using namespace std;

int main(void){
	string me;
	cin>>me;
	cout<<me<<endl;
	transform(me.begin(), me.end(), me.begin(), ::tolower);
	cout<<me<<endl;
	return 0;
}
