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
int flag[MAXE];
int parent[MAXE];
int idx[MAXE];

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

inline int maxflow() {
	int ans = 0;
	int day = 0;
	for(int i = 0; i <= N; i++) flag[i] = 0;
	while(true) {
		queue<int> q; q.push(source); 
		flag[source] = ++day;
		while (!q.empty()) {
			int f = q.front(); 
			q.pop();
			if (f == sink) break;
			int size = G[f].size();
			for (int i = 0; i < size; i++) {
				int t = G[f][i].to;
				int cap = G[f][i].cap;
				if (cap > 0 && flag[t] != day) {
					q.push(t), flag[t] = day, parent[t] = f;
					idx[t] = i;
				}
			}
		}
		
		if (flag[sink] != day) break;
		
		int aug = INF;
		int ptr = sink;
		while(ptr != source) {
			int from = parent[ptr];
			int id = idx[ptr];
			aug = min(aug, G[from][id].cap);
			ptr = from;
		}
		
		// printf("%d\n",aug); cin.ignore();
		ans += aug;
		
		ptr = sink;
		while(ptr != source) {
			int from = parent[ptr];
			int id = idx[ptr];
			int rev = G[from][id].rev;
			G[from][id].cap -= aug;
			G[ptr][rev].cap += aug;
			ptr = from;
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
		
		for(int i = 0; i <= N; i++) G[i].clear();
	}
}