#pragma once
#include "../queue/queue.h"
#include "../stack/mystack.h"

// 与BinNode状态与性质的判断
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeadf(x) (!HasChild(x))
// 与BinNode具有特定关系的节点及指针
#define sibling(p) (IsLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc)
#define uncle(x) (IsLChild(*((x)->parent)) ? (x)->parent->parent->rc : (x)->parent->parent->lc)
#define FromParentTo(x) (IsRoot(x) ? this-> _root :(IsLChild(x) ? (x).parent->lc : (x).parent->rc))

#define BinNodePosi(T) BinNode<T>* //节点位置
#define stature(p) ((p) ? (p)->height : -1) //节点高度（与“空树高度为-1”的约定相统一）
typedef enum { RB_RED, RB_BLACK} RBColor; //节点颜色

template <typename T> struct BinNode { //二叉树节点模板类
// 成员（为简化描述起见统一开放，读者可根据需要进一步封装）
   T data; //数值
   BinNodePosi(T) parent; BinNodePosi(T) lc; BinNodePosi(T) rc; //父节点及左、右孩子
   int height; //高度（通用）
   int npl; //Null Path Length（左式堆，也可直接用height代替）
   RBColor color; //颜色（红黑树）
// 构造函数
   BinNode() :
      parent ( NULL ), lc ( NULL ), rc ( NULL ), height ( 0 ), npl ( 1 ), color ( RB_RED ) { }
   BinNode ( T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL,
             int h = 0, int l = 1, RBColor c = RB_RED ) :
      data ( e ), parent ( p ), lc ( lc ), rc ( rc ), height ( h ), npl ( l ), color ( c ) { }
// 操作接口
   int size(); //统计当前节点后代总数，亦即以其为根的子树的规模
   BinNodePosi(T) insertAsLC ( T const& ); //作为当前节点的左孩子插入新节点
   BinNodePosi(T) insertAsRC ( T const& ); //作为当前节点的右孩子插入新节点
   BinNodePosi(T) succ(); //取当前节点的直接后继
   void alongLeftBranch(BinNode<T> *p, Stack<BinNode<T> *> S);
   template <typename VST> void travLevel ( VST& ); //子树层次遍历
   template <typename VST> void travPre ( VST& ); //子树先序遍历
   template <typename VST> void traPre_I(VST &visit);
   template <typename VST> void travIn ( VST& ); //子树中序遍历
   template <typename VST> void traIn_I(VST &visit);
   template <typename VST> void tranIn_I1(VST &visit);
   template <typename VST> void travPost ( VST &visit); //子树后序遍历
    template <typename VST> void travPost_I(VST &visit);
// 比较器、判等器（各列其一，其余自行补充）
   bool operator< ( BinNode const& bn ) { return data < bn.data; } //小于
   bool operator== ( BinNode const& bn ) { return data == bn.data; } //等于
   /*DSA*/
   /*DSA*/BinNodePosi(T) zig(); //顺时针旋转
   /*DSA*/BinNodePosi(T) zag(); //逆时针旋转
};

template <typename T> int BinNode<T>::size() {
    int ret = 1;
    if(this->lc) ret += lc->size();
    if(this->rc) ret += rc->size();
    return ret;
}

template <typename T> BinNode<T> * BinNode<T>::insertAsLC(const T &e) {
    auto ret =  new BinNode<T>(e, this);
    this->lc = ret;
    return ret;
}

template <typename T> BinNode<T> * BinNode<T>::insertAsRC(const T &e) {
    auto ret = new BinNode<T>(e, this);
    this->rc = ret;
    return ret;
}
template <typename T> BinNode<T> * BinNode<T>::succ() {
    auto p = rc;
    if(p){
        while(p->lc)p = p->lc;
    }else {
        while(IsRChild(*p))p = p->parent; // 是父亲的右孩子叶子节点
        p = p->parent;
    }
    return p;
}
template <typename T> template<typename VST> void BinNode<T>::travLevel(VST &visit) {
    Queue<BinNode<T> *> Q;
    Q.enqueue(this);
    while(!Q.empty()){
        auto now = Q.dequeue();
        visit(now->data);
        if(now->lc)Q.enqueue(lc);
        if(now->rc)Q.enqueue(rc);
    }
}
template <typename T> template <typename VST> void BinNode<T>::travPre(VST &visit) { // 递归实现
    if(NULL == this) return;
    visit(this->data);
    travPre(this->lc);
    travPre(this->rc);
}
template <typename T> template <typename VST> void BinNode<T>::traPre_I(VST &visit) {
    if(NULL == this)
        return;
    Stack<BinNode<T> *> S;
    S.push(this);
    while (!S.empty()){
        auto p = S.pop();
        visit(p->data);
        if(HasRChild(*p))S.push(p->rc);
        if(HasLChild(*p))S.push(p->lc);
    }
}
template <typename T> template <typename VST> void BinNode<T>::travIn(VST &visit) { // 递归实现
    if(NULL == this)return;
    travIn(this->lc);
    visit(this->data);
    travIn(this->rc);
}
template <typename T> template <typename VST> void BinNode<T>::traIn_I(VST &visit) { // 增加along函数会比较容易想
    Stack<BinNode<T> *> S;
    auto x = this;
    while(true){
        if(x){ // 技巧，使用函数处理可能更加容易想到
            S.push(x);
            x = x->lc;
        } else if(!S.empty()){
            x = S.pop();
            visit(x->data);
            if(HasRChild(*x))x = x->rc;
            else x = NULL;
            // x = x->rc; 邓俊辉的代码，bravo !!!
        } else
            break;
    }
}
template <typename T>
template<typename VST> void BinNode<T>::tranIn_I1(VST &visit) {
    bool backtracked = false;
    auto x = this;
    while(true){
        if(!backtracked && HasLChild(*x)){
            x = x->lc;
        }else{
            if(NULL == x)break;
            visit(x->data);
            if(HasRChild(*x)){
                x = x->rc;
                backtracked = false;
            }
            else{
                backtracked = true;
                x = x->succ();
            }
        }
    }
}
template <typename T> void BinNode<T>::alongLeftBranch(BinNode<T> *p, Stack<BinNode<T> *> S) {
    S.push(p);
    while(p->lc)S.push(p = p->lc);
}
template <typename T> template <typename VST> void BinNode<T>::travPost(VST &visit) {
    if(NULL == this) return;
    travPost(lc);travPost(rc);
    visit(data);
}
template <typename T> template <typename VST> void BinNode<T>::travPost_I(VST &visit) { // 迭代实现不直观，困难得多
    Stack<BinNode<T> *> S;
    alongLeftBranch(this, S); // 对以左孩子为根的子树进行中序遍历
    while(!S.empty()){
        auto p = S.top();
        if(p->rc)alongLeftBranch(p->rc, S); // 对以右孩子为根的子树进行中序遍历,非邓式方法，比较难想到!!!
        else {
            visit(p->data);
            S.pop();
        }
    }
}
