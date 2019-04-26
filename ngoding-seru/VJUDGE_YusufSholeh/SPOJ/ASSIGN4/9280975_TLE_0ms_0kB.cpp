#include <bits/stdc++.h>
 
using namespace std;
 
#define INF 1000000000
#define MAXN 500
 
struct Edge
{
    int t, c, w, r;
    Edge(int _t, int _c, int _w, int _r): t(_t), c(_c), w(_w), r(_r) {};
};
 
int pot[MAXN+5], prv[MAXN+5], dist[MAXN+5], vis[MAXN+5];
vector<Edge> edge[MAXN+5];
 
pair<int, int> mcmf(int n, int s, int t)
{
    fill(pot, pot+n, 0);
    int mf = 0, mc = 0;
	while (true) {
		priority_queue<pair<int, int> > pq;
		fill(dist, dist+n, INF);
		fill(vis, vis+n, 0);
		pq.push(make_pair(0, s));
		dist[s] = 0;
		while (!pq.empty()) {
			pair<int, int> top = pq.top();
			pq.pop();
			int v = top.second, c = -top.first;
			if (vis[v]) continue;
			vis[v] = 1;
			for (int i = 0; i < edge[v].size(); ++i) {
				Edge &e = edge[v][i];
				int u = e.t;
				if (e.c == 0) continue;
				int ndist = dist[v] + e.w + pot[v]-pot[u];
				if (ndist < dist[u]) {
					dist[u] = ndist;
					prv[u] = e.r;
					pq.push(make_pair(-ndist, u));
				}
			}
		}
		int v = t;
		if (dist[t] == INF) break;
		int flow = INF;
		for (int i = 0; i < n; ++i) pot[i] += dist[i];
		while (v != s) {
			Edge &r = edge[v][prv[v]], &e = edge[r.t][r.r];
			flow = min(flow, e.c);
			v = r.t;
		}
		mf += flow;
		v = t;
		while (v != s) {
			Edge &r = edge[v][prv[v]], &e = edge[r.t][r.r];
			e.c -= flow;
			r.c += flow;
			mc += e.w * flow;
			v = r.t;
		}
	}
    return make_pair(mf, mc);
}
 
void add(int u, int v, int c, int w) {
	Edge a(v,c,w,edge[v].size()), b(u,0,-w,edge[u].size());
	edge[u].push_back(a);
	edge[v].push_back(b);
}
 
int main()
{
	int tc;
	scanf("%d",&tc);
	while(tc--) {
		for(int i = 0; i < MAXN; i++) edge[i].clear();
		
		int N, M; scanf("%d %d",&N, &M);
		int n, m, s, t;
		s = 0, t = N + M + 1, n = t + 1;
		for(int i = 1; i <= N; i++) {
			int k; scanf("%d",&k);
			add(s, i, k, 0);
		}
		for(int i = 1; i <= M; i++) {
			int k; scanf("%d",&k);
			add(N+i, t, k, 0);
		}
		for(int i = 1; i <= N; i++)
			for(int j = 1; j <= M; j++) {
				int k; scanf("%d",&k);
				add(i, N+j, 1e5, k);
			}
			
		pair<int, int> ret = mcmf(n, s, t);
		printf("%d\n",ret.second);
	}
}