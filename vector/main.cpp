#include "vector.h"
#include <iostream>

using namespace std;

int main(){
    Vector<int> test(5, 5);
    while(true){
        for(int i = 0; i < 25000000; i ++){
            test.insert(i);
        }
        for(int i = 0; i < 25000000; i ++){
            test.remove(test.size() - 1);
        }
        cout << test.size() << endl;
    }
    return 0;
}