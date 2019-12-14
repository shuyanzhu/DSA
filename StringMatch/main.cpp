//
// Created by zhuhu on 2019/7/18.
//
#include <iostream>
#include "string.h"
using namespace std;
char *bf1_match(char *T, char *P){
    int n = strlen(T), m = strlen(P), i = 0, j = 0;
    while(j < m && i < n){
        if(T[i] == P[j]){ // 匹配，i,j同时右移
            i++;
            j++;
        } else{
            i -= j - 1;
            j = 0;
        }
    }
    if(j == m)return &T[i - j];
    else return NULL;
}
char *buildNext(char *P, char *next){
    int m = strlen(P), j = 0;
    memset(next, 0, m);
    int t = next[0] = -1;
    while(j < m - 1){
        if(t < 0 || P[j] == P[t]){
            j++; t++;
            next[j] = P[t] != P[j] ? t : next[t]; // 改进后的方法
        } else{
            next[j] = t;
        }
    }
}
char *KMP_match(char *T, char *P){
    int n = strlen(T), m = strlen(P), i = 0, j = 0;
    auto next = new char[m];
    buildNext(P, next);
    while(j < m && i < n){
        if(j < 0 || T[i] == P[j]){
            i++; j++;
        } else{
            j = next[j];
        }
    }
    if(j == m)return &T[i - j];
    else return NULL;
}

int main(){

    return  0;
}

