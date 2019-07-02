#pragma once

#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
/****************
 * 写代码的
 *
 * **************/
typedef int Rank;
#define DEFAULT_CAPACITY 3
template <typename T> void swap(T &a, T &b){
    T tmp = a;
    a = b;
    b = tmp;
}

template <typename T> class Vector{
public:
    // 通用接口
    Vector();
    Vector(int, T);
    Vector(const Vector<T> &from);
    Vector<T> & operator=(const Vector<T> &from);
    ~Vector();

    virtual int size(){ return _size;}
    T &operator[](Rank r)const; // 循秩访问
    Rank insert(Rank r, T e); // 插入
    Rank insert(T e); // 作为末尾元素插入
    Rank remove(Rank lo, Rank hi); // 删除[lo, hi)区间的元素
    T remove(Rank r); // 删除秩为r的元素
    Rank find(T e) const; // 无序，返回等于e的最大元素，如果没有返回-1
    Rank find(T e, Rank lo, Rank hi) const;
    int deduplicate();
    void traverse(void (*visit)(T &));
    template <typename VST> void traverse(VST &visit);

    // 有序接口
    int disordered();
    int uniquify();
    Rank search(Rank lo, Rank hi, T e);
    void permute(Rank lo, Rank hi);
    void sort(Rank lo, Rank hi);
    void bubbleSort(Rank lo, Rank hi);
    void insertSort(Rank lo, Rank hi); // 相比冒泡排序交换次数变少
    void selectSort(Rank lo, Rank hi);
    void mergeSort(Rank lo, Rank hi);
    void quickSort(Rank lo, Rank hi);


protected:
    int _size;
    int _capacity;
    T *_elem;
    void expand(); // 成倍增长，降低分摊时间
    void shrink(); // 缩水
    bool bubble(Rank lo, Rank hi); // 冒泡排序一趟
};
template <typename T> Vector<T>::Vector() {
    _capacity = DEFAULT_CAPACITY;
    _elem = new T[_capacity];
    _size = 0;
}
template <typename T> Vector<T>::Vector(int size, T e):_elem(nullptr), _capacity(0),  _size(0){
    _capacity = 2 * size;
    _elem = new T[_capacity];
//    memset(_elem, 0, sizeof(T) * _capacity);
    for(int i = 0; i < size; i ++)_elem[_size++] = e;
}
template <typename T> Vector<T>::Vector(const Vector<T> &from){
    _size = from._size;
    _capacity = 2 * _size;
    _elem = new T[_capacity];
//    memcpy(_elem, from._elem, sizeof(T) * _size);
    for(int i = 0; i < _size; i++)_elem[i] = from._elem[i];
}
template <typename T> Vector<T> &Vector<T>::operator=(const Vector<T> &from){
    if(_elem)delete []_elem;
    _size = from._size;
    _capacity = 2 * _size;
    _elem = new T[_capacity];
//    memcpy(_elem, from._elem, sizeof(T) * _size);
    for(int i = 0; i < _size; i++)_elem[i] = from._elem[i];
}
template <typename T> Vector<T>::~Vector() {
    delete []_elem;
}
template <typename T> void Vector<T>::expand(){
    _capacity *= 2;
    T *new_elem = new T[_capacity];
//    memcpy(new_elem, _elem, sizeof(T) * _size);
    for(int i = 0; i < _size; i++)new_elem[i] = _elem[i];
    delete[] _elem;
    _elem = new_elem;
}
template <typename T> T &Vector<T>::operator[](Rank r) const {
    assert(0 <= r && r < _size);
    return _elem[r];
}
template <typename T> Rank Vector<T>::insert(Rank r, T e) {
    assert(0 <= r && r <= _size);
//    memmove(_elem + r + 1, _elem + r, sizeof(T) * _size);
    for(int i = _size; i > r; r--)_elem[i] = _elem[i-1];
    _elem[r] = e;
    _size ++;
    if(_size == _capacity)expand();
    return r;
}
template <typename T> Rank Vector<T>::insert(T e) {
    _elem[_size++] = e;
    if(_size == _capacity)expand();
    return _size - 1;
}
template <typename T> Rank Vector<T>::remove(Rank lo, Rank hi) {
    assert(0 <= lo && lo <= _size);
    assert(0 <= hi && hi <= _size);
    assert(lo < hi);
//    memmove(_elem + lo, _elem + hi, sizeof(T) * (_size - hi));
    for(int i = 0; i < (_size - hi); i++)_elem[lo + i] = _elem[hi + i];
    _size -= (hi - lo);
    if(_size * 4 < _capacity)shrink();
    return hi - lo;
}
template <typename T> T Vector<T>::remove(Rank r) {
    T e = _elem[r];
    remove(r, r+1);
    return e;
}
template <typename T> void Vector<T>::shrink() {
    if (_size == 0)_capacity = DEFAULT_CAPACITY;
    else
        _capacity = 2 * _size;
    T *new_elem = new T[_capacity];
//    memcpy(new_elem, _elem, sizeof(T) * _size); // 有问题!!! 不能保证深拷贝
    for(int i = 0; i < _size; i++)new_elem[i] = _elem[i];
    delete []_elem;
    _elem = new_elem;
}
template <typename T> Rank Vector<T>::find(T e) const{
    Rank r = _size - 1;
    for(; 0 <= r; r--){
        if(_elem[r] == e)return r;
    }
    return r;
}
template <typename T> Rank Vector<T>::find(T e, Rank lo, Rank hi) const{
    assert(0 <= lo && lo <= _size);
    assert(0 <= hi && hi <= _size);
    while((lo < hi--) && (e != _elem[hi]));
    return hi;
}
template <typename T> int Vector<T>::deduplicate() {
    int oldSize = _size;
    Rank i = 1;
    while(i < _size){
        find(_elem[i], 0, i) == -1 ? i ++ : remove(i);
    }
    return oldSize - _size;
}
template <typename T> void Vector<T>::traverse(void (*visit)(T &)) {
    for(int i = 0; i < _size; i++)
        visit(_elem[i]);
}
template <typename T> template <typename VST> void Vector<T>::traverse(VST &visit) {
    for(int i = 0; i < _size; i++)
        visit(_elem[i]);
}
template <typename T> int Vector<T>::disordered() {
    int n = 0;
    for(Rank r = 1; r < _size; r++){
        if(_elem[r-1] > _elem[r]) n++;
    }
    return n;
}
template <typename T> int Vector<T>::uniquify() {
    int i = 0, j = 1;
    for(; j < _size; j++){
        if(_elem[i] != _elem[j])_elem[++i] = _elem[j];
    }
    _size = ++i;
    if(_size * 4 < _capacity)shrink();
    return j - i;
}
template <typename T> Rank Vector<T>::search(Rank lo, Rank hi, T e) {
    while(lo < hi){
        int mi = (lo + hi) >> 1;
        _elem[mi] <= e ? lo = mi + 1 : hi = mi;
    }
    return --lo;
}
template <typename T> void Vector<T>::permute(Rank lo, Rank hi) {
    T * V = _elem + lo;
    for (Rank i = hi - lo; i > 0; i--)
        swap(V[i-1], V[rand() % i]);
}
template <typename T> void Vector<T>::sort(Rank lo, Rank hi) {
    switch (rand() % 5){
        case 0: bubbleSort(lo, hi);break;
        case 1: selectSort(lo, hi);break;
        case 2: insertSort(lo, hi);break;
        case 3: mergeSort(lo, hi);break;
        case 4: quickSort(lo, hi);break;
    }
}
template <typename T> void Vector<T>::bubbleSort(Rank lo, Rank hi){
    while(!bubble(lo, hi--));
}
template <typename T> bool Vector<T>::bubble(Rank lo, Rank hi) {
    bool sorted = true;
    for(int i = lo + 1; i < hi ; i++){
        if(_elem[i-1] > _elem[i]){
            swap<T>(_elem[i-1], _elem[i]);
            sorted = false;
        }
    }
    return sorted;
}
template <typename T> void Vector<T>::selectSort(Rank lo, Rank hi) {
    while(lo < hi--){
        T m = _elem[hi]; Rank r = hi;
        for(int i = hi - 1; i > -1; i--){
            if(_elem[i] > m){
                m = _elem[i];
                r = i;
            }
        }
        swap(_elem[hi], _elem[r]);
    }
}
template <typename T> void Vector<T>::insertSort(Rank lo, Rank hi) {
    for(int i = ++lo; i < hi; i++){
        T tmp = _elem[i];
        Rank j = i;
        for(; j > -1 && _elem[--j] > tmp;);
//        memmove(_elem+j+2, _elem+j+1, sizeof(T) * (i - j -1));
        for(int k = i; k > j+1; k--)_elem[k] = _elem[k-1];
        _elem[j+1] = tmp;
    }
}
template <typename T> void Vector<T>::quickSort(Rank lo, Rank hi) {
    if (lo + 1 >= hi)
        return;
    T flag = _elem[lo];
    int i = lo, j = hi - 1;
    while(i != j){
        while(i !=j && flag <= _elem[j])j--; // <=号，避免条件过强时i,j包含的值可能在两边颠倒，使用<需要i++,勤于交换
        _elem[i] = _elem[j];
        while (i != j && _elem[i] <= flag)i++;
        _elem[j] = _elem[i];
    }
    _elem[i] = flag;
    quickSort(lo, i);
    quickSort(i+1, hi);
}
template <typename T> void Vector<T>::mergeSort(Rank lo, Rank hi) {
    assert(0 <= lo && lo < hi && hi <= _size);
    if(lo + 1 == hi)return;
    int mi = (lo + hi) >> 1;
    mergeSort(lo, mi);
    mergeSort(mi, hi);

    // merge
    T *A = new T[mi - lo];
//    memcpy(A, _elem + lo, sizeof(T) * (mi - lo));
    for (int i = 0; i < mi - lo;i++)A[i] = _elem[lo+i];
    int i = 0, j = mi, k = lo; // 在数组A中，在_elem大端，前两者比较后存放的位置
    while(true){
        if((i + lo) != mi && j != hi){
            if(A[i] < _elem[j])_elem[k++] = A[i++];
            else _elem[k++] = _elem[j++];
        } else if(i + lo == mi){
            break;
        } else{
            for(; k < hi; )_elem[k++] = A[i++];
            break;
        }
    }
    delete []A;
}
// 遍历类
template <typename T> class Print{
public:
    void operator()(int e){std::cout << e << std::endl;}
};
