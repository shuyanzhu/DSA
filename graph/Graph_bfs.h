#pragma once
#include <queue>
#include "Graph.h"

template<typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int, v, int &clock) {
	std::queue<int> Q; status(v) = DISCOVERED; Q.push(v);
	while (!Q.empty()) {
		int v = Q.pop(); //ȥ���͵����Ѿ�����
		dTime(v) = ++clock;
		for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
			if (UNDISCOVERED == status(u)) {
				status(u) = DISCOVERED; Q.push(u);
				status(v, u) = TREE; parent(u) = v;
			}
			else
				status(v, u) = CROSS; //����������ָ�򸸽ڵ�ı���Ϊ���
		}
		status(v) = VISITED;
	}
}
template<typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int v) { //bfsɭ��
	reset(); int clock = 0; int s = v;
	do 
		if(UNDISCOVERED==status(v))
			BFS(v, clock);
	while (s != (v = (++v%n)));
}
