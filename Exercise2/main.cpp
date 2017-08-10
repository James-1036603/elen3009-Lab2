#include<vector>
#include <iostream>

using namespace std;


int main(void){
	vector<int> vec;
	cout<< "vec: size: "<<vec.size()
		<< "capacity: "<<vec.capacity()<<endl; //The size and capacity should start off as 0
	for(int i = 0; i<24; i++){
		vec.push_back(i);
		cout<< "vec: size: "<<vec.size()
                << "capacity: "<<vec.capacity()<<endl; //The vector size and capacity should both be 24-- Wrong, the capacity ends up to be 32
	}
	return 0;
}

//It was seen that capacity reserves memory in powers of two. This is likely to allow for the size to be incremented, within reserved memory. According to cplusplus, capacity indicates the maximum allowed amount of elements, before extending the size.
