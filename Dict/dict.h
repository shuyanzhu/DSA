//
// Created by zhuhu on 2019/7/15.
//

#ifndef DSA_DICT_H
#define DSA_DICT_H
template <typename K, typename V> struct Dict{
    virtual int size() const = 0;
    virtual bool put(K k, V v) = 0;
    virtual V *get(K k) = 0;
    virtual bool remove(K k) = 0;
};
#endif //DSA_DICT_H
