//
// Created by zhuhu on 2019/7/11.
//

#ifndef DSA_BTREE_H
#define DSA_BTREE_H

//#include "array.h"
#include "../vector/vector.h"
#include "../_share/release.h"
template <typename T> struct BTNode{
    BTNode<T> *parent;
    Vector<T> key;
    Vector<BTNode<T> *> child;
    // 只能作为根节点进行创建
    BTNode(){ parent = NULL; child.insert(0, NULL); } // 不需要使用构造函数列表，成员均可默认初始化
    BTNode(T e, BTNode<T> *lc = NULL, BTNode<T> *rc = NULL){
        parent = NULL;
        key.insert(0, e);
        child.insert(0, lc); child.insert(1, rc); // 至少一个节点，两个孩子
        if(lc)lc->parent = this; if(rc)rc->parent = this;
    }
};
template <typename T> class BTree{
protected:
    int _size;
    int _order;
    BTNode<T> *_root;
    BTNode<T> *_hot;
    void solveOverflow(BTNode<T> *x); // 因插入上溢分裂
    void solveUnderflow(BTNode<T> *x); // 因删除下溢合并
public:
    BTree(int _order = 3):_order(3), _size(0){ _root = new BTNode<T>(); }
    ~BTree();
    int const order(){ return _order; }
    int const size() { return _size; }
    BTNode<T> * &root(){ return _root; }
    bool empty() const { return !_root; }
    BTNode<T> *search(const T &e);
    bool insert(const T &e);
    bool remove(const T &e);
};
template <typename T> BTNode<T>* BTree<T>::search(const T &e) {
    auto v = _root; _hot = NULL;
    while(v){
        Rank r = v->key.search(0, _order, e);
        if((0 <= r) && (e == v->key[r])) return v;
        _hot = v; v = v->child[r+1];
    }
    return NULL;
}
template <typename T> bool BTree<T>::insert(const T &e) {
    auto x = search(e); if(x)return false;
    Rank r = _hot->key.search(e); // _hot节点必为叶子节点
    _hot->key.insert(r+1, e);
    _hot->child.insert(r+2, NULL);
    _size --;
    solveOverflow(_hot);
    return true;
}
template <typename T> void BTree<T>::solveOverflow(BTNode<T> *x) {
    if(x->child.size() <= _order) return;
    auto p = x->parent;
    if(!p){ // 分裂到达根，先考虑向上的边界情况
        x->parent = p = _root = new BTNode<T>(); // 创建新的根
        p->child[0] = x; // 新创建的根节点孩子节点指向原来的根节点
    }
    Rank mi = _order / 2;
    auto s = new BTNode<T>();
    for(int i = 0; i < _order - mi - 1; i++){
        s->key.insert(i, x->key.remove(mi + 1));
        s->child.insert(i, x->child.remove(mi + 1));
    }
    s[_order - mi - 1] = x->child.remove(mi + 1);
    if(s->child[0]){  // 如果非叶子节点分裂
        for(int i = 0; i < s->child.size(); i++)
            s->child[i]->parent = s; // 重置节点父亲
    }
    Rank i = p->key.search(x->key[mi]);
    p->key.insert(i+1, x->key.remove(mi));
    p->child.insert(i+2, s); // 新节点比向父节点插入的关键码大
    solveOverflow(p); // 继续解决上溢
}

template <typename T> bool BTree<T>::remove(const T &e) {
    auto x = search(e); if(!x) return false;
    Rank r =  x->key.search(e); // 一定能找到
    if(x->child[0]){ // 如果x非叶子节点
        auto succ = x->child[r+1];
        while(succ->child[0]) succ = succ->child[0];
        x->key[r] = succ->key[0]; succ->key[0] = e; x = succ; r = 0;
    }
    x->key.remove(r);
    x->child.remove(r + 1);
    _size --;
    solveUnderflow(x);
    return true;
}
template <typename T> void BTree<T>::solveUnderflow(BTNode<T> *x) {
    if(x != _root && ((1 + _order) / 2 <= x->child.size())) return;
    if(x == _root){
        if(2 <= x->child.size()) return; // 根节点的下溢值为2
        if(x->child[0]){ // 树还有其他节点
            _root = x->child[0];
            _root->parent = NULL; // 根节点的父亲为空
            x->child[0] = NULL; // 避免容器释放根节点
            release(x);
        }
        return; // 根是树中的唯一节点
    }
    auto p = x->parent; // p一定非空
    Rank r = 0;
    while(p->child[r] != x)r++;
    BTNode<T> *ls = NULL, *rs = NULL;
    if((0 < r) && (ls = p->child[r - 1]) && ((_order + 1) / 2) < ls->child.size()){
        auto bak = p->key[r-1]; // r为child指针，选择key时需要-1
        p->key[r-1] = ls->key.remove(ls->key.size()-1);
        x->key.insert(0, bak);
        x->child.insert(0, ls->child.remove(ls->child.size()-1));
        if(x->child[0])
            x->child[0]->parent = x;
        return; // 已经完成所有层的下溢处理
    } else if(r < p->child.size() - 1 && (rs = p->child[r+1]) &&(1 + _order) / 2 < rs->child.size()){
        auto bak = p->key[r];
        p->key[r] = rs->key.remove(0);
        x->key.insert(bak);
        x->child.insert(rs->child.remove(0));
        if(x->child[0])
            x->child[x->child.size()-1]->parent = x;
        return; // 处理完成
    } else {
        if(r == 0){ // 和右兄弟合并
            x->key.insert(p->key.remove(r));
            rs = p->child[r+1];
            p->child.remove(r+1); // 删除指向有兄弟的指针
            for(int i = 0; i < (_order - 1) / 2; i++){
                x->key.insert(rs->key.remove(0));
                x->child.insert(rs->child.remove(0));
            }
            x->child.insert(rs->child.remove(0));
            delete(rs); // 释放右兄弟
            if(x->child[0])
                for(int i = 0; i < x->child.size(); i++)
                    x->child[i]->parent = x;
        } else{ // 和左星弟合并
            ls = p->child[r-1];
            ls->key.insert(p->key.remove(r-1)); p->child.remove(r); // 需要删除child指针
            for(int i = 0; i < (_order - 1) / 2 - 1; i++){
                ls->key.insert(x->key.remove(0));
                ls->child.insert(x->child.remove(0));
            }
            ls->child.insert(x->child.remove(0));
            delete(x); // 释放自己，返回左兄弟
            if(ls->child[0])
                for(int i = 0l i < ls->child.size(); i++)
                    ls->child[0]->parent = ls;
        }
    }
    solveUnderflow(p);
}
#endif //DSA_BTREE_H
