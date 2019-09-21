#include<bits/stdc++.h>
using namespace std;

#define MAXN 305
#define MAX 90005
#define INF 1e9

int n, N;
int arr[MAXN][MAXN];
int source, sink;

struct edge{
	int to, rev;
	int flow, cap;
};

vector<edge> G[MAX];
int q[1000000], dist[MAX], work[MAX];

void add(int s, int t, int cap) {
	edge a = {t, G[t].size(), 0, cap};
	edge b = {s, G[s].size(), 0, 0};
	//cout << s << " " << t << " " << cap << endl;
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

int num[MAX];

vector<int> ans[MAX];
int main() {
	map<int,int> maps;
	map<int,int> rev;
	scanf("%d",&n);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			scanf("%d",&arr[i][j]);
			maps[arr[i][j]]++;
		}
	}
	int cnt = 0;
	for(map<int,int>::iterator it = maps.begin(); it != maps.end(); it++) {
		rev[it->first] = ++cnt;
		num[cnt] = it->first;
	}
	
	source = 0;
	N = n + cnt + 3;
	sink = n + cnt + 2;
	//cout << source << " X " << sink << endl;
	for(int diag = n; diag >= 1; diag--) {
		add(source, diag, 2);
		int row = diag;
		int col = 1;
		while(row > 0) {
			add(diag, n+rev[arr[row][col]], 1);
			row--; col++;
		}
	}
	//cout << " BATAS : " << N << endl;
	for(int i = 1; i <= cnt; i++) add(n+i, sink, 1);
	
	int max_flow = maxflow();
	//printf("MAX FLOW %d\n",max_flow);
	if (max_flow < 2*n - 1) printf("NO\n");
	else {
		printf("YES\n");
		
		for(int diag = n; diag >= 1; diag--) {
			int size = G[diag].size();
			for(int i = 0; i < size; i++) {
				if (G[diag][i].flow == G[diag][i].cap) {
					int to = G[diag][i].to - n;
					ans[diag].push_back(num[to]);
				}
			}
		}
		
		vector<int> res;
		for(int diag = n; diag >= 2; diag--) {
			res.push_back(ans[diag][1]);
			ans[diag].pop_back();
		}
		
		res.push_back(ans[1][0]);
		
		for(int diag = 2; diag <= n; diag++) {
			res.push_back(ans[diag][0]);
		}
		
		for(int i = 0; i < (int)res.size(); i++) {
			if (i == (int)res.size() - 1) {
				printf("%d\n",res[i]);
			} else {
				printf("%d ",res[i]);
			}
		}
	}
}
