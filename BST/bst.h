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
template <typename K, typename V> struct Entry{
    K key; V value;
    Entry (K k = K(), V v = V()): key(k), value(v){}
    Entry (Entry<K, V> const &e): key(e.key), value(e.value){}
    bool operator< (Entry<K, V> const &e){ return key < e.key; }
    bool operator<= (Entry<K, V> const &e){ return key <= e.key; }
    bool operator> (Entry<K, V> const &e){ return key > e.key; }
    bool operator>= (Entry<K, V> const &e){ return key >= e.key; }
    bool operator== (Entry<K, V> const &e){ return key == e.key; }
    bool operator!= (Entry<K, V> const &e){ return key != e.key; }

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
