//
// Created by zhuhu on 2019/7/17.
//

#ifndef DSA_PQ_LEFTHEAP_H
#define DSA_PQ_LEFTHEAP_H

#include "PQ.h"
#include "../BinaryTree/BinTree.h"

template <typename T> class PQ_LeftHeap: public PQ<T>, public BinTree<T>{
public:
    PQ_LeftHeap() {}
    PQ_LeftHeap(T *E, int n) { // 批量构造，可以使用floyd建堆算法
        for(int i = 0; i < n; i++) insert(E[i]);
    }
    void insert(T e);
    T getMax(){ return this->_root->data;}
    T delMax();
};
template <typename T> BinNode<T> *merge(BinNode<T> *a, BinNode<T> *b){
    if(!a)return b; // 递归基
    if(!b)return a;
    if(a->data < b->data)swap(a, b);
    a->rc = merge(a->rc, b);
    a->rc->parent = a;
    if(!a->lc || a->lc->npl < a->rc->npl) swap(a->lc, a->rc);
    a->npl = a->rc ? a->rc->npl + 1 : 1;
    return a;
} // 堆的规模需要上层调用者更新
template <typename T> T PQ_LeftHeap<T>::delMax() {
    auto lc = this->_root->lc;
    auto rc = this->_root->rc;
    T e = this->_root->data; delete this->_root;
    this->_root = merge(lc, rc);
    this->_size--;
    if(this->_root)this->_root->parent = NULL;
    return e;
}
template <typename T> void PQ_LeftHeap<T>::insert(T e) {
    auto a = new BinNode<T>(e);
    this->_root = merge(a, this->_root);
    this->_root->parent = NULL; // 根节点有可能发生变化
    this->_size++;

}
#endif //DSA_PQ_LEFTHEAP_H
