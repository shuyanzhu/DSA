/*
 * @Author: 朱会茗
 * @Date: 2018-10-08 16:36:39
 * @LastEditors: OBKoro1
 * @LastEditTime: 2018-10-08 16:36:39
 * @Description:
 */
#ifndef MYLIST
#define MYLIST

#include <stdio.h>
#include <stdlib.h>

typedef int Rank;

int debug = 0;

template <typename T>
class Node
{
  public:
    T data;
    Node<T> *pred;
    Node<T> *succ;

    // 构造函数
    Node()
        : data(0)
        , pred(NULL)
        , succ(NULL)
    {}
    Node(T e, Node<T> *p = NULL, Node<T> *s = NULL)
        : data(e)
        , pred(p)
        , succ(s)
    {}

    // 操作接口: 插入作为前驱或后继
    Node<T> *insertAsPred(const T &e)
    {
        Node<T> *x = new Node(e, pred, this);
        pred->succ = x;
        pred = x;
        return x;
    }
    Node<T> *insertAsSucc(const T &e)
    {
        Node<T> *x = new Node(e, this, succ);
        succ->pred = x;
        succ = x;
        return x;
    }
};

// 主要有插入/删除，查找，唯一化,排序和遍历
template <typename T>
class List
{
  private:
    int _size;
    Node<T> *header;
    Node<T> *trailer;

  public:
    // 初始化函数复用
    void init()
    {
        header = new Node<T>;
        trailer = new Node<T>;
        header->succ = trailer;
        trailer->pred = header;
        _size = 0;
    }
    void copyNodes(Node<T> *p, int n)
    {
        init();
        while (n--) {
            insertAsLast(p->data);
            p = p->succ;
        }
    }
    // 排序函数,选择排序总是n2，插入排序最好有线性时间复杂度
    void swap(Node<T> *a, Node<T> *b)
    {
        T e = a->data;
        a->data = b->data;
        b->data = e;
    }
    Node<T> *selectMax(Node<T> *p, int n)
    {
        Node<T> *max = p;
        for (; n--; p = p->succ)
            if (max->data <= p->data) max = p;
        return max;
    }
    void selectSort()
    {
        int size = _size;
        for (Node<T> *p = last(); p != first(); p = p->pred) {
            Node<T> *max = selectMax(first(), size--);
            swap(max, p);
        }
    }
    void merge(Node<T> *begin, Node<T> *mi, Node<T> *end)
    {
        List L(begin, mi);
        Node<T> *i = L.first(), *j = mi, *k = begin;
        for (; (i != L.last()->succ) || (j != end);) {
            if ((i != L.last()->succ) &&
                (!(j != end) || (i->data <= j->data))) {
                k->data = i->data;
                k = k->succ;
                i = i->succ;
            }
            if ((j != end) && (!(i != L.last()->succ) || (j->data < i->data))) {
                k->data = j->data;
                k = k->succ;
                j = j->succ;
            }
        }
    }
    void mergeSort(Node<T> *begin, Node<T> *end)
    {
        if (begin->succ == end) return;
        if (begin == end) return;
        Node<T> *i = begin, *j = end;
        for (; !((i->succ == j) || (i == j)); i = i->succ, j = j->pred)
            ;
        Node<T> *mi = i;
        mergeSort(begin, mi);
        mergeSort(mi, end);
        merge(begin, mi, end);
    }
    // 实现得不好，暂时这样实现
    void insertSort()
    {
        for (Node<T> *p = first()->succ; p != trailer;) {
            Node<T> *x = search(p->data, first(), p);
            insertA(x, p->data);
            p = p->succ;
            remove(p->pred);
        }
    }

  public:
    // 构造与析构接口
    List() { init(); }
    List(const List<T> &L)
    {
        init();
        for (Node<T> *p = L.first(); !L.empty(); p = p->succ) {
            insertAsLast(p->data);
            if (p == L.last()) break;
        }
    }
    List(const List<T> &L, Rank r, int n)
    {
        Node<T> *p = L.first();
        for (int i = 0; i < r; i++)
            p = p->succ; // 第r+1个元素
        copyNodes(p, n);
    }
    // List(const Node<T> *p, int n) {
    //	copyNodes(p, n);
    //}
    List(Node<T> *begin, Node<T> *end)
    {
        init();
        for (Node<T> *p = begin; p != end; p = p->succ)
            insertAsLast(p->data);
    }
    ~List()
    {
        while (!empty())
            remove(first());
        delete header;
        delete trailer;
    }

    // 只读接口: 查找(有序和无序的最坏时间复杂度相同)
    bool empty() const { return header->succ == trailer; }
    Rank size() const { return _size; }
    Node<T> *first() const { return header->succ; }
    Node<T> *last() const { return trailer->pred; }
    bool valid(Node<T> *p)
    {
        return (p != NULL) && (p != header) && (p != trailer);
    }
    int disordered()
    {
        if (empty()) return -1;
        Node<T> *p = first()->succ;
        for (int n = 0; p != trailer; p = p->succ) {
            if (p->pred->data > p->data) n++;
        }
    }
    Node<T> *find(const T &e)
    {
        Node<T> *p = first();
        for (int i = 0; i < _size; i++, p = p->succ)
            if (p->data == e) return p;
        return NULL;
    }
    Node<T> *find(const T &e, Node<T> *begin, Node<T> *end)
    {
        for (Node<T> *p = begin; p != end; p = p->succ)
            if (p->data == e) return p;
        return NULL;
    }
    Node<T> *search(T &e, Node<T> *begin, Node<T> *end)
    {
        if (begin == end) return NULL;
        Node<T> *p = end->pred;
        for (; p != begin->pred; p = p->pred)
            if (p->data <= e) return p;
        return begin->pred;
    }

    // 读写接口: 插入/删除、排序(尚未完成)、唯一化(尚未完成,有序无序相同)
    Node<T> *insert(Rank r, const T &e)
    {
        Node<T> *p = first();
        while (r--)
            p = p->succ;
        return insertB(p, e);
    }
    Node<T> *insertAsFirst(const T &e)
    {
        _size++;
        return first()->insertAsPred(e);
    }
    Node<T> *insertAsLast(const T &e)
    {
        _size++;
        return last()->insertAsSucc(e);
    }
    Node<T> *insertA(Node<T> *p, const T &e)
    {
        _size++;
        return p->insertAsSucc(e);
    }
    Node<T> *insertB(Node<T> *p, const T &e)
    {
        _size++;
        return p->insertAsPred(e);
    }
    T remove(Node<T> *p)
    {
        T e = p->data;
        p->pred->succ = p->succ;
        p->succ->pred = p->pred;
        delete p;
        _size--;
        return e;
    }
    // 循秩访问接口
    T &operator[](Rank r)
    {
        Node<T> *p = first();
        while (r--)
            p = p->succ;
        T &e = p->data;
        return e;
    }
    void duplicate()
    {
        for (Node<T> *p = first()->succ; p != trailer;) {
            Node<T> *next = p->succ;
            if (find(p->data, first(), p)) remove(p);
            p = next;
        }
    }
    void uniquify()
    {
        if (size() < 2) return;
        for (Node<T> *i = first(), *j = first()->succ; j != trailer;) {
            if (i->data == j->data) {
                j = j->succ;
                remove(j->pred);
            } else {
                i = j;
                j = j->succ;
            }
        }
    }

    void sort()
    {
        switch (rand() % 3) {
        case 0:
            printf("选择排序\n");
            selectSort();
            break;
        case 1:
            printf("插入排序\n");
            insertSort();
            break;
        case 2:
            printf("归并排序\n");
            mergeSort(first(), trailer);
            break;
        }
    }

    // 遍历
    void traverse(void (*visit)(T &))
    {
        for (Node<T> *p = first(); p != trailer; p = p->succ)
            visit(p->data);
    }
    template <typename VST>
    void traverse(VST &visit)
    {
        for (Node<T> *p = first(); p != trailer; p = p->succ)
            visit(p->data);
    }
};
#endif;