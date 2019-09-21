#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MAX = 1800;

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

int n, a, b, c;

inline int node(int x, int y, int z) {
	return 144*z + 12*y + x;
}

int dx[] = {0, 0, 1,-1, 0, 0};
int dy[] = {0, 0, 0, 0, 1,-1};
int dz[] = {1,-1, 0, 0, 0, 0};

void sebar(int x, int y, int z) {
	if (x == 0 || y == 0 || z == 0 || x == 11 || y == 11 || z == 11) {
		add(node(x,y,z), sink, 1);
	} else {
		for(int i = 0; i < 6; i++) {
			add(node(x,y,z), node(x+dx[i],y+dy[i],z+dz[i]),1);
		}
	}
}

int tc;
int main() {
	source = MAX-2;
	sink = MAX-3;
	
	scanf("%d",&tc);
	while(tc--) {
		for(int i = 0; i < MAX; i++) G[i].clear();
		
		scanf("%d",&n);
		for(int i = 1; i <= n; i++) {
			scanf("%d %d %d",&a, &b, &c);
			a++, b++, c++;
			add(source, node(a,b,c), 6);
		}
		
		for(int x = 0; x <= 11; x++) {
			for(int y = 0; y <= 11; y++) {
				for(int z = 0; z <= 11; z++) {
					sebar(x, y, z);
				}
			}
		}
		
		printf("%d\n",maxflow());
	}
}