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
	
	// printf("%d %d\n",res.first, res.second);
	// printf("%d %d\n",res.first, res.second);
	return res;
}

int W[205][205];
int adj[205][205];
int deg[205];
int dp[1<<16];
int odd;
int mat[205][205];
int num[205];

int f(int mask) {
	if (((1 << odd) - 1) == mask) return 0;
	if (dp[mask] != -1) return dp[mask];
	int &ret = dp[mask];
	ret = INF;
	int first = 0;
	for(int i = 0; i < odd; i++) {
		if (((1 << i) & mask) == 0) {
			first = i;
			break;
		}
	}
	
	for(int i = 0; i < odd; i++) {
		if ((((1 << i) & mask) == 0) && i != first) {
			ret = min(ret, f(mask | (1 << i) | (1 << first)) + W[num[i]][num[first]]);
		}
	}
	
	return ret;
}

int main() {
	tc = 1;
	for(int cs = 1; cs <= tc; cs++) {
		scanf("%d %d",&n, &m);
		
		int ans = 0;
		for(int i = 0; i < 205; i++) for(int j = 0; j < 205; j++) W[i][j] = INF;
		for(int i = 0; i < 205; i++) G[i].clear(), deg[i] = 0;
		for(int i = 0; i < m; i++) {
			int u, v, w;
			scanf("%d %d %d",&u, &v, &w); u++, v++;
			W[u][v] = min(W[u][v],w);
			W[v][u] = min(W[v][u],w);
			adj[u][v] = w;
			adj[v][u] = w;
			deg[u]++;
			deg[v]++;
			ans += w;
		}
		
		source = 0, sink = 2*n + 1;
		for(int k = 1; k <= n; k++) {
			for(int i = 1; i <= n; i++) {
				for(int j = 1; j <= n; j++) {
					W[i][j] = min(W[i][j], W[i][k] + W[k][j]);
				}
			}
		}
		
		/*
		for(int i = 1; i <= n; i++) if (deg[i] & 1) {
			add(source, i, 1, 0);
			add(n+i, sink, 1, 0);
			for(int j = 1; j <= n; j++) if (i != j && (deg[j] & 1)) {
				printf("to %d %d %d\n",i, j, W[i][j]);
				add(i, n+j, 1, W[i][j]);
			}
		}
		
		printf("%d\n",ans + MCMF().second/2);
		
		for(int i = 1; i <= n; i++) {
			int size = G[i].size();
			for(int j = 0; j < size; j++) {
				if (G[i][j].cap == 0) 
					printf("(s,t,c):(%d,%d,%d)\n",i, G[i][j].to-n, G[i][j].cost);
			}
		}
		*/
		
		odd = 0;
		for(int i = 1; i <= n; i++) {
			if (deg[i] & 1) {
				num[odd] = i;
				odd += 1;
			}
		}
		
		// printf("%d\n",odd);
		if (odd == 0) printf("%d\n",ans);
		else {
			memset(dp,-1,sizeof(dp));
			printf("%d\n",ans + f(0));
		}
	}
}