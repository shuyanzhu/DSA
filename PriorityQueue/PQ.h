//
// Created by zhuhu on 2019/7/17.
//

#ifndef DSA_PQ_H
#define DSA_PQ_H
template <typename T> struct PQ{
    virtual void insert(T) = 0;
    virtual T getMax() = 0;
    virtual T delMax() = 0;
};
#endif //DSA_PQ_H
