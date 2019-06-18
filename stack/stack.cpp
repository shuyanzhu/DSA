#include<cstdio>
#include"mystack.h"
#include <iostream>
using namespace std;
int main() {
    Stack<int> s;
    cout << s.size() << endl;
    for (int i = 0; i < 10; i++)s.push(i);
    for(int i = 0; i < 3; i++)s.pop();
    cout << s.size() << endl;
    cout << s.top() << endl;
	return 0;
}