#pragma once

#include <string.h>
#include <stdlib.h>
#include <assert.h>
typedef int Rank;
#define DEFAULT_CAPACITY 3

template <typename T> class Vector{
public:
    Vector();
    Vector(int, T);
    Vector(const Vector<T> &from);
    Vector<T> & operator=(const Vector<T> &from);
    ~Vector();
    int size(){ return _size;}
    T &operator[](Rank r); // 循秩访问
    Rank insert(Rank r, T e); // 插入
    Rank insert(T e); // 作为末尾元素插入
    Rank remove(Rank lo, Rank hi); // 删除[lo, hi)区间的元素
    T remove(Rank r); // 删除秩为r的元素
    Rank find(T e); // 无序，返回等于e的最大元素，如果没有返回-1
private:
    int _size;
    int _capacity;
    T *_elem;
    void expand(); // 成倍增长，降低分摊时间
    void shrink(); // 缩水
};
template <typename T> Vector<T>::Vector() {
    _capacity = DEFAULT_CAPACITY;
    _elem = new T[_capacity];
    _size = 0;
}
template <typename T> Vector<T>::Vector(int size, T e):_elem(nullptr), _capacity(0),  _size(0){
    _capacity = 2 * size;
    _elem = new T[_capacity];
    memset(_elem, 0, sizeof(T) * _capacity);
    for(int i = 0; i < size; i ++)_elem[_size++] = e;
}
template <typename T> Vector<T>::Vector(const Vector<T> &from){
    _size = from._size;
    _capacity = 2 * _size;
    _elem = new T[_capacity];
    memcpy(_elem, from._elem, sizeof(T) * _size);
}
template <typename T> Vector<T> &Vector<T>::operator=(const Vector<T> &from){
    if(_elem)delete []_elem;
    _size = from._size;
    _capacity = 2 * _size;
    _elem = new T[_capacity];
    memcpy(_elem, from._elem, sizeof(T) * _size);
}
template <typename T> Vector<T>::~Vector() {
    delete []_elem;
}
template <typename T> void Vector<T>::expand(){
    _capacity *= 2;
    T *new_elem = new T[_capacity];
    memcpy(new_elem, _elem, _size);
    delete[] _elem;
    _elem = new_elem;
}
template <typename T> T &Vector<T>::operator[](Rank r) {
    assert(0 <= r && r < _size);
    return _elem[r];
}
template <typename T> Rank Vector<T>::insert(Rank r, T e) {
    assert(0 <= r && r <= _size);
    memmove(_elem + r + 1, _elem + r, sizeof(T) * _size);
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
    assert(lo <= hi);
    memmove(_elem + lo, _elem + hi, sizeof(T) * (_size - hi));
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
    _capacity = 2 * _size;
    T *new_elem = new T[_capacity];
    memcpy(new_elem, _elem, sizeof(T) * _size);
    delete []_elem;
    _elem = new_elem;
}
template <typename T> Rank Vector<T>::find(T e) {
    Rank r = _size - 1;
    for(; 0 <= r; r--){
        if(_elem[r] == e)return r;
    }
    return r;
}

