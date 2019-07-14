//
// Created by zhuhu on 2019/7/10.
//

#ifndef DSA_AVL_H
#define DSA_AVL_H

#include "bst.h"
#define Balanced(x) (stature((x).lc) == stature((x).rc))
#define BalFac(x) (stature((x).lc) - stature((x).rc))
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))
#define tallerChild(x) ( \
    stature((x).lc) > stature((x).rc) ? (x).lc : ( \
    stature((x).lc) < stature((x).rc) ? (x).rc : ( \
    IsLChild(x) ? (x).lc : (x).rc \
    ) \
    ) \
)

template <typename T> class AVL: public BST<T>{
public:
    BinNode<T> *insert(const T &e);
    bool remove(const T &e);
};

template <typename T> BinNode<T>* AVL<T>::insert(const T &e) {
    auto &x = search(e); if(x) return x;
    auto xx = x = new AVL<T>(e, this->_hot); // x为引用类型，不需要设置父节点的下行指针
    this->_size++;
    for(BinNode<T> *g = this->_hot; g; g = g->parent){
        if(!AvlBalanced(*g)) {
            FromParentTo(*g) = rotateAt(g);
            break;
        }
        updateHeight(g); // 未发生失衡也可能使树高增加
    }
    return xx;
}
template <typename T> bool AVL<T>::remove(const T &e) {
    auto &x = search(e); if(!x) return false;
    removeAt(x, this->_hot); this->_size--;
    for(auto g = this->_hot; g; g = g->parent){
        if(!AvlBalanced(*g)){
            g = FromParentTo(*g) = rotateAt(g);
        }
        updateHeight(g);
    }
    return true;
}
#endif //DSA_AVL_H
