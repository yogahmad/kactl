#include<bits/stdc++.h>
#define MAX 105
#define MAXP 1000006
#define INF 1000000000
using namespace std;

typedef pair<int, int> pii;
#define f first
#define s second
#define mp make_pair

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

int n, m;
int arr[MAX];
bool bol[MAXP];
bool prime[MAXP];

map<int,int> maps;
void generate_prime() {
	for(int i = 2; i < MAXP; i++) {
		if (bol[i] == false) {
			prime[i] = true;
			for(int j = i+i; j < MAXP; j += i) bol[j] = true;
		}
	}
}

int top[MAX];
pii node[MAX][12];
inline void factor(int index, int num) {
	int jmp = 0;
	top[index] = 0;
	for(int i = 2; i*i <= num; i++) {
		if (prime[i] && (num % i == 0)) {
			jmp++;
			int x = i;
			int cnt = 0;
			while(num > 0 && (num % x == 0)) {
				cnt++;
				num /= x;
			}
			node[index][++top[index]] = mp(i, cnt);
		}
	}
	if (num > 1) node[index][++top[index]] = (mp(num, 1));
	// for(int i = 1; i <= top[index]; i++) {
		// printf("%d %d\n",node[index][i].f, node[index][i].s);
	// }
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
		// printf("%d\n",day);
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
	}
	return ans;
}

int main() {
	generate_prime();
	
	scanf("%d %d",&n, &m);
	for(int i = 1; i <= n; i++) {
		scanf("%d",&arr[i]);
		factor(i, arr[i]);
	}
	
	source = 0;
	sink = 10*n + n + 1;
	
	for(int i = 1; i <= n; i++) {
		if (i % 2 == 1) {
			add(source, 10*n + i, INF);
			for(int j = 1; j <= top[i]; j++) {
				add(10*n + i, 10*(i-1) + j, node[i][j].s);
			}
		} else {
			add(10*n + i, sink, INF);
			for(int j = 1; j <= top[i]; j++) {
				add(10*(i-1) + j, 10*n + i, node[i][j].s);
			}
		}
	}
	
	// printf("ASDSA\n");
	for(int td = 1; td <= m; td++) {
		int a, b;
		scanf("%d %d",&a,&b);
		if (a % 2 == 0) swap(a,b);
		
		for(int i = 1; i <= top[a]; i++) {
			int x1 = node[a][i].f;
			for(int j = 1; j <= top[b]; j++) {
				int x2 = node[b][j].f;
				if (x1 == x2) {
					int a1 = arr[a];
					int a2 = arr[b];
					int cnt = 0;
					while(a1 && a2 && (a1 % x1 == 0) && (a2 % x1 == 0)) {
						a1 /= x1;
						a2 /= x1;
						cnt++;
					}
					add(10*(a-1) + i, 10*(b-1) + j, cnt);
				}
			}
		}
	}
	// printf("AZZ\n");
	printf("%d\n",maxflow());
}