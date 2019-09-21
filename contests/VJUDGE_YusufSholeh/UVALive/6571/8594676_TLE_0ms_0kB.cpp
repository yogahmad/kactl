#include<bits/stdc++.h>
#define INF 1e9
using namespace std;

#define MAX 605

struct edge{
	int to, rev;
	int flow, cap;
};

vector<edge> G[MAX];
int q[1000005], dist[MAX], work[MAX], N;
int source, sink;

void add(int s, int t, int cap) {
	edge a = {t, G[t].size(), 0, cap};
	edge b = {s, G[s].size(), 0, 0};
	G[s].push_back(a);
	G[t].push_back(b);
}

inline bool search() {
	for(int i = 0; i <= N+1; i++) dist[i] = -1;
	dist[source] = 0;
	int tail = 0;
	q[tail] = source;
	for(int head = 0; head <= tail; head++) {
		int u = q[head];
		int sz = G[u].size();
		for(int i = 0; i < sz; i++) {
			int v = G[u][i].to;
			if (dist[v] < 0 && G[u][i].flow < G[u][i].cap) {
				dist[v] = dist[u] + 1;
				q[++tail] = v;
			}
		}
	}
	return dist[sink] >= 0;
}

int dinic(int now, int flo) {
	if (now == sink) return flo;
	int size = G[now].size();
	for(int &i = work[now]; i < size; i++) {
		int to = G[now][i].to;
		int flow = G[now][i].flow;
		int cap = G[now][i].cap;
		int rev = G[now][i].rev;
		if (dist[to] == dist[now] + 1) {
			int fflow = dinic(to, min(flo, cap - flow));
			if (fflow) {
				G[now][i].flow += fflow;
				G[to][rev].flow -= fflow;
				return fflow;
			}
		}
	}
	return 0;
}

int maxflow() {
	int ans = 0;
	while(search()) {
		for(int i = 0; i <= N+1; i++) work[i] = 0;
		while(true) {
			int res = dinic(source, INF);
			if (res == 0) break;
			ans += res;
		}
	}
	return ans;
}


int tc;
int A[MAX], B[MAX], S[MAX];
int clean[MAX][MAX];

int main() {
	scanf("%d",&tc);
	for(int cs = 1; cs <= tc; cs++) {
		int n, m;
		scanf("%d %d",&n, &m);
		for(int i = 1; i <= n; i++) {
			scanf("%d %d %d",&A[i], &B[i], &S[i]);
		}
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				scanf("%d",&clean[i][j]);
			}
		}
		
		//printf("AMPAS\n");
		source = 0;
		sink = 2*n+1;
		N = sink + 1;
		for(int i = 0; i < MAX; i++) G[i].clear();
		
		int sum = 0;
		for(int i = 1; i <= n; i++) {
			add(source, i, (S[i] + m - 1) / m);
			add(i + n, sink, (S[i] + m - 1) / m);
			sum += (S[i] + m -1) / m;
			for(int j = 1; j <= n; j++) {
				if (B[i] + clean[i][j] < A[j]) {
					add(i, n + j, INF);
				}
			}
		}
		
		//printf("AMPAS 2\n");
		int min_cut = maxflow();
		//printf("%d WTF\n",min_cut);
		printf("Case %d: %d\n",cs, sum - min_cut);
	}
}
