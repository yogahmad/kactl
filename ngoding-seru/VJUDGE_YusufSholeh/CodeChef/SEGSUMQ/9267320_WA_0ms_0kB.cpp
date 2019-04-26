#include<bits/stdc++.h>
using namespace std;

#define LL long long

typedef pair<LL,LL> pii;
#define f first
#define s second
#define mp make_pair
#define MAX 100005

LL cross(pii x, pii y) { //x=(C,D), y=(A,B)
	return x.f*y.s - x.s*y.f;
}

LL N;
LL A[MAX], B[MAX];

struct inner{
	
	vector<pii> values;
	vector<pii> prefix;
	
	void insert(pii T) {
		values.push_back(T);
	}
	
	void compute_prefix() {
		int size = values.size();
		LL sumA = 0, sumB = 0;
		for(int i = 0; i < size; i++) {
			sumA += values[i].s;
			sumB += values[i].f;
			prefix.push_back(mp(sumA, sumB));
		}
	}
	
} tree[4*MAX];

bool cmp(pii a, pii b) { // a.s/a.f di a > b.s/b.f di b -> a.s * b.f > b.s * a.f
	return a.s * b.f > b.s * a.f;
}

void build(int now, int l, int r) {
	
	if (l == r) {
		tree[now].insert(mp(B[l], A[l]));
		tree[now].prefix.push_back(mp(A[l], B[l]));
		return;
	}
	
	int mid = (l + r) >> 1;
	build(now << 1, l, mid);
	build(now << 1 | 1, mid + 1, r);
	
	vector<pii> left = tree[now<<1].values; int sz_left = left.size();
	vector<pii> right = tree[now<<1|1].values; int sz_right = right.size();
	
	
	int i = 0, j = 0;
	while(i < sz_left || j < sz_right) {
		if (i == sz_left) tree[now].insert(right[j++]);
		else if (j == sz_right) tree[now].insert(left[i++]);
		else {
			if (cmp(left[i], right[j])) {
				tree[now].insert(left[i++]);
			} else {
				tree[now].insert(right[j++]);
			}
		}
	}
	
	tree[now].compute_prefix();
}

LL queries(int now, int l, int r, int L, int R, pii Q) {
	if (r < L || R < l) return 0;
	if (L <= l && r <= R) {
		int l = 0, r = tree[now].values.size()-1;
		int maks = -1;
		while(l <= r) {
			int mid = (l + r) >> 1;
			if (cmp(tree[now].values[mid], Q)) {
				maks = mid;
				l = mid + 1;
			} else r = mid - 1;
		}
		if (maks == -1) return 0;
		pii take = tree[now].prefix[maks];
		return take.f * Q.f - take.s * Q.s;
	}
	int mid = (l + r) >> 1;
	return queries(now << 1, l, mid, L, R, Q) + 
	queries(now << 1 | 1, mid + 1, r, L, R, Q);
}

int main() {
	scanf("%lld",&N);
	for(int i = 1; i <= N; i++) scanf("%lld",&A[i]);
	for(int i = 1; i <= N; i++) scanf("%lld",&B[i]);
	
	build(1, 1, N);
	
	LL Q;
	scanf("%lld",&Q);
	while(Q--) {
		LL L, R, C, D; 
		scanf("%lld %lld %lld %lld",&L, &R, &C, &D);
		printf("%lld\n",queries(1, 1, N, L, R, mp(C,D)));
		fflush(stdout);
	}
}