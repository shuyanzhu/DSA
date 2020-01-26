#ifndef _DSA_STRINGCIRCLEQUEUE_
#define _DSA_STRINGCIRCLEQUEUE_
#include <assert.h>
#include <unistd.h>
#include <errno.h>

#include "unp.h"
// 字符串读写环形缓冲区数据结构
class CircleQueue {
#ifdef DEBUG
public:
#else
private:
#endif
    char *queue_; int capacity_;
    int front_;
    int rear_;
    int flag_; // 环形队列要么设置标志位要么空闲一个空间标志
public:
    CircleQueue(int capacity = 512): capacity_(capacity), front_(0), rear_(0), flag_(0){ queue_ = new char[capacity_]; }
    ~CircleQueue(){ delete queue_; }
     // 环形缓冲区的使用导致增加了一次系统调用。避免方法是开辟空间但增加复制次数
    bool full(){ return flag_; }
    bool empty() { return !flag_ && front_ == rear_; }
    int circleReadIn(int fileno){ // assert(rear_ < capacity_);
        int end1 = (front_ <= rear_ ? capacity_ : front_); // rear_ < end1
        int n1 = read(fileno, queue_ + rear_, end1 - rear_);
        rear_ = (n1 >= 0 ? rear_ + n1 : rear_);
        if(n1 <= 0)return n1; // RST/EOF
        if(rear_ < capacity_) { // assert(rear_ <= end1 && front_ < capacity_) endl为front_时可能满，越界必然等于capacity_
            if(rear_ == front_)flag_ = 1; // assert(n>0), 环形缓冲区必不为空，故必为满
            return n1;
        }
        int n2 = read(fileno, queue_, front_); // assert(0<n1 && rear_1 = end1 = capacity_)
        rear_ = (0 <= n2 ? rear_ + n2 : rear_) % capacity_; // 收到FIN下次处理
        if(rear_ == front_) flag_ = 1;
        errno = 0; // 成功调用不会改变errno值, 需要手动更改
        return n1 + (n2 < 0 ? 0 : n2); // 必定大于0
    }
    int circleWriteout(int fileno){ // assert(front_ < capacity_ && 0 <= rear_ < capacity_)
        int end1 = (rear_ <= front_ ? capacity_ : rear_);
        int n1 = write(fileno, queue_ + front_, end1 - front_);
        front_ = (n1 >= 0 ? front_ + n1 : front_);
        if(n1 > 0)flag_ = 0;
        if(n1 <= 0 || front_ < capacity_) {// EPIPE/BLOCK || front_无需越界(end1为rear_或未越界)
            return n1;
        }
        int n2 = write(fileno, queue_, rear_);
        front_ = (0 <= n2 ? front_ + n2 : front_)  % capacity_;
        errno = 0; // 收到的RST下次调用write时再进行处理
        return n1 + (n2 < 0 ? 0 : n2); // 结果必定大于0
    }

};
#endif
