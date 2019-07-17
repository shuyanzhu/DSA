//
// Created by zhuhu on 2019/7/17.
//

#ifndef DSA_PQ_COMPLHEAP_H
#define DSA_PQ_COMPLHEAP_H

#include "../vector/vector.h"
#include "PQ.h"
#include "../_share/utils.h"
#define InHeap(n, i) (((-1) < (i)) && ((i) < (n))) // 判断PQ[i]是否合法
#define Parent(i) ((i - 1 ) >> 2) // PQ[i]的父亲节点
#define LastInternal(n) Parent(n-1) // 最后一个叶子节点的父亲既是最后的内部节点
#define LChild(i) (1 + (i) << 1)
#define RChild(i) (2 + (i) << 1)
#define ParentValid(i) (0 < (i))
#define LChildValid(n, i) (LChild(i) < n)
#define RChildValid(n, i) (RChild(i) < n)
#define Bigger(PQ, i, j) ((PQ)[i] < (PQ)[j] ? j : i) //比较哪个大
#define ProperParent(PQ, n, i) \
    (RChildValid(n, i) ? Bigger(PQ, Bigger(PQ, i, LChild(i)), RChild(i)) :\
    (LChildValid(n, i) ? Bigger(PQ, i, LChild(i)) : i))


template <typename T> class PQ_ComplHeap: public PQ<T>, public Vector<T>{
protected:
    Rank percolateDown(Rank n, Rank i); // 下滤
    Rank percolateUp(Rank i); // 上滤
    void heapify(Rank n); // floyd建堆算法
public:
    PQ_ComplHeap(){}
    PQ_ComplHeap(T *A, Rank n){ copyFrom(A, 0, n); heapify(n); } // 批量建堆
    void insert(T e) { Vector<T>::insert(e); percolateUp(this->_size -1); } // 插入词条.插入后进行上滤
    T getMax() { return this->_elem[0]; } // 读取优先级最高的词条
    T delMax(); // 删除优先级最高的词条
};
template <typename T> Rank PQ_ComplHeap<T>::percolateUp(Rank i) {
    while(ParentValid(i)){
        Rank j = Parent(i);
        if(this->_elem[i] < this->_elem[j])break;
        swap(this->_elem[i], this->_elem[j]);
        i = j;
    }
    return i; // 返回最终的上行位置
}
template <typename T> T PQ_ComplHeap<T>::delMax() {
    T maxElem = this->_elem[0]; this->_elem[0] = this->_elem[--this->size];
    percolateDown(this->_size, 0); //下滤到结尾
    return maxElem; // 返回被删除元素
}
template <typename T> Rank PQ_ComplHeap<T>::percolateDown(Rank n, Rank i) {
    while(i < n){
        Rank j = ProperParent(*this, n, i); // 为完全二叉堆的边界
        if(i == j) break;
        swap(this->_elem[i], this->_elem[j]);
        i = j;
    }
    return i; // 返回下滤最终抵达的位置
}
template <typename T> void PQ_ComplHeap<T>::heapify(Rank n) {
    for(int i = LastInternal(n); InHeap(n, i); i--)
        percolateDown(n, i);
}
#endif //DSA_PQ_COMPLHEAP_H
