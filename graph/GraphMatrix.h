#pragma once
#include <vector>
#include "Graph.h"

template <typename Tv>
struct Vertex
{ //�������ݽṹ����װ����ڵ�����?
    Tv data;
    int inDegree, outDegree; // ���ݺ���ȳ���?
    VStatus
        status; // �����ڱ�������ʼʱ����UNDISCOVERED
    int dTime, fTime; // ʱ����?
    int parent;
    int priority; // ���ȼ�
    Vertex(const Tv &d)
        : data(d)
        , inDegree(0)
        , outDegree(0) status(UNDISCOVERED)
        , dTime(-1)
        , fTime(-1)
        , parent(-1)
        , priority(INT_MAX)
    {}
};
template <typename Te>
struct Edge
{ //�����ݽṹ����װ����ߵ��ڽӾ���?
    Te data;        //�ߵ�����
    int weight;     //�ߵ�Ȩ��
    EStatus status; //�ߵ�״̬
    Edge(const Te &d, int w)
        : data(d)
        , weight(w)
        , status(UNDETERMINED)
    {}
};

// �ڽӾ������ݽṹ
template <typename Tv, typename Te>
class GraphMatrix : public Graph
{
  private:
    std::vector<Vertex<Tv> > V;
    std::vector<std::vector<Edge<Te> *> > E;

  public:
    GraphMatrix() { n = e = 0; }
    GraphMatrix()
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                delete E[i][j];
    }
    //����Ļ�������?
    Tv &vertex(int i) { return V[i].data; } //���ض�������
    int inDegree(int i)
    {
        return V[i].inDegree;
    } //���ض������?
    int outDegree(int i)
    {
        return V[i].outDegree;
    } //���ض������?
    VStatus &status(int i) { return V[i].status; } //���ض���״̬
    int &dTime(int i) { return V[i].dTime; }
    int &fTime(int i) { return V[i].fTime; }
    int &parent(int i) { return V[i].parent; }
    int &priority(int i) { return V[i].priority; }
    int nextNbr(int i, int j)
    { //�����ڽӱ�֮�󣬸��ӶȽ������ڵ�ǰ�ڵ�ĳ���?
        while ((-1 < j) && !exists(i, --j))
            ;
        return j;
    }
    int firstNbr(int i)
    {
        return nextNbr(i, n);
    } // n������ʵ����Ϊ�ڱ�Ԫ�أ���������κ�һ��Ԫ������?
    //����Ķ�̬����?
    int insert(const Tv &vertex)
    { // �������?
        E.push_back(std::vector<Te *>(n + 1, NULL));
        for (int i = 0; i < n; i++)
            E[i].push_back(NULL);
        V.push_back(Vertex(vertex));
        n++;
    }
    Tv remove(int i)
    { // �ڵ��ɾ��?
        if (i < 0 || n <= i) return;
        for (int j = 0; j < n; j++)
            if (exists(i, j)) {
                delete E[i][j];
                V[j].inDegree--;
            }
        E.erase(E.begin() + i);
        n--;
        for (int j = 0; j < n; j++) {
            if (exists(j, i)) {
                delete E[j][n];
                V[j].outDegree--;
            }
            E[j].erase(E[j].begin() + i);
        }
        Tv vBak = V[i].data;
        V.erase(V.begin() + i);
        return vBak;
    }
    //�߲���
    bool exists(i, j)
    {
        return (0 <= i) && (i < n) && (0 <= j) && (j < n) && E[i][j] != NULL;
    }
    Te &edge(int i, int j) { return E[i][j]->data; }
    EStatus &status(int i) { return E[i][j]->status; }
    int &weight(int i) { return E[i][j]->weight; }
    void insert(const Te &edge, int w, int i, int j)
    {
        if (exists(i, j)) return;
        E[i][j] = new Edge<Te>(edge, w);
        e++;
        V[i].outDegree++;
        V[j].inDegree++;
    }
    Te remove(int i, int j)
    {
        if (!exists(i, j)) return;
        Te eBak = E[i][j]->data;
        e--;
        V[i].outDegree--;
        V[j].inDegree--;
        delete E[i][j];
        E[i][j] = NULL;
        return eBak;
    }
};