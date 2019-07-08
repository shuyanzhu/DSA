//
// Created by zhuhu on 2019/7/6.
//

#ifndef DSA_GRAPH_H
#define DSA_GRAPH_H
/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma once
#include "../vector/vector.h"
#include "../queue/queue.h"
#include "../stack/mystack.h"
typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus; //顶点状态
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType; //边在遍历树中所属的类型

template <typename Tv, typename Te> //顶点类型、边类型
class Graph { //图Graph模板类
private:
    void reset() { //所有顶点、边的辅助信息复位
        for ( int i = 0; i < n; i++ ) { //所有顶点的
            status ( i ) = UNDISCOVERED; dTime ( i ) = fTime ( i ) = -1; //状态，时间标签
            parent ( i ) = -1; priority ( i ) = INT_MAX; //（在遍历树中的）父节点，优先级数
            for ( int j = 0; j < n; j++ ) //所有边的
                if ( exists ( i, j ) ) type ( i, j ) = UNDETERMINED; //类型
        }
    }
    void BFS ( int, int& ); //（连通域）广度优先搜索算法
    void DFS ( int, int& ); //（连通域）深度优先搜索算法
    void DFS_I(int i, int &clock);
    void BCC ( int, int&, Stack<int>& ); //（连通域）基于DFS的双连通分量分解算法
    bool TSort ( int, int&, Stack<Tv>* ); //（连通域）基于DFS的拓扑排序算法
    template <typename PU> void PFS ( int, PU ); //（连通域）优先级搜索框架
public:
// 顶点
    int n; //顶点总数
    virtual int insert ( Tv const& ) = 0; //插入顶点，返回编号
    virtual Tv remove ( int ) = 0; //删除顶点及其关联边，返回该顶点信息
    virtual Tv& vertex ( int ) = 0; //顶点v的数据（该顶点的确存在）
    virtual int inDegree ( int ) = 0; //顶点v的入度（该顶点的确存在）
    virtual int outDegree ( int ) = 0; //顶点v的出度（该顶点的确存在）
    virtual int firstNbr ( int ) = 0; //顶点v的首个邻接顶点
    virtual int nextNbr ( int, int ) = 0; //顶点v的（相对于顶点j的）下一邻接顶点
    virtual VStatus& status ( int ) = 0; //顶点v的状态
    virtual int& dTime ( int ) = 0; //顶点v的时间标签dTime
    virtual int& fTime ( int ) = 0; //顶点v的时间标签fTime
    virtual int& parent ( int ) = 0; //顶点v在遍历树中的父亲
    virtual int& priority ( int ) = 0; //顶点v在遍历树中的优先级数
// 边：这里约定，无向边均统一转化为方向互逆的一对有向边，从而将无向图视作有向图的特例
    int e; //边总数
    virtual bool exists ( int, int ) = 0; //边(v, u)是否存在
    virtual void insert ( Te const&, int, int, int ) = 0; //在顶点v和u之间插入权重为w的边e
    virtual Te remove ( int, int ) = 0; //删除顶点v和u之间的边e，返回该边信息
    virtual EType & type ( int, int ) = 0; //边(v, u)的类型
    virtual Te& edge ( int, int ) = 0; //边(v, u)的数据（该边的确存在）
    virtual int& weight ( int, int ) = 0; //边(v, u)的权重
// 算法
    void bfs ( int ); //广度优先搜索算法
    void dfs ( int ); //深度优先搜索算法
    void bcc ( int ); //基于DFS的双连通分量分解算法
    Stack<Tv>* tSort ( int ); //基于DFS的拓扑排序算法
    void prim ( int ); //最小支撑树Prim算法
    void dijkstra ( int ); //最短路径Dijkstra算法
    template <typename PU> void pfs ( int, PU ); //优先级搜索框架
};
template <typename Tv, typename Te> void Graph<Tv, Te>::BFS(int i, int &clock) {
    Queue<int> q;
    q.enqueue(i);
    dTime(i) = clock++;
    while(!q.empty()){
        auto pa = q.dequeue(); status(pa) = DISCOVERED;
        for(int j = firstNbr(pa); j > -1; j = nextNbr(pa, j)){
            if(UNDISCOVERED == status(j)) {
                parent(j) = pa;
                type(pa, j) = TREE;
                dTime(j) = clock++;
                q.enqueue(j);
            } else{
                type(pa, j) = CROSS;
            }
        }
        status(pa) = VISITED;
    }
}

template <typename Tv, typename Te> void Graph<Tv, Te>::bfs(int i) {
    int clock = 0; reset();
    for(int j = 0; j < this->n; j++){
        if(status((i + j) % this->n) == UNDISCOVERED)BFS((i + j) % this->n, clock);
    }
}
template <typename Tv, typename Te> void Graph<Tv, Te>::DFS(int i, int &clock) { // 递归回溯
    dTime(i) = clock++; status(i) = DISCOVERED;
    for(int j = firstNbr(i); j > -1; j = nextNbr(i, j)){
        if(DISCOVERED == status(j)){
            type(i, j) = BACKWARD;
        } else if(UNDISCOVERED == status(j)){
            parent(j) = i;
            type(i, j) = TREE;
            DFS(i, clock);
        } else {
            if(dTime(i) < dTime(j))
                type(i, j) = FORWARD;
            else
                type(i, j) = CROSS;
        }
    }
    fTime(i) = clock++; status(i) = VISITED;
}
template <typename Tv, typename Te> void Graph<Tv, Te>::DFS_I(int i, int &clock) { // 使用栈的迭代式回溯
    Stack<int> s;
    s.push(i);
    dTime(i) = clock++; status(i) = DISCOVERED;
    int bak_k = -1;
    while(!s.empty()){
        int j = s.top(), k;
        for(k = (bak_k == -1 ? firstNbr(j) : nextNbr(j, bak_k)); k > -1; k = nextNbr(j, k)){
            if(UNDISCOVERED == status(k)){
                s.push(k);
                dTime(k) = clock++; status(k) = DISCOVERED;
                type(j, k) = TREE;
                break;
            } else if(DISCOVERED == status(k)){
                type(j, k) = BACKWARD;
            } else
                type(j, k) = (dTime(j) < dTime(k) ? FORWARD : CROSS);
        }
        if(k == -1){
            fTime(j) = clock++; status(j) = VISITED;
            bak_k = s.pop(); // 回溯
        } else
            bak_k = -1;
    }
}
template <typename Tv, typename Te> void Graph<Tv, Te>::dfs(int i) {
    int clock = 0; reset();
    for(int j = 0; j < this->n; j++){
        if(status((i + j) % this->n) == UNDISCOVERED)DFS((i+j)%this->n, clock);
    }
}
template <typename Tv, typename Te> template <typename PU> void Graph<Tv, Te>::pfs(int i, PU prioUpdater) {
    reset();
    for (int j = 0; j < n; j++){
        if(UNDISCOVERED == status(( i + j) % n)) PFS((i + j) % n, prioUpdater);
    }
}
template <typename Tv, typename Te> template <typename PU> void Graph<Tv, Te>::PFS(int i, PU prioUpdater) {
    priority(i) = 0; status(i) = VISITED; parent(i) = -1;
    while(true){
        for(int w = firstNbr(i); -1 < w; w = nextNbr(i, w))
            prioUpdater(this, i, w);
        for(int shortest = INT_MAX, w = 0; w < n; w++){
            if(UNDISCOVERED == status(w))
                if(shortest > priority(w)){
                    shortest = priority(w);
                    i = w;
                }
        }
        if(VISITED == status(i)) break;
        status(i) = VISITED; type(parent(i), i) = TREE;
    }
}


template <typename Tv, typename Te>
struct PrimPU {
    virtual void operator()(Graph<Tv, Te> *g, int uk, int v){
        if(UNDISCOVERED == g->status(v)){
            if(g->priority(v) > g->weight(uk, v)){
                g->priority(v) = g->weight(uk, v);
                g->parent(v) = uk;
            }
        }
    }
};
template <typename Tv, typename Te> struct DijkstraPU{
    virtual void operator()(Graph<Tv, Te> *g, int uk, int v){
        if(UNDISCOVERED == g->status(v)){
            if(g->priority(v) > g->priority(uk) + g->weight(uk, v)){
                g->priority(v) = g->priority(uk) + g->weight(uk, v);
                g->parent(v) = uk;
            }
        }
    }
};
#endif //DSA_GRAPH_H
