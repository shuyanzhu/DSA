#ifndef MYLIST
#define MYLIST

#include <stdio.h>
#include<stdlib.h>
typedef int Rank;


template<typename T>
class Node {
  public:
	T data; Node<T> *pred; Node<T> *succ;

	// 构造函数
	Node() :data(0), pred(NULL), succ(NULL) {}
	Node(T e, Node<T> *p = NULL, Node<T> *s = NULL) :data(e), pred(p), succ(s) {}

	// 操作接口: 插入作为前驱或后继
	Node<T> *insertAsPred(const T &e) {
		Node<T> *x = new Node(e, pred, this);
		pred->succ = x; pred = x;
		return x;
	}
	Node<T> *insertAsSucc(const T &e) {
		Node<T> *x = new Node(e, this, succ);
		succ->pred = x; succ = x;
		return x;
	}
};

// 主要有插入/删除，查找，唯一化,排序和遍历
template<typename T>
class List {
protected:
	int _size; Node<T> *header; Node<T> *trailer;
    // 初始化函数复用
    void init() ;
    void copyNodes(Node<T> *p, int n) { init(); while (n--) { insertAsLast(p->data); p = p->succ; } }
    void swap(Node<T> *a, Node<T> *b) ;

public:
    // 通用接口
    List();
	List(const List<T> &L) ;
	List(const List<T> &L, Rank r, int n) ;
	List(Node<T> *begin, Node<T> *end) ;
	~List() ;
	bool empty()const { return header->succ == trailer; }
	Rank size()const { return _size; }
	// 访问
    T &operator[](Rank r) ;
	Node<T> *first()const { return header->succ; }
    Node<T> *last() const { return trailer->pred; }
	bool valid(Node<T> *p) { return (p != NULL) && (p != header) && (p != trailer); }
	// 查
    Node<T> *find(const T &e) ;
    Node<T> *find(const T &e, Node<T> *begin, Node<T> *end) ;
    // 增
	Node<T> *insert(Rank r, const T &e) ;
	Node<T> *insertAsFirst(const T &e) ;
	Node<T> *insertAsLast(const T &e) ;
	Node<T> *insertA(Node<T> *p, const T &e) { _size++; return p->insertAsSucc(e); }
	Node<T> *insertB(Node<T> *p, const T &e) { _size++; return p->insertAsPred(e); }
	// 删
	T  remove(Node<T> *p) ;
    void deduplicate() ;
    // 遍历
    template <typename VST> void traverse(VST &visit) ;


	// 有序列表接口
	// 排序函数,选择排序总是n2，插入排序最好有线性时间复杂度
    int disordered() ;
    void permute(Node<T> *begin, Node<T> *end);
    void sort() ;
	Node<T> *selectMax(Node<T> *p, int n) ;
	void selectSort() ;
	void merge(Node<T> *begin, Node<T> *mi, Node<T> *end) ;
	void mergeSort(Node<T> *begin, Node<T> *end) ;
	// 实现得不好，暂时这样实现
	void insertSort() ;
	void uniquify() ;
    Node<T> *search(T &e, Node<T> *begin, Node<T> *end) ;
};
template <typename T> List<T>::List() {
    init();
}

template <typename T> void List<T>::init() {
    header = new Node<T>;
    trailer = new Node<T>;
    header->succ = trailer; trailer->pred = header;
	_size = 0;
}

template <typename T> void List<T>::swap(Node<T> *a, Node<T> *b) {
    T e = a->data;
    a->data = b->data;
    b->data = e;
}

template <typename T> Node<T> *List<T>::selectMax(Node<T> *p, int n) {
    Node<T> *max = p;
    for (; n--; p = p->succ) if (max->data <= p->data)max = p;
    return max;
}

template <typename T> void List<T>::selectSort() {
    int size = _size;
    for (Node<T> *p = last(); p != first(); p = p->pred) {
        Node<T> *max = selectMax(first(), size--);
        swap(max, p);
    }
}
template <typename T> void List<T>::merge(Node<T> *begin, Node<T> *mi, Node<T> *end) {
    List L(begin, mi);
    Node<T> *i = L.first(), *j = mi, *k = begin;
    for (; (i != L.last()->succ) || (j != end);) {
        if ((i != L.last()->succ) && (!(j != end) || (i->data <= j->data))) { k->data = i->data; k = k->succ; i = i->succ; }
        if ((j != end) && (!(i != L.last()->succ) || (j->data < i->data))) { k->data = j->data; k = k->succ; j = j->succ; }
    }
}
template <typename T> void List<T>::mergeSort(Node<T> *begin, Node<T> *end) {
    if (begin->succ == end)return;
    if (begin == end)return;
    //Node<T> *i = begin, *j = end;
    //for (; !((i->succ == j) || (i == j)); i = i->succ, j = j->pred);
    //Node<T> *mi = i;
    int i = 0; Node<T> *mi = begin;
    for (i = 0; mi != end; i++)mi = mi->succ;
    for (i = i >> 1; i > 0;i--)mi = mi->pred;
    mergeSort(begin, mi);
    mergeSort(mi, end);
    merge(begin, mi, end);
}
template <typename T> void List<T>::insertSort() {
    for (Node<T> *p = first()->succ; p != trailer; ) {
        Node<T> *x = search(p->data, first(), p);
        insertA(x, p->data);
        p = p->succ;
        remove(p->pred);
    }
}
template <typename T> List<T>::List(const List<T> &L) {
    init();
    for (Node<T> *p = L.first(); !L.empty(); p = p->succ) {
        insertAsLast(p->data);
        if (p == L.last())break;
    }
}
template <typename T> List<T>::List(const List<T> &L, Rank r, int n) {
    Node<T> *p = L.first();
    for (int i = 0; i < r; i++) p = p->succ;  // 第r+1个元素
    copyNodes(p, n);
}
template <typename T> List<T>::List(Node<T> *begin, Node<T> *end) {
    init();
    for (Node<T> *p = begin; p != end; p = p->succ)insertAsLast(p->data);
}
template <typename T> List<T>::~List() {
    while (!empty())remove(first());
    delete header; delete trailer;
}
template <typename T> int List<T>::disordered() {
    if (empty())return -1;
    Node<T> *p = first()->succ;
    int n;
    for (n = 0; p != trailer; p = p->succ) {
        if (p->pred->data > p->data)n++;
    }
    return n;
}
template <typename T> Node<T> *List<T>::find(const T &e) {
    Node<T> *p = first();
    for (int i = 0; i < _size; i++, p = p->succ)
        if (p->data == e)return p;
    return NULL;
}
template <typename T> Node<T> *List<T>::find(const T &e, Node<T> *begin, Node<T> *end) {
    for (Node<T> *p = begin; p != end; p = p->succ)
        if (p->data == e)return p;
    return NULL;
}
template <typename T> Node<T> *List<T>::insert(Rank r, const T &e) {
    Node<T> *p = first();
    while (r--) p = p->succ;
    return insertB(p, e);
}
template <typename T> Node<T> *List<T>::insertAsFirst(const T &e) {
    _size++;
    return first()->insertAsPred(e);
}
template <typename T> Node<T> *List<T>::insertAsLast(const T &e) {
    _size++;
    return last()->insertAsSucc(e);
}
template <typename T> T List<T>::remove(Node<T> *p) {
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p; _size--;
    return e;
}
template <typename T> T &List<T>::operator[](Rank r) {
    Node<T> *p = first();
    while (r--)p = p->succ;
    T &e = p->data;
    return e;
}
template <typename T> void List<T>::deduplicate() {
    for (Node<T> *p = first()->succ; p != trailer; ) {
        Node<T> *next = p->succ;
        if (find(p->data, first(), p)) remove(p);
        p = next;
    }
}
template <typename T> void List<T>::uniquify() {
    if (size() < 2)return;
    for (Node<T> *i = first(), *j = first()->succ; j != trailer;) {
        if (i->data == j->data) { j = j->succ; remove(j->pred); }
        else { i = j; j = j->succ; }
    }
}
template <typename T> void List<T>::sort() {
    switch (rand() % 3) {
        case 0:printf("选择排序\n"); selectSort();  break;
        case 1:printf("插入排序\n"); insertSort();  break;
        case 2:printf("归并排序\n"); mergeSort(first(), trailer);  break;
    }
}
template <typename T> template <typename VST> void List<T>::traverse(VST &visit) {
    for (Node<T> *p = first(); p != trailer; p = p->succ)
        visit(p->data);
}
template <typename T> void List<T>::permute(Node<T> *begin, Node<T> *end) {
    int n = 0;
    for (Node<T> *p = begin; p != end; p = p->succ)n++;
    for(Node<T> *p = end->pred; p != begin; p = p->pred){
        Node<T> *q = begin;
        n--;
        for(int r = 0; r < rand() % n; r++){
            q = q->succ;
        }
        swap(p, q);
    }
}
template <typename T> Node<T> *List<T>::search(T &e, Node<T> *begin, Node<T> *end) {
    if (begin == end)return NULL;
    Node<T> *p = end->pred;
    for (; p != begin->pred; p = p->pred)
        if (p->data <= e) return p;
    return begin->pred;
}
#endif