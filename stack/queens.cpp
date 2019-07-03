//
// Created by zhuhu on 2019/7/1.
//
#include "mystack.h"
#include "iostream"
using namespace std;

struct Queen{
    int x, y;
    Queen(int x_ = 0, int y_ = 0):x(x_), y(y_){}
    bool operator==(const Queen &other) const;
    bool operator!=(const Queen &other) const;
};

bool Queen::operator==(const Queen &other) const{
    return this->x == other.x ||
           this->y == other.y ||
           this->x - other.x + other.y == this->y ||
           this->x - other.x + this->y == other.y;
}
bool Queen::operator!=(const Queen &other) const { return !(*this == other); }

// 找到解的数量
// 使用栈方式迭代实现回溯
// 此外还有递归回溯——无显式的退栈操作，函数返回时回溯到上一层
// 无论是递归还是迭代，回溯的本质都是先摆的皇后处于试探性的状态，依赖于能不能有后摆的皇后存在
// 如果当前层没有位置，则需要返回上一层，而上一层的皇后需要出栈（在递归实现时需要消去摆放痕迹，继续试探）
int nsolu = 0;
Stack<Queen> solu;
void eight_queens(int index){
    Queen q(index, 0);
    for(; q.y < 8; q.y++){
        if(solu.find(q) < 0){ // 试探本问题可能的解，条件不满足则进行剪枝
            solu.push(q);
            if(7 == index){
                nsolu++;
                solu.pop(); // 退栈，寻找下一处可能的解
                return ; // 从本问题回溯
            }
            eight_queens(index+1); // 递归搜索子问题
            solu.pop(); // 从子问题返回后，要么子问题无解，要么找到解，均需要回溯到本层后继续试探
        }
    }
}
// 迭代同样可以实现两个方向!!!, 使用栈pop来实现回溯
int queens(int N){
    int nsolu = 0;
    Stack<Queen> S;
    auto q = Queen(0, 0);
    while((0 < q.x) || (q.y < N)){
        while ((q.y < N) && (0 <= S.find(q)))q.y++; // 剪枝，检查皇后是否会遭到攻击
        if (q.y < N) {
            S.push(q);
            if (N <= S.size()) {
                nsolu++;
            }
            q.x++; // 迭代搜索子问题
            q.y = 0;
        }
        if(N <= q.y || N <= S.size()){ // 从本问题回溯，继续尝试找到解或找到新的解
            q = S.pop();
            q.y++;
        }
    }
    return nsolu;
}

int main(){
    cout << queens(8) << endl;
    eight_queens(0);
    cout << nsolu << endl;
    Stack<Queen> S;
    S.push(Queen(1,1));
    S.pop();
    return 0;
}
