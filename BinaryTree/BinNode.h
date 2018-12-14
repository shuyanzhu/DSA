#pragma once
#define stature(p) ((p) ? (p)->height : -1)
template <typename T>
struct BinNode
{
    T data;
    BinNode<T> *parent, *left, *right;
    int height;
    int npl;
    int color; // 高级数据结构需要的指标
    BinNode()
        : parent(NULL)
        , left(NULL)
        , right(NULL)
        , height(0)
        , npl(0)
        , color(0)
    {}
    BinNode(
        const T &e,
        BinNode<T> *p = NULL,
        BinNode<T> *lc = NULL,
        BinNode<T> *rc = NULL,
        int h = 0)
        : data(e)
        , parent(p)
        , left(lc)
        , right(rc)
    {}

    int size()
    { // 线性时间复杂度
        // 树形递归，考察递归基是什么？
        // 没有左右孩子的节点即为递归基
        int s = 1;
        if (left) s += left->size();
        if (right) s += right->size();
        return s;
    }
    BinNode<T> *insertAsLC(const T &e) { return left = new BinNode(e, this); }
    BinNode<T> *insertAsRC(const T &e) { return right = new BinNode(e, this); }
    BinNode<T> *succ();
    template <typename VST>
    void goAlongLeftBranch(BinNode<T> *x, VST &visit, stack<BinNode<T> *> &S)
    {
        while (x) {
            S.push(x);
            x = x->left;
        }
    }
    template <typename VST>
    void traPost(VST &visit)
    {
        BinNode<T> *x = this;
        if (!x) return;
        stack<BinNode<T> *> S;
        goAlongLeftBranch(x, visit, S);
        while (true) {
            if (S.empty()) break;
            x = S.top();
            if (x->right) goAlongLeftBranch(x->right, visit, S);
            visit(S.pop()->data);
        }
    }
};