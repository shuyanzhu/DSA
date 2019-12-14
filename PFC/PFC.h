//
// Created by zhuhu on 2019/7/5.
//

#ifndef DSA_PFC_H
#define DSA_PFC_H
#include "vector"
#include "iostream"
std::vector<char> codes{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X','Y', 'Z'};
std::vector<int> probabilities {41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61, 91, 95, 42, 27, 36, 91, 4, 2, 53, 92, 82};
float sum = 1331.0;
struct HuffChar{
    char data;
    int probability;
    HuffChar(char code=' ', int probability=0):data(code), probability(probability){}
};
#include "../BinaryTree/BinTree.h"
typedef BinTree<HuffChar> PFCTree;

#include "../vector/vector.h"
typedef Vector<PFCTree *> PFCForest; // 这里的森林用List更好，因为长度需要经常变化（邓俊辉的做法）

// 邓俊辉
//#include "../Bitmap/bitmap.h"
//#include "../Skiplist/skiplist.h"
//typedef Skiplist<char, char *> PFCTable;
//
//PFCForest *initForest();
//PFCTree *generateTree(PFCForest *forest);
//void generateCT(Bitmap *code, int length, PFCTable *table, BinNode<char> *v);

#include "map"
#include "bitset"
#include "string"
#include "../Bitmap/bitmap.h"
typedef std::map<char, char *> PFCTable;
PFCForest *initForest();
PFCTree *generateTree(PFCForest *forest);
void generateCT(Bitmap *code, int length, PFCTable *table, BinNode<HuffChar> *v);
int encode(Bitmap *bincode, const char *input, PFCTable *table);
std::vector<char> *decode(Bitmap *code, int len, PFCTree *HuffTree);


int encode(Bitmap *bincode, const char *input, PFCTable *table){
    int len = 0;
    while(*input != '\0'){
        auto code2string = table->find(*input);
        if(code2string != table->end()){
            for(int i = 0; code2string->second[i] != 0; i++)
                ('1' == code2string->second[i]) ? bincode->set(len++) : bincode->clear(len++);
        }
        input ++;
    }
    return len;
}
std::vector<char> *decode(Bitmap *code, int len, PFCTree *HuffTree){
    auto ret = new std::vector<char>();
    auto node = HuffTree->root();
    for(int i = 0; i < len; i++){
        if(code->test(i)){
            node = node->rc;
        } else{
            node = node->lc;
        }
        if(IsLeadf(*node)){
            ret->insert(ret->end(), node->data.data);
            node = HuffTree->root();
        }
    }
    return ret;
}

PFCForest *initForest(){
    auto forest = new PFCForest;
    int length = probabilities.size();

    for (int i = 0; i < length; i++){
        auto tree = new PFCTree();
        tree->insertAsRoot(HuffChar(codes[i], probabilities[i]));
        forest->insert(tree);
    }
    return forest;
}
int selectMinFromForest(PFCForest *forest){
    int min = int(sum) + 2;
    int imin = 0;
    for(int i = 0; i < forest->size(); i++){
        if((*forest)[i]->root()->data.probability < min){
            min = (*forest)[i]->root()->data.probability;
            imin = i;
        }
    }
    return imin;
}
PFCTree *generateTree(PFCForest *forest){
    while(1 < forest->size()){
        auto min1 = selectMinFromForest(forest); auto pmin1 = (*forest)[min1];
        (*forest)[min1] = NULL; forest->remove(min1);
        auto min2 = selectMinFromForest(forest); auto pmin2 = (*forest)[min2];
        auto newTree = new PFCTree();
        newTree->insertAsRoot(HuffChar('^', pmin1->root()->data.probability + pmin2->root()->data.probability));
        newTree->attachAsRC(newTree->root(), pmin1);
        newTree->attachAsLC(newTree->root(), pmin2);
        (*forest)[min2] = newTree;
    }
    return (*forest)[0];
}
void generateCT(Bitmap *code, int length, PFCTable *table, BinNode<HuffChar> *v){
    if(IsLeadf(*v)){
        (*table)[v->data.data] = code->bits2string(length);
        return;
    }
    code->clear(length); generateCT(code, length+1, table, v->lc);
    code->set(length); generateCT(code, length+1, table, v->rc);
}
void printTable(PFCTable *table){
    for(auto iter = table->begin(); iter != table->end(); iter++){
        std::cout << iter->first << ": " << iter->second << std::endl;
    }
}

#endif //DSA_PFC_H
