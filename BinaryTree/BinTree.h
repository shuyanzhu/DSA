#pragma once

#include "BinNode.h" //引入二叉树节点类
#include "../_share/release.h"
template <typename T> class BinTree { //二叉树模板类
protected:
   int _size; BinNodePosi(T) _root; //规模、根节点
   virtual int updateHeight ( BinNodePosi(T) x ); //更新节点x的高度
   void updateHeightAbove ( BinNodePosi(T) x ); //更新节点x及其祖先的高度
public:
   BinTree() : _size ( 0 ), _root ( NULL ) { } //构造函数
   ~BinTree() { if ( 0 < _size ) remove ( _root ); } //析构函数
   int size() const { return _size; } //规模
   bool empty() const { return !_root; } //判空
   BinNodePosi(T) root() const { return _root; } //树根
   BinNodePosi(T) insertAsRoot ( T const& e ); //插入根节点
   BinNodePosi(T) insertAsLC ( BinNodePosi(T) x, T const& e ); //e作为x的左孩子（原无）插入
   BinNodePosi(T) insertAsRC ( BinNodePosi(T) x, T const& e ); //e作为x的右孩子（原无）插入
   BinNodePosi(T) attachAsLC ( BinNodePosi(T) x, BinTree<T>* &S ); //T作为x左子树接入（原无左子树）
   BinNodePosi(T) attachAsRC ( BinNodePosi(T) x, BinTree<T>* &S ); //T作为x右子树接入（原无右子树）
   int remove ( BinNodePosi(T) x ); //删除以位置x处节点为根的子树，返回该子树原先的规模
   BinTree<T>* secede ( BinNodePosi(T) x ); //将子树x从当前树中摘除，并将其转换为一棵独立子树
   template <typename VST> //操作器
   void travLevel ( VST& visit ) { if ( _root ) _root->travLevel ( visit ); } //层次遍历
   template <typename VST> //操作器
   void travPre ( VST& visit ) { if ( _root ) _root->travPre ( visit ); } //先序遍历
   template <typename VST> //操作器
   void travIn ( VST& visit ) { if ( _root ) _root->travIn ( visit ); } //中序遍历
   template <typename VST> //操作器
   void travPost ( VST& visit ) { if ( _root ) _root->travPost ( visit ); } //后序遍历
   bool operator< ( BinTree<T> const& t ) //比较器（其余自行补充）
   { return _root && t._root && lt ( _root, t._root ); }
   bool operator== ( BinTree<T> const& t ) //判等器
   { return _root && t._root && ( _root == t._root ); }
   /*DSA*/
   /*DSA*/void stretchToLPath() { stretchByZag ( _root ); } //借助zag旋转，转化为左向单链
   /*DSA*/void stretchToRPath() { stretchByZig ( _root, _size ); } //借助zig旋转，转化为右向单链
}; //BinTree

template <typename T> int BinTree<T>::updateHeight(BinNode<T> *x) {
    return x->height = 1 + std::max(stature(x->lc), stature(x->rc));
}
template <typename T> void BinTree<T>::updateHeightAbove(BinNode<T> *x) {
    while(x){ updateHeight(x); x = x->parent; }
}
template <typename T> BinNode<T> * BinTree<T>::insertAsRoot(const T &e) {
    _size = 1; return _root = new BinNode<T>(e);
}
template <typename T> BinNode<T> * BinTree<T>::insertAsLC(BinNode<T> *x, const T &e) {
    _size ++; x->insertAsLC(e); updateHeightAbove(x); return x->lc;
}
template <typename T> BinNode<T> * BinTree<T>::insertAsRC(BinNode<T> *x, const T &e) {
    _size ++; x->insertAsLC(e); updateHeightAbove(x);
    return x->rc;
}
template <typename T> BinNode<T> * BinTree<T>::attachAsLC(BinNode<T> *x, BinTree<T> *&S) {
    if (x->lc = S->_root)x->lc->parent = x;
    _size += S->_size;updateHeightAbove(x);
    S->_root == NULL; S->_size = 0; release(S); S = NULL;
    return x;
}
template <typename T> BinNode<T> * BinTree<T>::attachAsRC(BinNode<T> *x, BinTree<T> *&S) {
    if(x->rc = S->_root)S->_root->parent = x;
    _size += S->_size; updateHeightAbove(x);
    S->_root = NULL; S->_size = 0; release(S); S = NULL;
    return x;
}
template <typename T> static int removeAt(BinNode<T> *x){
    if(NULL == x)return 0;
    int n = 1 + removeAt(x->lc) + removeAt(x->rc);
    release(x->data); release(x);
    return n;
}
template <typename T> int BinTree<T>::remove(BinNode<T> *x) {
    FromParentTo(*x) = NULL;
    updateHeightAbove(x->parent);
    int n = removeAt(x);
    _size -= n;
    return n;
}
template <typename T> BinTree<T>* BinTree<T>::secede(BinNode<T> *x) {
    FromParentTo(*x) = NULL; updateHeightAbove(x->parent);
    auto ret = new BinTree<T>();
    ret->_root = x; ret->_size = x->size(); x->parent=NULL;
    _size -= ret->_size;
    return ret;
}
