#include<bits/stdc++.h>
using namespace std;

#define INF 1e9
#define MAX 10005

int source, sink;
struct edge{
	int to, rev;
	int flow, cap;
};

vector<edge> G[30*MAX];

inline void add(int s, int t, int cap) {
	edge a = {t, G[t].size(), 0, cap};
	edge b = {s, G[s].size(), 0,   0};
	G[s].push_back(a);
	G[t].push_back(b);
}

int vis[30*MAX], bt[30*MAX];
int idx[30*MAX];
int maxflow() {
	int day = 0;
	int ans = 0;
	while(true) {
		day++;
		queue<int> q;
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
		int ptr = sink;
		int aug = INF;
		while(ptr != source) {
			int from = bt[ptr];
			int to = idx[ptr];
			aug = min(aug, G[from][to].cap);
			ptr = from;
		}
		ptr = sink;
		while(ptr != source) {
			int from = bt[ptr];
			int to = idx[ptr];
			int rev = G[from][to].rev;
			G[from][to].cap -= aug;
			G[ptr][rev].cap += aug;
			ptr = from;
		}
		ans += aug;
		if (ans > 1) break;
	}
	return ans;
}


int n, m;
int cs = 0;
int main() {
	while(true) {
		scanf("%d %d",&n, &m);
		if (n == 0 && m == 0) return 0;
		for(int i = 1; i <= m; i++) {
			int a, b;
			scanf("%d %d",&a, &b);
			add(a,b,1);
			add(b,a,1);
		}
		int x, y;
		scanf("%d %d",&x,&y);
		source = 0, sink = n+1;
		add(source, x, 1000);
		add(y, sink, 1000);
		printf("Case %d: ",++cs);
		if (maxflow() > 1) printf("YES\n");
		else printf("NO\n");
		
		for(int i = 0; i <= n+1; i++) G[i].clear();
	}
}