#include <iostream>
#include <stdlib.h>
#include "../_share/utils.h"

using namespace std;
template <typename T>
void print(){
    T *elem = new T[10];
    cout << sizeof(T) << endl;
}
int main() {
//	cout << 2*sizeof(bool) << endl;
//    print<int>();
//    int table[26] = {0};
//    int sum = 0;
//    for(int i = 0; i < 26; i++){
//        table[i] = rand() % 100;
//        sum += table[i];
//    }
//    for(int i = 0; i < 26 ; i++){
//        cout <<"\'" << char('A' + i) << "\'" << ", ";
//    }
//    cout << sum;
//    int y = 0;
//    int z = 1;
//    auto x = (z == 1 ? y++ : y);
//    cout << x << y << endl;
    cout << ceil(0.5, 1) << round(0.5, 1) << floor(0.5, 1) << endl;
	return 0;
}

