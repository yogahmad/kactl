#include<bits/stdc++.h>
using namespace std;

#define pii pair<int,int>
#define f first
#define s second
#define mp make_pair
#define pb push_back
#define pf push_front

inline int ask_interactive(int x) {
	printf("? %d\n",x);
	fflush(stdout);
	int has;
	scanf("%d",&has);
	return has;
}

#define LL long long
#define MAX 100005
#define MAXE 250005


double EPS = 1e-9;
int INF = 1e9+7;;
long long INFLL = 1e17;
double pi = acos(-1);

int N;
int source, sink;
int dist[MAXE];
int work[MAXE];
int q[MAXE*10];

struct edge{
	int to, rev;
	int flow, cap;
};

vector<edge> G[MAXE];

inline void add(int s, int t, int cap) {
	edge a = {t, G[t].size(), 0, cap};
	edge b = {s, G[s].size(), 0,   0};
	G[s].push_back(a);
	G[t].push_back(b);
}

inline bool search() {
	for(int i = 0; i <= N + 1; i++) dist[i] = -1;
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
	if (now == sink)
		return flo;
	
	int size = G[now].size();
	for(int &i = work[now]; i < size; i++) {
		int to = G[now][i].to;
		int flow = G[now][i].flow;
		int cap = G[now][i].cap;
		int rev = G[now][i].rev;
		
		if (flow >= cap) continue;
		
		if (dist[to] == dist[now] + 1) {
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
	while(search()) {
		for(int i = 0; i <= N + 1; i++) work[i] = 0;
		while(true) {
			int res = dinic(source, INF);
			if (res == 0) break;
			ans += res;
		}
	}
	return ans;
}

int n, m;
int arr[505][505];
int nilai[505][505];

inline int node(int A, int B) {
	return A*(n-1) + B;
}

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--) {
		scanf("%d %d",&n, &m);
		
		source = n*m + 1;
		sink = n*m + 2;
		
		N = n*m + 2;
		
		int x, y;
		int sum = 0;
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				scanf("%d",&arr[i][j]);
				if (arr[i][j] == -1) x = i, y = j, nilai[i][j] = INF;
				else sum += arr[i][j], nilai[i][j] = arr[i][j];
				if ( (i + j)%2 == 0 ) {
					add(source, node(i,j), nilai[i][j]);
					if (i != 1) add(node(i,j), node(i-1,j), INF);
					if (i != n) add(node(i,j), node(i+1,j), INF);
					if (j != 1) add(node(i,j), node(i,j-1), INF);
					if (j != m) add(node(i,j), node(i,j+1), INF);
				} else {
					add(node(i,j), sink, nilai[i][j]);
				}
				
				
			}
		}
		
		printf("%d\n",maxflow()*2 - sum);
		
		for(int i = 0; i < MAXE; i++) G[i].clear();
	}
}