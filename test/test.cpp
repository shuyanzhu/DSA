#include <iostream>
#include <stdlib.h>

using namespace std;
template <typename T>
void print(){
    T *elem = new T[10];
    cout << sizeof(T) << endl;
}
int main() {
//	cout << 2*sizeof(bool) << endl;
    print<int>();
	return 0;
}

