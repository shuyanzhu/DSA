#ifndef _DSA_STRINGCIRCLEQUEUE_
#define _DSA_STRINGCIRCLEQUEUE_
#include "assert.h"
#include "unistd.h"
#include "errno.h"
// 字符串读写环形缓冲区数据结构
class CircleQueue {
protected:
    char *queue; int capacity;
    int front;
    int rear;
    int flag; // 环形队列要么设置标志位要么空闲一个空间标志
public:
    CircleQueue(int capacity_ = MAXLINE): capacity(capacity_), front(0), rear(0), flag(0){ queue = new char[capacity]; }
    ~CircleQueue(){ delete queue; }
     // 环形缓冲区的使用导致增加了一次系统调用。避免方法是开辟空间但增加复制次数
    bool full(){ return flag; }
    bool empty() { return !flag && front == rear; }
    int circleReadIn(int fileno){ // assert(rear < capacity);
        int end1 = (front <= rear ? capacity : front); // rear < end1
        int n1 = read(fileno, queue + rear, end1 - rear);
        rear = (n1 >= 0 ? rear + n1 : rear);
        if(n1 <= 0)return n1; // RST/EOF
        if(rear < capacity) { // assert(rear <= end1 && front < capacity) endl为front时可能满，越界必然等于capacity
            if(rear == front)flag = 1; // assert(n>0), 环形缓冲区必不为空，故必为满
            return n1;
        }
        int n2 = read(fileno, queue, front); // assert(0<n1 && rear1 = end1 = capacity)
        rear = (0 <= n2 ? rear + n2 : rear) % capacity; // 收到FIN下次处理
        if(rear == front) flag = 1;
        errno = 0; // 成功调用不会改变errno值, 需要手动更改
        return n1 + n2; // 必定大于0
    }
    int circleWriteout(int fileno){ // assert(front < capacity && 0 <= rear < capacity)
        int end1 = (rear <= front ? capacity : rear);
        int n1 = write(fileno, queue + front, end1 - front);
        front = (n1 >= 0 ? front + n1 : front);
        if(n1 > 0)flag = 0;
        if(n1 <= 0 || front < capacity) {// EPIPE/BLOCK || front无需越界(end1为rear或未越界)
            return n1;
        }
        int n2 = write(fileno, queue, rear);
        front = (0 <= n2 ? front + n2 : front)  % capacity;
        errno = 0; // 收到的RST下次调用write时再进行处理
        return n1 + n2; // 结果必定大于0
    }

};
#endif