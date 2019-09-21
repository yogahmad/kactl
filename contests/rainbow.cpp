#include<bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
#define pb push_back
#define MAX 200005
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> pip;
const int root = 0;
int tc, n, m, ptr, cnt;
long long ans = 0;
int P[MAX][25];
int L[MAX], sub[MAX], arr[MAX];
int lg[MAX];
int ChainHead[MAX], indx[MAX], ChainNo[MAX];
int ChainTail[MAX];
int tree[4*MAX][8], lazy[4*MAX][8];
long long color[9];
vector<int> v[MAX];
vector<int> child[MAX];
char ch[50];

inline void precomp() {
	for(int i = 0; i < MAX; i++) {
		int T = 0;
		for(T = 1; (1 << T) <= i; T++); T--;
		lg[i] = T;
	}
}

void dfs(int now, int depth, int par) {
	int size = v[now].size();
	L[now] = depth;
	P[now][0] = par;
	sub[now] = 1;
	for(int i = 0; i < size; i++) {
		int next = v[now][i];
		if (next != par) {
			child[now].pb(next);
			dfs(next, depth + 1, now);
			sub[now] += sub[next];
		} 
	}
}

inline void makeP() {
	int logg = lg[n];
	for(int j = 1; j <= logg; j++) {
		for(int i = 1; i <= n; i++) {
			if (P[i][j - 1] != -1) {
				P[i][j] = P[P[i][j - 1]][j - 1];
			}
		}
	}
}

inline int LCA(int p, int q) {
	if (L[p] < L[q]) swap(p, q);
	int logg = lg[L[p]];
	for(int i = logg; i >= 0; i--) {
		if (L[p] - (1 << i) >= L[q]) {
			p = P[p][i];
		}
	}
	if (p == q) return p;	
	for(int i = logg; i >= 0; i--) 
		if (P[p][i] != -1 && P[p][i] != P[q][i]) 
			p = P[p][i], q = P[q][i];
		
	return P[p][0];
}
void HLD(int now) {
	if (ChainHead[cnt] == -1) {
		ChainHead[cnt] = now;
	}
	ChainNo[now] = cnt;
	indx[now] = ptr;
	int sc = -1, size = child[now].size(), next;
	if (size == 0) ChainTail[cnt] = now;
	ptr += 1;
	for(int i = 0; i < size; i++) {
		next = child[now][i];
		if (sc == -1 || sub[sc] < sub[next]) sc = next;
	}
	
	if (sc != -1) HLD(sc);
	
	for(int i = 0; i < size; i++) {
		next = child[now][i];
		if (sc != next) {
			cnt += 1;
			HLD(next);
		}
	}
}

inline void jumlah(int node, int l, int r) {
	for(int i = 1; i <= 7; i++) {
		tree[node][i] = tree[node<<1][i] + tree[node<<1|1][i];
	}
}

inline void propagate(int node, int l, int r) {
	int jmp = 0;
	for(int i = 1; i <= 7; i++) jmp += lazy[node][i];
	if (jmp == 0) return;
	for(int i = 1; i <= 7; i++) {
		if (lazy[node][i] == 0) tree[node][i] = 0;
		else tree[node][i] = r - l + 1;
		if (lazy[node][i] > 0 && l != r) {
			for(int j = 1; j <= 7; j++) {
				lazy[node<<1][j] = 0;
				lazy[node<<1|1][j] = 0;
			}
			lazy[node<<1][i] += lazy[node][i];
			lazy[node<<1|1][i] += lazy[node][i];
		}
		lazy[node][i] = 0;
	}
}
int jum = 0;
int ca , cb ;
void update(int node, int l, int r, int a, int b, int v) {
	propagate(node, l, r);
	if (l > b || r < a) return;
	if (a <= l && r <= b) {
		lazy[node][v] += 1;
		jum += tree[node][v];
		propagate(node, l, r);
		return;
	}
	int mid = (l + r) >> 1;
	update(node<<1, l, mid, a, b, v);
	update(node<<1|1, mid + 1, r, a, b, v);
	if (ca <= l && r <= cb) jumlah(node, l, r);
}

inline int query_up(int u, int v, int col) {
	int uchain = ChainNo[u];
	int vchain = ChainNo[v];
	int res = 0;
	while(true) {
		ca = indx[ChainHead[uchain]];
		cb = indx[ChainTail[uchain]];
		if (uchain == vchain) {
			if (u != v) {
				jum = 0;
				update(1, 1, ptr - 1, indx[v] + 1, indx[u], col);
				res += jum;
			}
			break;
		}
		jum = 0;
		update(1, 1, ptr - 1, indx[ChainHead[uchain]], indx[u], col);
		res += jum;
		u = ChainHead[uchain];
		u = P[u][0];
		uchain = ChainNo[u];
	}
	return res;
}

int main() {

	scanf("%d",&n);
	for(int i = 1; i < n; i++) {
		int a, b, w;
		scanf("%d %d",&a, &b);
		v[a].pb(b);
		v[b].pb(a);
	}
	
		
	precomp();
	memset(P, -1, sizeof(P));
	memset(L, -1, sizeof(L));
	memset(ChainHead, -1, sizeof(ChainHead));
	memset(ChainTail, -1, sizeof(ChainTail));
	ptr = 0, cnt = 1;
	dfs(root, 1, -1);
	makeP();
	HLD(root);
	ans = 0;
	
	scanf("%d",&m);
	while(m--) {
		int u, v, col;
		scanf("%d %d %s",&u, &v, &ch);
		if (ch[0] == 'r') {
			col = 1;
		} else if (ch[0] == 'o') {
			col = 2;
		} else if (ch[0] == 'y') {
			col = 3;
		} else if (ch[0] == 'g') {
			col = 4;
		} else if (ch[0] == 'b') {
			col = 5;
		} else if (ch[0] == 'i') {
			col = 6;
		} else if (ch[0] == 'v') {
			col = 7;
		}
		int ancestor = LCA(u,v);
		long long path = L[u] + L[v] - 2*L[ancestor];
		long long x = - query_up(u, ancestor, col); 
		long long y = - query_up(v, ancestor, col);
		color[col] += path + x + y;
	}
	
	printf("red %lld\n",color[1]);
	printf("orange %lld\n",color[2]);
	printf("yellow %lld\n",color[3]);
	printf("green %lld\n",color[4]);
	printf("blue %lld\n",color[5]);
	printf("indigo %lld\n",color[6]);
	printf("violet %lld\n",color[7]);
}