#include<bits/stdc++.h>
#define INF 1000000000
using namespace std;
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

int tc, n, m, source, sink;
int flag[500], bt[500], dist[500], idx[500];

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
		
		while(ptr != source) {
			int from = bt[ptr];
			int id = idx[ptr];
			
			if (G[from][id].cap < mins) 
				mins = G[from][id].cap;
			
			ptr = from;
		}
		
		res.first += mins;
		
		ptr = sink;
		
		while(ptr != source) {
			int from = bt[ptr];
			int id = idx[ptr];
			int rev = G[from][id].rev;
			G[from][id].cap -= mins;
			G[ptr][rev].cap += mins;
			res.second += G[from][id].cost * mins;
			ptr = from;
		}
	}
	
	return res;
}

int main() {
	scanf("%d",&tc);
	while(tc--) {
		memset(flag,0,sizeof(flag));
		memset(bt, -1, sizeof(bt));
		memset(dist, 0, sizeof(dist));
		memset(idx, 0, sizeof(idx));
		for(int i = 0; i < 500; i++) G[i].clear();
		
		int n, m;
		scanf("%d %d",&n, &m);
		
		source = 0; sink = n + m + 1;
		
		for(int i = 1; i <= n; i++) {
			int k;
			scanf("%d",&k);
			add(source, i, k, 0);
		}
		
		for(int i = 1; i <= m; i++) {
			int k;
			scanf("%d",&k);
			add(n+i, sink, k, 0);
		}
		
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++) {
				int k;
				scanf("%d",&k);
				add(i, n+j, 1e7, k);
			}
			
		printf("%d\n",MCMF().second);
	}
}