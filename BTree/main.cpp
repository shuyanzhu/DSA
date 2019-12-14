//
// Created by zhuhu on 2019/7/11.
//

#include "iostream"
#include "btree.h"
#include "time.h"
//#include "windows.h"
#include "stdlib.h"

int main(){
    BTree<int> t(5);
    clock_t start = clock();
    for(int i = 0; i < 100000; i++)
        t.insert(i);
    for(int i = 0; i < 50000000; i++)
        t.remove(i);
    clock_t end = clock();
    std::cout << t.size() << std::endl << end - start << std::endl << debug_size << std::endl;
    getchar();
    return 0;
}