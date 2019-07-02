//
// Created by zhuhu on 2019/6/29.
//
#include "mystack.h"
#include "iostream"

using namespace std;

bool paren(const char *exp){
    Stack<char> S;
    while(*exp != '\0'){
        switch(*exp){
            case '(':
                S.push(*exp++);
                break;
            case ')':
                if(S.empty())return false;
                S.pop();exp++;break;
            default:
                exp++;
        }
    }
    return S.empty();
}

int main(){
    const char exp[] = ")((()()))()";
    cout << paren(exp) << endl;
}
