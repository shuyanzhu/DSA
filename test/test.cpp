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
//    print<int>();
    int table[26] = {0};
    int sum = 0;
    for(int i = 0; i < 26; i++){
        table[i] = rand() % 100;
        sum += table[i];
    }
    for(int i = 0; i < 26 ; i++){
        cout <<"\'" << char('A' + i) << "\'" << ", ";
    }
    cout << sum;
	return 0;
}

