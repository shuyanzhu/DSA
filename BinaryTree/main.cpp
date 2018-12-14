#include <iostream>
#include <algorithm>
#include <stack>
#include "Btree_test.h"

using namespace std;

int main()
{
    BinNode<int> *p1 = new BinNode<int>(), *p2 = NULL;
    printf("%d\n", p1->data);
    return 0;
}