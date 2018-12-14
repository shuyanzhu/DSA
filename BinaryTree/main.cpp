#include <iostream>
#include <algorithm>
#include <stack>
#define stature(p) ((p) ? (p)->height : -1)
using namespace std;

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

template <typename T>
class BinTree
{
  protected:
    int _size;
    BinNode<T> *_root;
    virtual int updateHeight(BinNode<T> *x)
    { // 更新节点x的高度
        return max(stature(x->left, stature(x->right)));
    }
    void updateHeightAbove(BinNode<T> *x)
    {
        while (x) {
            updateHeight(x);
            x = x->parent;
        }
    }

  public:
    int size() { return _size; }
    bool empty() { return !_root; }
    BinNode<T> *root() const { return _root; }
    BinNode<T> *insertAsLC(BinNode<T> *x, const T &e)
    {
        _size++;
        x->insertAsLC(e);
        updateHeightAbove(x);
        return x->left;
    }
    BinNode<T> *insertAsRC(BinNode<T> *x, const T &e)
    {
        _size++;
        x->insertAsRC(e);
        updateHeightAbove(x);
        return x->right;
    }
    template <typename VST>
    void traPost(VST &visit) const
    {
        _root->traPost(visit);
    }
};

int main()
{
    BinNode<int> *p1 = new BinNode<int>(), *p2 = NULL;
    printf("%d\n", p1->data);
    return 0;
}