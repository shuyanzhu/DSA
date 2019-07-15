//
// Created by zhuhu on 2019/7/15.
//

#ifndef DSA_ENTRY_H
#define DSA_ENTRY_H
template <typename K, typename V> struct Entry{
    K key; V value;
    Entry (K k = K(), V v = V()): key(k), value(v){}
    Entry (Entry<K, V> const &e): key(e.key), value(e.value){}
    bool operator< (Entry<K, V> const &e){ return key < e.key; }
    bool operator<= (Entry<K, V> const &e){ return key <= e.key; }
    bool operator> (Entry<K, V> const &e){ return key > e.key; }
    bool operator>= (Entry<K, V> const &e){ return key >= e.key; }
    bool operator== (Entry<K, V> const &e){ return key == e.key; }
    bool operator!= (Entry<K, V> const &e){ return key != e.key; }

};
#endif //DSA_ENTRY_H
