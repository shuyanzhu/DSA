//
// Created by zhuhu on 2019/6/29.
//
#include "mystack.h"
#include <iostream>

using std::cout;
using std::endl;

Stack<char> &convert(Stack<char> &S, int num){
    const char table[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    if (num == 0) return S;
    else{
        S.push(table[num % 16]);
        convert(S, num / 16);
    }
}
int main(){
    Stack<char> S;
    while(S.size())S.pop();
    convert(S, 256);
    while(S.size()){
        printf("%c", S.pop());
    }
    cout << endl;
}

