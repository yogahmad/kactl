#include<bits/stdc++.h>
#define MAXN 105
using namespace std;
struct edge{
	int to, rev;
	int flow, cap;
	int cost;
};

vector<edge> G[MAXN];

inline void add(int s, int t, int cap, int cost) {
	edge a = {t, G[t].size(), 0, cap, cost};
	edge b = {s, G[s].size(), 0, cap,-cost};
	G[s].push_back(a);
	G[t].push_back(b);
}

typedef pair<int,int> pii;

int inQ[MAXN];
int q[1000005];
int dist[MAXN];
int bt[MAXN];
int dari[MAXN];
int source, sink;
int n, m, k;

inline int SPFA() {
	for(int i = 1; i <= n; i++) bt[i] = -1, dist[i] = 2e9, inQ[i] = 0, dari[i] = -1;
	q[1] = source;
	dist[source] = 0;
	inQ[source] = 1;
	int tail = 1;
	for(int head = 1; head <= tail; head++) {
		int now = q[head];
		inQ[now] = 0;
		int size = G[now].size();
		
		//printf("%d %d\n",now, size);
		for(int i = 0; i < size; i++) {
			edge next = G[now][i];
			int flow = next.flow;
			int cap = next.cap;
			int to = next.to;
			int cost = next.cost;
			
			if (flow == cap) continue;
			
			//printf("now next %d %d\n",now, to);
			cost = cost*(flow*2 + 1);
			if (cost < 0 && flow >= 0) continue;
			
			if (cost < 0) {
				int rev = next.rev;
				int flowrev = G[to][rev].flow;
				
				cost = cost*((flowrev-1)*2 + 1);
			}
			
			//printf("%d %d %d\n",now, cost);
			if (dist[now] + cost < dist[to]) {
				dist[to] = dist[now] + cost;
				bt[to] = now;
				dari[to] = i;
				if (inQ[to] == 0) {
					inQ[to] = 1;
					q[++tail] = to;
				}
			}
		}
	}
	
	return bt[sink] != -1;
}

pii MCMF(int FLOW_MAX) {
	int ans = 0;
	int flow = 0;
	while(SPFA()) {
		int ptr = sink;
		ans += dist[sink];
		
		while(ptr != source) {
			int from = bt[ptr];
			int idx = dari[ptr];
			int rev = G[from][idx].rev;
			G[ptr][rev].flow -= 1;
			G[from][idx].flow += 1;
			ptr = from;
		}
		flow++;
		if (flow == FLOW_MAX) break;
	}
	return make_pair(flow, ans);
}

int main() {
	while(scanf("%d %d %d",&n, &m, &k) != EOF) { 
		
		for(int i = 1; i <= m; i++) {
			int ui, vi, ai, Ci;
			scanf("%d %d %d %d",&ui, &vi, &ai, &Ci);
			add(ui, vi, Ci, ai);
		}
		
		source = 1;
		sink = n;
		pii res = MCMF(k);
		
		if (res.first == k) printf("%d\n",res.second);
		else printf("-1\n");
		
		for(int i = 1; i <= n; i++) G[i].clear();
	}
}