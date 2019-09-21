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
char ch[20][20];

inline void try_add(int px, int py, int x, int y) {
	if (x >= 0 && x < n && y >= 0 && y < m) {
		// printf("BZZ %d %d\n",px*m + py, m*n + x*m + y);
		if (x == px) {
			
			if (ch[px][py] == '>' && y == py + 1) {
				add(px*m + py, m*n + x*m + y, 1, 0);
			} else if (ch[px][py] == '<' && y == py - 1) {
				add(px*m + py, m*n + x*m + y, 1, 0);
			} else {
				add(px*m + py, m*n + x*m + y, 1, 1);
			}
			
		} else {
			
			if (ch[px][py] == '^' && x == px - 1) {
				add(px*m + py, m*n + x*m + y, 1, 0);
			} else if (ch[px][py] == 'v' && x == px + 1) {
				add(px*m + py, m*n + x*m + y, 1, 0);
			} else {
				add(px*m + py, m*n + x*m + y, 1, 1);
			}
			
		}
	}
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
		
		while(ptr != source) {
			int from = bt[ptr];
			int id = idx[ptr];
			
			if (G[from][id].cap < mins) 
				mins = G[from][id].cap;
			
			// printf("%d %d %d\n",ptr, from,G[from][id].cost);
			res.second += G[from][id].cost;
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
			ptr = from;
		}
	}
	
	return res;
}

int main() {
	scanf("%d",&tc);
	for(int cs = 1; cs <= tc; cs++) {
		scanf("%d %d",&n, &m);
		source = 2*n*m + 1;
		sink = 2*n*m + 2;
		for(int i = 0; i < n; i++) 
			scanf("%s",&ch[i]);
		if (n & m & 1) {
			printf("Case #%d: -1\n",cs);
			continue;
		}
		
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				try_add(i, j, i + 1, j);
				try_add(i, j, i - 1, j);
				try_add(i, j, i, j - 1);
				try_add(i, j, i, j + 1);
				add(source, i*m + j, 1, 0);
				add(m*n + i*m + j, sink, 1, 0);
			}
		}
		
		pair<int,int> ans = MCMF();
		
		printf("Case #%d: %d\n",cs,ans.second);
		
		for(int i = 0; i <= sink; i++) G[i].clear();
	}
}