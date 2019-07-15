//
// Created by zhuhu on 2019/7/10.
//

#ifndef DSA_BST_H
#define DSA_BST_H

#include "../BinaryTree/BinTree.h"
template <typename T> class BST : public BinTree<T>{
protected:
    BinNode<T> *_hot;
    BinNode<T> *connect34(BinNode<T> *, BinNode<T> *, BinNode<T> *,
            BinNode<T> *, BinNode<T> *, BinNode<T> *, BinNode<T> *);
    BinNode<T> *rotateAt(BinNode<T> *x);

public:
    virtual BinNode<T> * &search(const T &e); // 查找
    virtual BinNode<T> *insert(const T &e); // 插入
    virtual bool remove(const T&e); // 删除
};

template <typename T> static BinNode<T> * &searchIn(BinNode<T> * &v, const T &e, BinNode<T> * &hot){
    if(!v || (e == v->data))return v;
    hot = v;
    return searchIn(((e < v->data) ? v->lc : v->rc), e, hot);
}
template <typename T> BinNode<T>* & BST<T>::search(const T &e) {
    return searchIn(this->_root, e, _hot=NULL);
}
template <typename T> BinNode<T>* BST<T>::insert(const T &e) {
    auto &x = search(e); if(x) return x;
    x = new BinNode<T>(e, this->_hot);
    this->_size ++;
    updateHeightAbove(x);
    return x;
}
template <typename T> static BinNode<T> *removeAt(BinNode<T> * &x, BinNode<T> * &hot){
    auto w = x;
    BinNode<T> *succ = NULL; // 左右子树都没有
    if(!HasLChild(*x)){ // 仅有右子树
        succ = x = x->rc;
    } else if(!HasRChild(*x)){ // 仅有左子树
        succ = x = x->lc; 
    } else{ // 左右子树都有
        w = w->succ();
        auto databak = x->data;
        x->data = w->data;
        w->data = databak;
        auto u = w->parent;
        ((u == x) ? u->rc : u->lc) = succ = w->rc;
    }
    hot = w->parent;
    if(succ) succ->parent = hot;
    release(w->data); release(w);
    return succ;
}
template <typename T> bool BST<T>::remove(const T &e) {
    auto &x = search(e); if(!x)return false;
    removeAt(x, _hot);
    this->_size--;
    updateHeightAbove(_hot);
    return true;
}
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
            return connect34(x->lc, x, x->c, x->parent, x->parent->rc, x->parent->parent, x->parent->parent->rc);
        }
        else { // zig-zag
            x->parent = x->parent->parent->parent;
            return connect34(x->parent->parent->lc, x->parent->parent, x->lc, x, x->rc, x->parent, x->parent->rc);
        }
    } else{ // zag
        if(IsRChild(*(x->parent))) { // zag-zag
            x->parent->parent = x->parent->parent->parent;
            return connect34(x->parent->parent->lc, x->parent->parent, x->parent->lc, x->parent, x->lc, x, x->rc);
        }
        else { // zag-zig
            x->parent = x->parent->parent->parent;
            return connect34(x->parent->lc, x->parent, x->lc, x, x->rc, x->parent->parent, x->parent->parent->rc);
        }
    }
}
//template <typename T> bool BST<T>::remove(const T &e) {
//    auto &x = search(e); if(!x) return false;
//    if(IsLeadf(*x)){
//        release(x->data); release(x);
//        x = NULL;
//        updateHeightAbove(this->_hot);
//    } else if(HasBothChild(*x){
//        auto suc = x->succ();
//        auto data = suc->data;
//        suc->data = x->data;
//        x->data = data;
//        if(HasRChild(*suc)){
//            suc->rc->parent = suc->parent;
//            FromParentTo(*suc) = suc->rc;
//            updateHeightAbove(suc->rc);
//            release(suc->data); release(suc); suc = NULL;
//        } else{
//            FromParentTo(suc) = NULL;
//            updateHeightAbove(suc->parent);
//            release(suc->data); release(suc); suc = NULL;
//        }
//    } else{
//        auto tmpx = x;
//        x = (HasLChild(*x) ? x->lc : x->rc);
//        x->parent = tmpx->parent;
//        updateHeightAbove(x);
//        release(tmpx->data); release(tmpx);
//    }
//    return true;
//}


#endif //DSA_BST_H
