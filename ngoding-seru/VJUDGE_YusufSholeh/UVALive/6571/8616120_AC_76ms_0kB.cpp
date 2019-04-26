#include<bits/stdc++.h>
#define INF 1e9
using namespace std;

#define MAX 605

struct edge{
	int to, rev;
	int flow, cap;
};


vector<edge> G[MAX];
int source, sink;
int vis[MAX], bt[MAX], idx[MAX], day(0), N;


void add(int s, int t, int cap) {
	edge a = {t, G[t].size(), 0, cap};
	edge b = {s, G[s].size(), 0, 0};
	G[s].push_back(a);
	G[t].push_back(b);
}

int maxflow() {
	day++;
	int ans = 0;
	while(true) {
		day++; queue<int> q;
		q.push(source);
		while(!q.empty()) {
			int f = q.front(); q.pop();
			if (f == sink) break;
			int size = G[f].size();
			for(int i = 0; i < size; i++) {
				int next = G[f][i].to;
				int cap = G[f][i].cap;
				if (vis[next] != day && cap > 0) {
					vis[next] = day;
					bt[next] = f;
					idx[next] = i;
					q.push(next);
				}
			}
		}
		if (vis[sink] != day) break;
		int ptr = sink; int aug = INF;
		while(ptr != source) {
			int from = bt[ptr];
			int to = idx[ptr];
			aug = min(aug, G[from][to].cap);
			ptr = from;
		} ptr = sink;
		while(ptr != source) {
			int from = bt[ptr];
			int to = idx[ptr];
			int rev = G[from][to].rev;
			G[from][to].cap -= aug;
			G[ptr][rev].cap += aug;
			ptr = from;
		} ans += aug;
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
		
		int min_cut = maxflow();
		printf("Case %d: %d\n",cs, sum - min_cut);
	}
}
