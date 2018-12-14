/*
 * @Author: 朱会茗
 * @Date: 2018-10-08 16:39:29
 * @LastEditors: OBKoro1
 * @LastEditTime: 2018-10-08 16:39:29
 * @Description:
 */
#pragma once
#include <vector>
#include <stack>

typedef enum
{
    UNDISCOVERED,
    DISCOVERED,
    VISITED
} VStatus;
typedef enum
{
    UNDETERMINED,
    TREE,
    CROSS,
    FORWARD,
    BACKWARD
} EStatus;

template <typename Tv, typename Te>
class Graph
{
    y private : void reset()
    {
        for (int i = 0; i < n; i++) {
            status(i) = UNDISCOVERED;
            dTime(i) = fTime(i) - 1;
            parent(i) = -1;
            priority(i) = INT_MAX;
            for (int j = 0; j < n; j++) {
                if (exist(i, j)) status(i, j) = UNDETERMINED;
            }
        }
    }
    void BFS(int, int &); // （连通域）广度优先搜索算法
    void DFS(int, int &); // （连通域）深度优先搜索算法
    void BCC(int, int &, std::stack<int> &); // （连通域）
    bool Tsort(int, int &, std::stack<Tv> *);
    template <typename PU>
    void PFS(int, PU);

  public:
    //顶点
    int n;                              //顶点总数
    virtual int insert(const Tv &) = 0; //插入顶点返回编号
    virtual Tv remove(int) = 0; //删除顶点及其关联的边，返回该顶点信息
    virtual Tv &vertex(int) = 0;   //顶点v的数据（该顶点的确存在）
    virtual int inDegree(int) = 0; //顶点的入度
    virtual int outDegree(int) = 0; //顶点的出度
    virtual int firstNbr(int) = 0;  //顶点的第一个邻接顶点
    virtual int nextNbr(int, int) = 0; //顶点的下一个邻接顶点, 相对于顶点j
    virtual VStatus &status(int) = 0; //顶点v的状态
    virtual int &dTime(int) = 0;      //顶点v的时间标签dTime
    virtual int &fTime(int) = 0;      //顶点v的时间标签fTime
    virtual int &parent(int) = 0;     //顶点v在遍历树中的父亲
    virtual int &priority(int) = 0;   //顶点v在遍历树种的优先级数
    //边，这里预定，无向边化为一对有向边
    int e; //边总数
    virtual bool exists(int, int) = 0;
    virtual void
    insert(cosnt Te &, int, int, int) = 0; //顶点v和顶点u之间插入权重为w的边e
    virtual Te remove(int, int) = 0; //删除v和u之间的边e，返回该边的信息
    virtual EStatus &type(int, int) = 0; //边（v，u）的类型
    virtual Te &edge(int, int) = 0; //边（v，u）的数据（该边确实存在）
    virtual int &weight(int, int) = 0; //边（v，u）的权重
    //算法,不用到数据类型的函数定义为非虚函数
    void bfs(int);              //广度优先算法
    void dfs(int);              //深度优先算法
    void bcc(int);              //基于DFS的双联通分量分解算法
    std::stack<Tv> *tSort(int); //基于DFS的拓扑排序算法
    void prim(int);             //最小生成树prim算法
    void dijkstra(int);         //最短路径的Dijkstra算法
    template <typename PU>
    void pfs(int, PU); //优先级搜索框架
};

#include "Graph_implementation.h"
