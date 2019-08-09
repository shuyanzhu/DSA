//
// Created by zhuhu on 2019/7/20.
//

#ifndef DSA_UTILS_H
#define DSA_UTILS_H
#include "../vector/vector.h"
#include "../PriorityQueue/PQ_ComplHeap.h"
/*
 * 1. 求取一个向量中出现次数超过一半的树（最多, 如果没有超过一半——哈希）
 * 2. 求取两个有序向量合并后的中位数
 * 3. Top-k选取: <堆选取> <快速选取> [线性选取]
 */
// 求得向量中出现次数超过一半的元素(没有返回false)

template <typename T> bool majority(Vector<T> A, T &maj);
template <typename T> bool majCheck(Vector<T> A, T maj);
template <typename T> T majCandidate(Vector<T> A);

// 归并两个有序向量获得其中位数, 蛮力算法
template <typename T> T trivialMedian(Vector<T> &S1, int lo1, int n1, Vector<T> &S2, int lo2, int n2);
// 找到归并两个任意长度的有序向量后的中位数
// 目前为止处理的较为复杂的辩解情况之一
template <typename T> T median(Vector<T> &S1, int lo1, int n1, Vector<T> &S2, int lo2, int n2);

// 构建大小为k的堆，然后插入n-k个数，每插入一个删除一次堆顶
template <typename T> T heapTopk(T *A, Rank n, Rank k);

// 快速选取，类似快速排序, （尾）递归实现
template <typename T> T quickTopk(T *A, Rank n, Rank k);
// 快速选取，针对向量，迭代实现。无论哪种实现子向量规模都会严格减小，直到平凡情况
template <typename T> void quickTopk(Vector<T> &A, Rank k);

// 线性选取，常系数复杂度较高，不实用

template <typename T> bool majCheck(Vector<T> A, T maj){
    int occurance = 0;
    for (int i = 0; i < A.size(); i++)
        if(A[i] == maj)
            occurance ++;
    return 2 * occurance > A.size();
}
template <typename T> T majCandidate(Vector<T> A){
    T maj;
    int c = 0;
    for(int i = 0; i < A.size(); i++){
        if(0 == c){
            maj = A[i]; c = 1;
        } else{
            maj == A[i] ? c++ : c--;
        }
    }
    return maj;
}
template <typename T> bool majority(Vector<T> A, T &maj){
    maj = majCandidate(A);
    return majCheck(A, maj);
}

template <typename T> T trivialMedian(Vector<T> &S1, int lo1, int n1, Vector<T> &S2, int lo2, int n2){
    Vector<T> S;
    int i = 0, j = 0;
    while(i < n1 || j < n2){
        while(j >= n2 || (i < n1 && S1[lo1 + i] <= S2[lo2 + j]))S.insert(S1[lo1 + i++]);
        while(i >= n1 || (j < n2 && S1[lo1 + i] > S2[lo2 + j]))S.insert(S2[lo2 + j++]);
    }
    return S[(n1 + n2) / 2];
}
template <typename T> T median(Vector<T> &S1, int lo1, int n1, Vector<T> &S2, int lo2, int n2){
    if(n1 > n2)
        return median(S2, lo2, n2, S1, lo1, n1);
    if(n2 <= 5)
        return trivialMedian(S1, lo1, n1, S2, lo2, n2); // 不重要的平凡情况

    if(2 * n1 < n2)
        return median(S1, lo1, n1, S2, lo2 + (n2 - n1 - 1) / 2, n2 - (n2 - n1 - 1) / 2 * 2 );

    int m1 = lo1 + n1 / 2;
    int mib = lo2 + (n1 - 1) / 2;
    int mia = lo2 + n2 - 1 - n1 / 2;

    if(S1[m1] < S2[mib])
        return median(S1, m1, n1 - n1 / 2, S2, lo2, n2 - n1 / 2);
    else if(S2[mia] <  S1[m1])
        return median(S1, lo1, n1 - (n1 - 1) / 2, S2, mia, n2 - (n1 - 1) / 2);
    else
        return median(S1, lo1, n1, S2, mia, n2 - (n1 - 1) / 2 * 2);
}

template <typename T> T heapTopk(T *A, Rank n, Rank k){
    PQ_ComplHeap<T> heap(A, k);
    for(int i = 0; i < n - k; i++){
        heap.insert(A[i + k]);
        heap.delMax();
    }
    return heap.getMax();
}
template <typename T> T quickTopk(T *A, Rank n, Rank k){
    int key = A[0];
    int i = 0, j = n - 1;
    while(i != j){
        while(i != j && A[j] >= key) j--;
        A[i] = A[j];
        while(i != j && A[i++] <= key) i++;
        A[j] = A[i];
    }
    A[i] = key;
    if(k < i + 1) // 向下分解，也包含必然的递归基
        quickTopk(A, i, k);
    else if(i + 1 < k)
        quickTopk(&A[i + 1]. n - i - 1, k - i - 1);
    else
        return A[i];
}
template <typename T> void quickTopk(Vector<T> &A, Rank k){ // 双分支递归，包含空的递归基
    for(int lo = 0, hi = A.size() - 1; lo < hi;){
        int key = A[lo];
        int i = 0, j = hi;
        while(i != j){
            while(i != j && A[j] >= key) j--;
            A[i] = A[j];
            while(i != j && A[i++] <= key) i++;
            A[j] = A[i];
        }
        A[i] = key;
        (k < i + 1) ? (hi = i - 1) : (lo = i + 1); // 类似二分查找中的操作，减少比较次数
//        if(k < i + 1) hi = i - 1;
//        if(i + 1 < k) lo = i + 1;
//        else break; // i + 1 == k. A[i]即为第k个元素
    }
}
#endif //DSA_UTILS_H
