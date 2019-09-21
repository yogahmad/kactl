#include<bits/stdc++.h>
using namespace std;

#define MAXN 25005
#define MAXM 50005
#define INF 1e9

typedef pair<int,int> pii;
#define f first
#define s second
#define mp make_pair

const int debug_djikstra = 0;
const int debug_sorted_commuter = 0;

int n, m, c;
int source, sink = 0;
int reset_flow_day = 0;

vector<pii> v[MAXM];

struct edge{
	int to, rev;
	int flow, cap;
	bool is_back_edge;
	int flow_day;
};

vector<edge> G[MAXM];

int q[MAXM*3];
int day(1);
int work[MAXM], work_day[MAXM];
int dist[MAXM], dist_day[MAXM];

inline void add_edge(int s, int t, int cap) {
	edge a = {t, G[t].size(), 0, cap, 0, 0};
	edge b = {s, G[s].size(), 0,   0, 1, 0};
	G[s].push_back(a);
	G[t].push_back(b);
}

inline bool search() {
	dist[source] = 0; dist_day[source] = day;
	int tail = 0;
	q[tail] = source;
	for(int head = 0; head <= tail; head++) {
		int u = q[head];
		int sz = G[u].size();
		for(int i = 0; i < sz; i++) {
			int v = G[u][i].to;
			if (G[u][i].flow_day != reset_flow_day) {
				G[u][i].flow_day = reset_flow_day;
				G[u][i].flow = 0;
			}
			if (dist_day[v] != day) {
				dist_day[v] = day;
				dist[v] = -1;
			}
			if (dist[v] < 0 && G[u][i].flow < G[u][i].cap) {
				dist[v] = dist[u] + 1;
				q[++tail] = v;
			}
		}
	}
	
	return (dist_day[sink] == day);
}

int dinic(int now, int flo) {
	if (now == sink)
		return flo;
	
	int size = G[now].size();
	
	if (work_day[now] != day) {
		work_day[now] = day;
		work[now] = 0;
	}
	for(int &i = work[now]; i < size; i++) {
		int to = G[now][i].to;
		int flow = G[now][i].flow;
		int cap = G[now][i].cap;
		int rev = G[now][i].rev;
		
		if (G[now][i].flow_day != reset_flow_day) {
			G[now][i].flow_day = reset_flow_day;
			G[now][i].flow = 0;
		}
		if (flow >= cap) continue;
		
		if (dist_day[to] == day && dist[to] == dist[now] + 1) {
			int fflow = dinic(to, min(flo, cap - flow));
			
			if (fflow) {
				G[now][i].flow  += fflow;
				G[to][rev].flow -= fflow;
				return fflow;
			}
		}
	}
	
	return 0;
}

inline int maxflow() {
	int ans = 0;
	day++;
	reset_flow_day++;
	while(search()) {
		while(true) {
			int res = dinic(source, INF);
			if (res == 0) break;
			ans += res;
		}
		day++;
	}
	return ans;
}

int djikstra[MAXN];
bool flag[MAXN];

inline void generate_djikstra() {
	for(int i = 1; i <= n; i++) djikstra[i] = INF, flag[i] = false;
	djikstra[1] = 0;
	priority_queue<pii, vector<pii>, greater<pii> > pq;
	pq.push(mp(0, 1));
	while(!pq.empty()) {
		pii top = pq.top();
		pq.pop();
		
		int now = top.s;
		int d = top.f;
		if (flag[now] || djikstra[now] < d) continue;
		flag[now] = true;
		
		int size = v[now].size();
		for(int i = 0; i < size; i++) {
			int next = v[now][i].f;
			int jar = v[now][i].s;
			
			if (flag[next] == false && djikstra[next] > d + jar) {
				djikstra[next] = d + jar;
				pq.push(mp(djikstra[next], next));
			}
		}
	}
	if (debug_djikstra) {															// <-- debug djikstra here
		for(int i = 1; i <= n; i++) {
			printf("nodes: %d, distance: %d\n",i, djikstra[i]);
		}
	}
}

bool cmp(int a, int b) {
	return djikstra[a] < djikstra[b];
}

int number_commuter[MAXM];
int commuter[MAXM];
pair<int,pii> edge_list[MAXM];

int solve() {
	sort(commuter + 1, commuter + c + 1, cmp);
	if (debug_sorted_commuter) {									// <-- debug sorted commuter here
		for(int i = 1; i <= c; i++) {
			printf("commuter at %d, distance %d\n",commuter[i], djikstra[commuter[i]]);
		}
	}
	int ans = 0;
	source = 0;
	sink = n + 1;
	add_edge(1, sink, INF);
	
	for(int i = 1; i <= c; i++) {
		int j;
		for(j = i; j <= c; j++) {
			if (djikstra[commuter[j]] != djikstra[commuter[i]]) {
				j--;
				break;
			}
		}
		if (i == j) {
			ans++;
			continue;
		}
		G[source].clear();
		for(int k = i; k <= j; k++) {
			if (number_commuter[commuter[k]] == 0) continue;
			add_edge(source, commuter[k], number_commuter[commuter[k]]);
			number_commuter[commuter[k]] = 0;
		}
		ans += maxflow();
	}
	
	return ans;
}

inline void clear_data() {
	for(int i = 0; i <= n+1; i++) {
		v[i].clear();
		G[i].clear();
		number_commuter[i] = 0;
	}
}

int main() {
	while(scanf("%d %d %d",&n, &m, &c) != EOF) {
		for(int i = 1; i <= m; i++) {
			int U, V, W; scanf("%d %d %d",&U, &V,&W);
			edge_list[i] = mp(W, mp(U, V));
			v[U].push_back(mp(V,W));
			v[V].push_back(mp(U,W));
		}
		for(int i = 1; i <= c; i++) scanf("%d",&commuter[i]), number_commuter[commuter[i]]++;
		generate_djikstra();	
		for(int i = 1; i <= m; i++) {
			int x = edge_list[i].s.f;
			int y = edge_list[i].s.s;
			int z = edge_list[i].f;
			if (djikstra[x] > djikstra[y]) swap(x,y);
			if (djikstra[y] == djikstra[x] + z) add_edge(y, x, 1);
		}
		printf("%d\n",solve());
		clear_data();
	}
}