//
// Created by zhuhu on 2019/6/18.
//

#ifndef DSA_QUEUE_H
#define DSA_QUEUE_H
#include "../List/mylist.h"

template <typename T> class Queue: protected List<T>{
public:
    int size(){ return this->_size; }
    bool empty() { return this->_size == 0; }
    void enqueue(const T &e){ this->insertAsLast(e); }
    T dequeue() { return this->remove(this->last()); }
    T &front() { return this->last()->data; }
};

#endif //DSA_QUEUE_H
