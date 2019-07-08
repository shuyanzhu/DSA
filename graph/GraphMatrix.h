//
// Created by zhuhu on 2019/7/6.
//

#include "graph.h"
#include "../vector/vector.h"
#include "../queue/queue.h"
#include "../stack/mystack.h"

template <typename T> struct Vertex{
    T data; int inDegree, outDegree; VStatus status;
    int dTime, fTime; // 时间标签
    int parent; int priority; // 在遍历树中的父节点, 优先级

    Vertex(T const &d = (T)0):data(d), inDegree(0), outDegree(0),
            status(UNDISCOVERED), dTime(-1), fTime(-1), parent(-1), priority(INT_MAX){}
};
template <typename T> struct Edge{
    T data; int weight; EType type;
    Edge(T const &d, int w):data(d), weight(w), type(UNDETERMINED){}
};
template <typename Tv, typename Te> class GraphMatrix : public Graph<Tv, Te>{
private:
    Vector<Vertex<Tv> > V; // 顶点集
    Vector<Vector< Edge<Te> *> >E; // 边集
public:
    GraphMatrix(){ this->n = this->e = 0;}
    ~GraphMatrix(){
        for(int i = 0; i < this->n; i++)
            for(int j = 0; j < this->n; j++){
                delete E[i][j];
            }
    }

    // 顶点操作
    virtual Tv &vertex(int i){ return V[i].data; }
    virtual int inDegree(int i){ return V[i].inDegree; }
    virtual int outDegree(int i){ return V[i].outDegree; }
    virtual int firstNbr(int i){ return nextNbr(i, this->n); }
    virtual int nextNbr(int i, int j){ // 相对于j的下一个邻接顶点
        while((-1 < j) && (!exists(i, --j)));
        return j;
    }
    virtual VStatus &status(int i){ return V[i].status; }
    virtual int &dTime(int i){ return V[i].dTime; }
    virtual int &fTime(int i){ return V[i].fTime; }
    virtual int &priority(int i) { return V[i].priority; }
    virtual int &parent(int i){ return V[i].parent; }

    virtual int insert(Tv const &vertex){
        for(int i = 0; i < this->n; i++){
            E[i].insert(NULL);
        }
        this->n++;
        E.insert(Vector<Edge<Te> *>(this->n, (Edge<Te> *)NULL));
        return V.insert(Vertex<Tv>(vertex));
    }
    virtual Tv remove(int i){
        for(int j = 0; j < this->n; j++){
            if(exists(i, j)){
                delete E[i][j];
                V[j].inDegree--; // 入度
                this->e--;
            }
            if(exists(j, i)){
                delete E[j][i];
                V[j].outDegree--; // 出度
                this->e--;
            }
            E[j].remove(i);
        }
        E.remove(i);
        this->n--;
        return V.remove(i).data; // 返回被删除的顶点信息
    }

    // 边操作
    virtual bool exists(int i, int j){ return (0 <= i) &&(i < this->n) && (0 <= j) && (j < this->n) && E[i][j] != NULL;}
    virtual EType &type(int i, int j) { return E[i][j]->type; }
    virtual Te &edge(int i, int j) { return E[i][j]->data; }
    virtual int &weight(int i, int j){ return E[i][j]->weight; }

    virtual void insert(Te const &edge, int w, int i, int j){
        if(exists(i, j))return;
        E[i][j] = new Edge<Te>(edge, w);
        this->e++; V[i].outDegree++; V[j].inDegree ++;
    }
    virtual Te remove(int i, int j){
        Te eBak = edge(i, j); delete E[i][j]; E[i][j] = NULL;
        this->e--;V[i].outDegree--; V[j].inDegree--;
        return eBak ;
    }

};

