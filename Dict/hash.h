//
// Created by zhuhu on 2019/7/15.
//

#ifndef DSA_HASH_H
#define DSA_HASH_H

#include "dict.h"
#include "../_share/Entry.h"
#include "../Bitmap/bitmap.h"
#include "string.h"
static size_t hashCode ( char c ) { return ( size_t ) c; } //字符
static size_t hashCode ( int k ) { return ( size_t ) k; } //整数以及长长整数
static size_t hashCode ( long long i ) { return ( size_t ) ( ( i >> 32 ) + ( int ) i ); }
static size_t hashCode ( char s[] ) { //生成字符串的循环移位散列码（cyclic shift hash code）
    int h = 0; //散列码
    for ( size_t n = strlen ( s ), i = 0; i < n; i++ ) //自左向右，逐个处理每一字符
    { h = ( h << 5 ) | ( h >> 27 ); h += ( int ) s[i]; } //散列码循环左移5位，再累加当前字符
    return ( size_t ) h; //如此所得的散列码，实际上可理解为近似的“多项式散列码”
} //对于英语单词，"循环左移5位"是实验统计得出的最佳值
int primeNLT ( int c, int n, char* file ) { //根据file文件中的记录，在[c, n)内取最小的素数
    Bitmap B ( file, n ); //file已经按位图格式，记录了n以内的所有素数，因此只要
    while ( c < n ) //从c开始，逐位地
        if ( B.test ( c ) ) c++; //测试，即可
        else return c; //返回首个发现的素数
    return c; //若没有这样的素数，返回n（实用中不能如此简化处理）
}
template <typename K, typename V>
class HashTable: public Dict<K, V>{
private:
    Entry<K, V> **ht; // bucket array
    int M; // bucket size
    int N; // entries number
    Bitmap *layyRemoval; // lazy delete mark
protected:
    int probe4Hit(const K &k); // confict search
    int probe4Free(const K &k);  // empty bucket
    void rehash(); // rehash algorithm, guarantee hashtale size
public:
    HashTable(int c = 5);
    ~HashTable();
    int size(){ return N; }
    bool put(K k, V v); // insert
    V *get(K k); // search
    bool remove(K k); // remove an entry
};

template <typename K, typename V> HashTable<K, V>::HashTable(int c) {
    M = primeNLT(c, 1048576, "prime-1048576-bitmap.txt");
    N = 0;
    ht = new Entry<K, V> *[M];
    memset(ht, 0, sizeof(Entry<K, V> *) * M);
    layyRemoval = new Bitmap(M);
}
template <typename K, typename V> HashTable<K, V>::~HashTable() {
    for(int i = 0; i < M; i++)
        delete ht[i];
    delete ht;
    delete(layyRemoval);
}
template <typename K, typename V> int HashTable<K, V>::probe4Hit(const K &k) {
    int r = hashCode(k) % M;
    while((ht[r] && (k != ht[r]->key)) || (!ht[r] && layyRemoval->test(r)))
        r = (r + 1) % M;
    return r;
}
template <typename K, typename V> V* HashTable<K, V>::get(K k) {
    int r = probe4Hit(k);
    return ht[r] ? &(ht[r]->value) : NULL;
}
template <typename K, typename V> bool HashTable<K, V>::remove(K k) {
    int r = probe4Hit(k); if(!ht[r]) return false;
    release(ht[r]); ht[r] = NULL;
    layyRemoval->set(r);
    N--;
    return true;
}
template <typename K, typename V> bool HashTable<K, V>::put(K k, V v) {
    int r = probe4Free(k); if(ht[r]) return false; // 一定能够找到空桶
    auto p = new Entry<K, V>(k, v);
    ht[r] = p;
    N++;
    if(N * 2 > M)rehash(); // 装填因子过高则重新哈希
    return true;
}
template <typename K, typename V> int HashTable<K, V>::probe4Free(const K &k) {
    int r = hashCode(k);
    while(ht[r] && ht[r] != k)
        r = (r + 1) / M;
    return r;
}
template <typename K, typename V> void HashTable<K, V>::rehash() {
    int old_ca = M; Entry<K, V> **old_ht = ht;
    M = primeNLT(2 * M, 1048576, "prime-1048576-bitmap.txt");
    ht = new Entry<K, V> *[M]; memset(ht,0 , sizeof(Entry<K, V> *) *M);
    release(layyRemoval); layyRemoval = new Bitmap(M);
//    memcpy(ht, old_ht, sizeof(void *) * M); 不能这样
    N = 0;
    for(int i = 0; i < old_ca; i++)
        if(old_ht[i])
            put(old_ht[i]->key, old_ht[i]->value);
    delete old_ht;
}
#endif //DSA_HASH_H
