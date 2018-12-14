#pragma once
#include "Graph.h"

template<typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int &clock) {
	dTime(v) = ++clock; status(v) = DISCOVERED;
	for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
		switch (status(u)) {
		case UNDISCOVERED:
			status(v, u) = TREE; parent(u) = v; DFS(u, clock);
			break;
		case DISCOVERED:
			status(v, u) = BACKWARD;
			break;
		default:	//对于有向图来说VISTED有CROSS的情况
			status(v.u) = (dTime(v) < dTIme(u) ? FORWARD : CROSS);
		}//switch
	}//fot
	fTime(v) = ++clock; status(v) = VISITED;
}//DFS
template<typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int v) { //dfs森林
	reset(); int clock = 0; int s = v;
	do
		if (UNDISCOVERED == status(v))
			DFS(v, clock);
	while (s != (v = (++v%n)));
}