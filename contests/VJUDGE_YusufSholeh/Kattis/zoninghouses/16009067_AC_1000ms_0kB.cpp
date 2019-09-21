#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define f first
#define s second
#define mp make_pair

const ll INF = 3e18+5;

const ll N = 1e5 + 5;

pair<ll,ll> tree[4][4*N];

ll n, q;
ll x[N], y[N];

pii query(ll no, ll now, ll l, ll r, ll a, ll b) {
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
	ll mid = (l + r) >> 1;
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

void update(ll no, ll now, ll l, ll r, ll pos, ll val) {
	if (l == r) {
		tree[no][now] = mp(val, l);
		return;
	}
	ll mid = (l + r) >> 1;
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

ll go(ll a, ll b, pii res) {
	//printf("PERTAMA %lld %lld\n",res.first, res.second);
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
	//printf("ww %lld %lld\n", maxy, miny);
	
	update(0, 1, 1, n, res.second, x[res.second]);
	update(1, 1, 1, n, res.second, x[res.second]);
	update(2, 1, 1, n, res.second, y[res.second]);
	update(3, 1, 1, n, res.second, y[res.second]);
	
	//printf("DAPAT %lld\n",semua);
	return semua;
}

int main() {

	scanf("%lld %lld",&n, &q);
	for(ll i = 1; i <= n; i++) {
		scanf("%lld %lld",&x[i], &y[i]);
		update(0, 1, 1, n, i, x[i]);
		update(1, 1, 1, n, i, x[i]);
		update(2, 1, 1, n, i, y[i]);
		update(3, 1, 1, n, i, y[i]);
	}
	
	for(ll i = 1; i <= q; i++) {
		ll a, b;
		scanf("%lld %lld",&a, &b);
		
		ll ans = 4e18;
		ans = min(ans, go(a, b, query(0, 1, 1, n, a, b)));
		ans = min(ans, go(a, b, query(1, 1, 1, n, a, b)));
		ans = min(ans, go(a, b, query(2, 1, 1, n, a, b)));
		ans = min(ans, go(a, b, query(3, 1, 1, n, a, b)));
		
		printf("%lld\n",ans);
		
	}
	return 0;
}