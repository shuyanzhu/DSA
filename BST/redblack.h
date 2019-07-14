//
// Created by zhuhu on 2019/7/12.
//

#ifndef DSA_REDBLACK_H
#define DSA_REDBLACK_H

#include "bst.h"
#define IsBlk(p) ((!p) || (RB_BLACK == (p)->color))
#define IsRed(p) !(IsBlk(p))
#define BlackHeightUpdated(x) (\
    (stature((x).lc) == stature((x).rx)) && \
    ((x).height == (IsRed(&(x)) ? stature((x).lc) : stature((x).lc) + 1))\
)
template <typename T> class RBTree: public BST<T>{
protected:
    virtual int updateHeight(BinNode<T> *x);
    void solveDoubleRed(BinNode<T> *x);
    void solveDoubleBlk(BinNode<T> *x);
public:
    RBTree(){} // 使用BST->BinTree的默认构造函数
    ~RBTree(){} // 使用默认析构函数
    BinNode<T> *insert(T const &e);
    bool remove(T const &e);
};
template <typename T> int RBTree<T>::updateHeight(BinNode<T> *x) {
    x->height = std::max(stature(x->lc), stature(x->rc)); // 左右子树一般高度相等，除非发生双黑
    return IsBlk(x) ? x->height++ : x->height; // 此三元表达式虽然返回左值，但实测仍是寄存器里的值，改成++height为好
}
template <typename T> BinNode<T> *RBTree<T>::insert(const T &e) {
    auto &x = search(e); if(x) return false;
    x = new BinNode<T>(e, this->_hot,NULL, NULL, -1); // 作为叶子节点插入
    x->color = RB_RED; // 构造函数的默认传参为RED，此处多余
    if(!this->_hot){ // 表明新插入的节点为根节点
        x->color = RB_BLACK;
        updateHeight(x);
    }
    this->_size++; // 树的规模更新, 插入红色节点时不需要更新树的高度
    solveDoubleRed(x);
    return x ? x : this->_hot->parent;
}
template <typename T> void RBTree<T>::solveDoubleRed(BinNode<T> *x) {
    auto p = x->parent;
    if(IsRoot(*x)){ // 向上染色到达根节点，强行将根节点染色为黑色
        x->color = RB_BLACK;
        x->height++;
        return;
    }
    if(IsBlk(p)){ // 到达节点的父亲节点为黑色，不会发生双红缺陷
        return;
    }
    // x非根, 节点p一定存在,且为红色节点，x祖父节点一定存在
    auto g = p->parent;
    auto u = (IsLChild(*p) ? g->rc : g->lc);
    if(IsBlk(u)){ // 叔父节点为黑
        BinNode<T> *r = NULL;
        g->color = RB_RED;
        if((IsLChild(*x) && IsLChild(*p)) || (IsRChild(*x) && IsRChild(*p))){
            // zig-zig 或 zag-zag
            p->color = RB_BLACK;
        } else
            x->color = RB_BLACK;
        FromParentTo(*g) = r = rotateAt(x); // b->paren指向g父亲已在rotate中设置
        // 局部子树高度不变，故不需要继续向上更新树的高度
    } else{ // 叔父节点为红色
        p->color = RB_BLACK; p->height++;
        u->color = RB_BLACK; u->height++;
        g->color = RB_RED; // 如果g此时为根则进入下一层迭代时会强制染黑返回
        solveDoubleRed(g); // 继续调整祖父节点
    }
}
template <typename T> bool RBTree<T>::remove(const T &e) {
    auto &x = search(e); if(!x) return false;
    auto r = removeAt(x, this->_hot);
    if(!(--this->_size)) // 边界情况，删除的节点为唯一的根
        return true;
    if(!this->_hot){ // 删除的节点为根，但有后继节点
        this->_root->color = RB_BLACK;
        updateHeight(this->_root);
        return true;
    }
    if(BlackHeightUpdated(*(this->_hot)))
        return true; // 删除节点后并未失衡，无序进行调整，包含了x为红节点的情况
    if(IsRed(r)){
        r->color = RB_BLACK;
        r->height++; // 局部依然平衡，无需向上传播
        return true;
    }
    solveDoubleBlk(r);
    return true;
}
template <typename T> void RBTree<T>::solveDoubleBlk(BinNode<T> *r) {
    auto p = r ? r->parent : this->_hot;
    if(!p) return; // r在BB-2B情况下回上升到根节点
    auto s = (r == p->lc) ? p->rc : p->lc; // r的兄弟
    if(IsBlk(s)){ // 兄弟节点为黑
        BinNode<T> *t = NULL; // s的孩子，侄子节点
        if(IsRed(s->rc)) t = s->rc;
        if(IsRed(s->lc)) t = s->lc;
        if(t){ // 有红侄子可以过继.BB-1
            RBColor oldColor = p->color;
            auto b = FromParentTo(*p) = rotateAt(t); // 过继
            if(HasLChild(*b)){ // r可能为外部节点
                b->lc->color = RB_BLACK;
                updateHeight(b->lc);
            }
            if(HasRChild(*b)){
                b->rc->color = RB_BLACK;
                updateHeight(b->rc);
            }
            b->color = oldColor;
            updateHeight(b);
        } else{ //没有侄子可以过继，但是父亲为红色，可以合并节点
            s->color = RB_RED; s->height--;
            if(IsRed(p)){ // BB-2R, s没有孩子过继，需要父亲可以钱合并。局部高度不变
                p->color = RB_BLACK
            } else{ // BB-2B，s没有孩子过继，父亲也不可以过继
                p->height--; // p若为根节点
                solveDoubleBlk(p); //递归解决下溢，父亲必然发生下溢（双黑）
            }
        }
    } else{ // BB-3,兄弟s为红
        s->color = RB_BLACK; p->color = RB_RED;
        auto t = IsLChild(*s) ? s->lc : s->rc; // 去与父亲同侧的黑侄子
        this->_hot = p; // 新的发生下溢的节点父亲
        FromParentTo(*p) = rotateAt(t);
        solveDoubleBlk(r); // 继续解决双黑，此时父亲为红，但是获得了s为黑色的节点
        // 之后可能有红色侄子，有黑色侄子就找爸爸借
    }
}
#endif //DSA_REDBLACK_H
