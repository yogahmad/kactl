#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
#define f first
#define s second
#define mp make_pair

const int INF = 2e9+5;

const int N = 1e5 + 5;

pair<int,int> tree[4][4*N];

int n, q;
int x[N], y[N];

pii query(int no, int now, int l, int r, int a, int b) {
	if (r < a || b < l) {
		if (no == 0 || no == 2) {
			return mp(INF, 0);
		} else {
			return mp(-INF, 0);
		}
	}
	if (a <= l && r <= b){
		return tree[no][now];
	}
	int mid = (l + r) >> 1;
	pii ki = query(no, now << 1, l, mid, a, b);
	pii ka = query(no, now << 1 | 1, mid + 1, r, a, b);
	
	if (no == 0 || no == 2) {
		if (ki.first < ka.first) return ki;
		else return ka;
	} else {
		if (ki.first > ka.first) return ki;
		else return ka;
	}
}

void update(int no, int now, int l, int r, int pos, int val) {
	if (l == r) {
		tree[no][now] = mp(val, l);
		return;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid) update(no, now<<1, l, mid, pos, val);
	else update(no, now<<1|1, mid + 1, r, pos, val);
	
	if (no == 0 || no == 2) {
		if (tree[no][now<<1].first < tree[no][now<<1|1].first) {
			tree[no][now] = tree[no][now<<1];
		} else {
			tree[no][now] = tree[no][now<<1|1];
		}
	} else {
		if (tree[no][now<<1].first > tree[no][now<<1|1].first) {
			tree[no][now] = tree[no][now<<1];
		} else {
			tree[no][now] = tree[no][now<<1|1];
		}
	}
}

ll go(int a, int b, pii res) {
	update(0, 1, 1, n, res.second, INF);
	update(1, 1, 1, n, res.second, -INF);
	update(2, 1, 1, n, res.second, INF);
	update(3, 1, 1, n, res.second, -INF);
	
	ll minx, maxx, miny, maxy;
	ll semua = 0;
	
	minx = query(0, 1, 1, n, a, b).first;
	maxx = query(1, 1, 1, n, a, b).first;
	miny = query(2, 1, 1, n, a, b).first;
	maxy = query(3, 1, 1, n, a, b).first;
	semua = max(maxx - minx, maxy - miny);
	//printf("ww %lld %lld\n", maxx, minx);
	for(int j = 0; j < 4; j++) {
		update(j, 1, 1, n, res.second, res.first);
	}
	return semua;
}

int main() {

	scanf("%d %d",&n, &q);
	for(int i = 1; i <= n; i++) {
		scanf("%d %d",&x[i], &y[i]);
		update(0, 1, 1, n, i, x[i]);
		update(1, 1, 1, n, i, x[i]);
		update(2, 1, 1, n, i, y[i]);
		update(3, 1, 1, n, i, y[i]);
	}
	
	for(int i = 1; i <= q; i++) {
		int a, b;
		scanf("%d %d",&a, &b);
		
		ll ans = 4e18;
		ans = min(ans, go(a, b, query(0, 1, 1, n, a, b)));
		ans = min(ans, go(a, b, query(1, 1, 1, n, a, b)));
		ans = min(ans, go(a, b, query(2, 1, 1, n, a, b)));
		ans = min(ans, go(a, b, query(3, 1, 1, n, a, b)));
		
		printf("%lld\n",ans);
		
	}
	return 0;
}