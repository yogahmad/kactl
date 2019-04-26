#include<bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
#define pb push_back
#define MAX 10005
#define INF 1000000000
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> pip;
const int root = 1;
int tc, n, m, ptr, cnt;
long long ans = 0;
int P[MAX][16];
int L[MAX], sub[MAX], arr[MAX];
int lg[MAX];
int ChainHead[MAX], indx[MAX], ChainNo[MAX];
int Tmax[4*MAX];
int Tmin[4*MAX], lazy[4*MAX];
long long PPTR[MAX];
pip E[10*MAX];
vector<pii> v[MAX];
vector<pip> tree[MAX];
vector<int> child[MAX];
vector<pii> costs[MAX];
inline void precomp() {
	for(int i = 0; i < MAX; i++) {
		int T = 0;
		for(T = 1; (1 << T) <= i; T++); T--;
		lg[i] = T;
	}
}
inline void fastRead_int(int &x) {
    register int c = getchar_unlocked();
    x = 0;
    for(; ((c<48 || c>57) && c != '-'); c = getchar_unlocked());
    for(; c>47 && c<58 ; c = getchar_unlocked()) {
    	x = (x<<1) + (x<<3) + c - 48;
    }
} 
inline void clear(int len) {
	ptr = 0;
	cnt = 1;
	for(int i = 0; i < len; i++) {
		v[i].clear();
		tree[i].clear();
		child[i].clear();
		costs[i].clear();
		PPTR[i] = -1;
		L[i] = ChainHead[i] = -1;
		indx[i] = arr[i] = ChainNo[i] = sub[i] = 0;
		Tmax[i] = Tmax[len + i] = Tmax[len*2 + i] = Tmax[len*3 + i] = 0;
		Tmin[i] = Tmin[len + i] = Tmin[len*2 + i] = Tmin[len*3 + i] = INF;
		lazy[i] = lazy[len + i] = lazy[len*2 + i] = lazy[len*3 + i] = INF;
		for(int j = 0; j <= lg[len]; j++) P[i][j] = -1;
	}
}

void dfs(int now, int depth, int par) {
	int size = tree[now].size();
	L[now] = depth;
	P[now][0] = par;
	sub[now] = 1;
	for(int i = 0; i < size; i++) {
		int next = tree[now][i].s.f;
		if (next != par) {
			child[now].pb(next);
			costs[now].pb(mp(tree[now][i].s.s,tree[now][i].f));
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
	if (L[p] < L[q]) {
		int tmp = p;
		p = q;
		q = tmp;
	}
	
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

void HLD(int now, int cost, int id) {
	if (ChainHead[cnt] == -1) ChainHead[cnt] = now;
	ChainNo[now] = cnt;
	indx[now] = ptr;
	arr[ptr] = cost;
	PPTR[ptr] = id;
	ptr += 1;
	int sc = -1, lastcost, size = child[now].size(), next, idp;
	for(int i = 0; i < size; i++) {
		next = child[now][i];
		if (sc == -1 || sub[sc] < sub[next]) {
			sc = next;
			lastcost = costs[now][i].f;
			idp = costs[now][i].s;
		} 
	}
	
	if (sc != -1) HLD(sc, lastcost, idp);
	
	for(int i = 0; i < size; i++) {
		next = child[now][i];
		if (sc != next) {
			cnt += 1;
			HLD(next, costs[now][i].f, costs[now][i].s);
		}
	}
}
void build(int node, int l, int r) {
	if (l == r) {
		Tmax[node] = arr[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(node<<1, l, mid);
	build(node<<1|1, mid + 1, r);
	Tmax[node] = (Tmax[node<<1] > Tmax[node<<1|1]) ? Tmax[node<<1] : Tmax[node<<1|1];
}

int query_tree(int node, int l, int r, int a, int b) {
	if (r < a || b < l) return -INF;
	if (a <= l && r <= b) return Tmax[node];
	int mid = (l + r) >> 1;
	int q1 = query_tree(node<<1, l, mid, a, b);
	int q2 = query_tree(node<<1|1, mid + 1, r, a, b);
	return (q1 > q2) ? q1 : q2;
}

void update(int node, int l, int r, int a, int b, int v) {
	if (lazy[node] != INF) {
		Tmin[node] = (lazy[node] < Tmin[node]) ? lazy[node] : Tmin[node];
		if (l != r) {
			lazy[node<<1] = (lazy[node<<1] > lazy[node]) ? lazy[node] : lazy[node<<1];
			lazy[node<<1|1] = (lazy[node<<1|1] > lazy[node]) ? lazy[node] : lazy[node<<1|1];
		}
		lazy[node] = INF;
	}
	if (r < a || b < l) return;
	if (a <= l && r <= b) {
		// printf("%d %d\n",l,r);
		Tmin[node] = (Tmin[node] > v)  ? v : Tmin[node];
		lazy[node] = v;
		if (l != r) {
			lazy[node<<1] = (lazy[node<<1] > lazy[node]) ? lazy[node] : lazy[node<<1];
			lazy[node<<1|1] = (lazy[node<<1|1] > lazy[node]) ? lazy[node] : lazy[node<<1|1];
		}
		lazy[node] = INF;
		return;
	}
	int mid = (l + r) >> 1;
	update(node<<1, l, mid, a, b, v);
	update(node<<1|1, mid + 1, r, a, b, v);
}

inline int query_up(int u, int v, int w) {
	int uchain = ChainNo[u];
	int vchain = ChainNo[v];
	int ret = 0;
	while(true) {
		if (uchain == vchain) {
			if (u != v) {
				int res = query_tree(1, 1, ptr - 1, indx[v] + 1, indx[u]);
				update(1, 1, ptr - 1, indx[v] + 1, indx[u], w);
				if (res > ret) ret = res;
			}
			break;
		}
		int res = query_tree(1, 1, ptr - 1, indx[ChainHead[uchain]], indx[u]);
		update(1, 1, ptr - 1, indx[ChainHead[uchain]], indx[u], w);
		if (res > ret) ret = res;
		u = ChainHead[uchain];
		u = P[u][0];
		uchain = ChainNo[u];
	}
	return ret;
}

void PostOrder(int node, int l, int r, int w) {
	w = (lazy[node] < w) ? lazy[node] : w;
	w = (Tmin[node] < w) ? Tmin[node] : w;
	// printf("%d %d %d %d %d\n",l,r, w, lazy[node],Tmin[node]);
	if (l == r) {
		// printf("%d %d\n",PPTR[l], w);
		if (w == INF) ans += (long long)(-PPTR[l] - PPTR[l]*PPTR[l]);
		else ans += (long long)(PPTR[l]*(w - E[PPTR[l]].f) - PPTR[l]*PPTR[l]);
		return; 
	}
	int mid = (l + r) >> 1;
	PostOrder(node<<1, l, mid, w);
	PostOrder(node<<1|1, mid + 1, r, w);
}

int main() {
	precomp();
	clear(MAX);
	fastRead_int(tc);
	for(int cs = 1; cs <= tc; cs++) {
		fastRead_int(n);
		fastRead_int(m);
		clear(n + 1);	
		for(int i = 1; i <= m; i++) {
			int a, b, w;
			fastRead_int(a);
			fastRead_int(b);
			fastRead_int(w);	
			v[a].pb(mp(b,w));
			v[b].pb(mp(a,w));
			E[i] = (mp(w,mp(a,b)));
			if (i < n) {
				tree[a].pb(mp(i,mp(b,w)));
				tree[b].pb(mp(i,mp(a,w)));
			}
		}
		
		dfs(root, 1, -1);
		makeP();
		HLD(root, -1, -1);
		build(1,1,ptr-1);
		ans = 0;
		
		for(long long i = n; i <= m; i++) {
			int lca = LCA(E[i].s.f, E[i].s.s);
			int aa = query_up(E[i].s.f, lca, E[i].f);
			int bb = query_up(E[i].s.s, lca, E[i].f);
			ans += (long long)(-i + i*i*(E[i].f - ((aa < bb) ? bb : aa)));
		}
		
		PostOrder(1, 1, ptr - 1, INF);
		printf("Case %d: %lld\n",cs,ans);
	}
}