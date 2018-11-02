/**
 * Author: Stanford
 * Date: Unknown
 * Source: Stanford Notebook
 * Description: Min-cost max-flow. 
 * Not handling negative cycle. When there is negative cycle, there is no answer for MCMF.
 * Status: Tested on kattis mincostmaxflow
 * Time: Approximately O(E^2)
 */
#pragma once

struct edge{
	int to, rev;
	int flow, cap;
	int cost;
};
vector<edge> G[500];
inline void add(int s, int t, int capa, int costs) {
	edge a = {t, G[t].size(), 0, capa,  costs};
	edge b = {s, G[s].size(), 0,    0, -costs};
	G[s].push_back(a);
	G[t].push_back(b);
}
inline bool SPFA() {
	for(int i = 0; i <= sink; i++) dist[i] = INF, flag[i] = false, bt[i] = -1, idx[i] = -1;
	dist[source] = 0;
	queue<int> q;
	q.push(source);
	flag[source] = true;
	while(!q.empty()) {
		int now = q.front();
		q.pop();
		flag[now] = false;
		int size = G[now].size();
		for(int i = 0; i < size; i++) {
			int to = G[now][i].to;
			int cost = G[now][i].cost;
			int capa = G[now][i].cap;	
			if (capa > 0 && dist[to] > dist[now] + cost) {
				dist[to] = dist[now] + cost;
				bt[to] = now;
				idx[to] = i;
				if (!flag[to]) {
					flag[to] = true;
					q.push(to);
				}
			}
		}
	}
	return bt[sink] != -1;
}
 
pair<int,int> MCMF() {
	pair<int,int> res; res.first = 0, res.second = 0;
	while(true) {
		if (!SPFA()) break;
		int mins = INF;
		int ptr = sink;
		int total = 0;
		while(ptr != source) {
			int from = bt[ptr];
			int id = idx[ptr];
			if (G[from][id].cap < mins) 
				mins = G[from][id].cap;
			total += G[from][id].cost;
			ptr = from;
		}
		res.first += mins;
		res.second += total * mins;
		ptr = sink;
		while(ptr != source) {
			int from = bt[ptr];
			int id = idx[ptr];
			int rev = G[from][id].rev;
			G[from][id].cap -= mins;
			G[ptr][rev].cap += mins;
			ptr = from;
		}
	}
	return res;
}
