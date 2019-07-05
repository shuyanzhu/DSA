//
// Created by zhuhu on 2019/7/5.
//
#include "iostream"
#include <vector>
#include "PFC.h"

using namespace std;

void print(){
    int length = probabilities.size();
    float probability = 0.0;
    for(int i = 0; i < length; i++){
        cout << char('A' + i) << ": " << probabilities[i] / sum << " ";
        probability += probabilities[i] / sum;
    }
    cout << endl << "probability: " << probability << endl;
}

int main(int argc, char *argv[]){
    print();
    auto forest = initForest();
    auto HuffTree = generateTree(forest);
    auto table = new PFCTable();
    auto code = new Bitmap();
    generateCT(code, 0, table, HuffTree->root());
    printTable(table);


    auto s = "ABFGJGF";
    auto n = encode(code, s, table);
    code->print(n);
    auto ret = decode(code, n, HuffTree);
    cout << endl << ret->size() << endl;
    for (auto iter = ret->begin(); iter != ret->end(); iter++){
        cout << *iter;
    }

    delete(forest);
    delete(HuffTree);
    delete(table);
    delete(code);
    return 0;
}

