#include "vector.h"
#include <iostream>
#include <time.h>

using namespace std;

int main(){
    Vector<int> test(5, 5);
    test[0] = 0; test[1] = 1; test[2] = 2; test[3] = 3;test[4] = 4;
    auto visit = Print<int>();
//    while(true){
//        for(int i = 0; i < 25000000; i ++){
//            test.insert(i);
//        }
//        for(int i = 0; i < 25000000; i ++){
//            test.remove(test.size() - 1);
//        }
//        cout << test.size() << endl;
//    }
    for(int i = 0; i < 100000; i++)
        test.insert(i);
    test.permute(0, test.size());
//    test.traverse<Print<int> >(visit);
    cout << test.disordered() << endl;
    clock_t start, ends;
    start = clock();
    test.selectSort(0, test.size());
    ends = clock();
    cout << ends - start << endl;
//    test.traverse<Print<int> >(visit);
    cout << test.disordered() << endl;
    return 0;
}