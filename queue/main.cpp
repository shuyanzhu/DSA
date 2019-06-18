//
// Created by zhuhu on 2019/6/18.
//
#include "queue.h"
#include <iostream>
using namespace std;

int main(){
    Queue<int> q;
    cout << q.size() << endl;
    q.enqueue(5);
    q.enqueue(10);
    q.enqueue(100);
    q.dequeue();
    cout << q.size() << endl;
    cout << q.front() << endl;
}
