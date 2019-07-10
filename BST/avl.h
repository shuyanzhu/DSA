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
template <typename T> BinNode<T>* BST<T>::connect34(BinNode<T> *T0, BinNode<T> *a, BinNode<T> *T1, BinNode<T> *b,
                                                    BinNode<T> *T2, BinNode<T> *c, BinNode<T> *T3) {

    a->lc = T0; if(T0)T0->parent = a;
    a->rc = T1; if(T1)T1->parent = a;
    updateHeightAbove(a); // T的高度是已经维护的，需要重新维护a, b, c的高度
    c->lc = T2; if(T2)T2->parent = c;
    c->rc = T3; if(T3)T3->parent = c;
    updateHeight(c);
    b->lc = a; a->parent = b;
    b->rc = c; c->parent = c;
    updateHeight(b);
    return b;
}
template <typename T> BinNode<T>* BST<T>::rotateAt(BinNode<T> *x) {
    if(IsLChild(*x)){ // zig
        if(IsLChild(*(x->parent))) {// zig-zig
            x->parent->parent = x->parent->parent->parent;
            connect34(x->lc, x, x->c, x->parent, x->parent->rc, x->parent->parent, x->parent->parent->rc);
        }
        else { // zig-zag
            x->parent = x->parent->parent->parent;
            connect34(x->parent->parent->lc, x->parent->parent, x->lc, x, x->rc, x->parent, x->parent->rc);
        }
    } else{ // zag
        if(IsRChild(*(x->parent))) { // zag-zag
            x->parent->parent = x->parent->parent->parent;
            connect34(x->parent->parent->lc, x->parent->parent, x->parent->lc, x->parent, x->lc, x, x->rc);
        }
        else { // zag-zig
            x->parent = x->parent->parent->parent;
            connect34(x->parent->lc, x->parent, x->lc, x, x->rc, x->parent->parent, x->parent->parent->rc);
        }
    }
}
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
