#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include "mylist.h"
#include <iostream>
using namespace std;

int main(){
    auto a = List<int>();
    for (int i = 0; i < 600; i++)
        a.insertAsLast(i);
    cout << a.disordered() << endl;
    a.permute(a.first(), a.last()->succ);
    cout << a.disordered() << endl;
    a.selectSort();
    cout << a.disordered() << endl;
    return 0;
}
