#include<bits/stdc++.h>
#define LL long long
#define MAX 100005
using namespace std;
int n;

LL tree[4*MAX];
LL A[4*MAX];
int par[4*MAX];

void update(int now, int l, int r, int pos, LL val) {
	if (l == r) {
		tree[now] = val;
		return;
	}
	
	int mid = (l + r) >> 1;
	
	if (pos <= mid) update(now << 1, l, mid, pos, val);
	else update(now<<1|1, mid + 1, r, pos, val);

	tree[now] = tree[now << 1] + tree[now<<1|1];
}

LL query(int now, int l, int r, int a, int b) {
	if (a > r || b < l) return 0LL;
	if (a <= l && r <= b) return tree[now];
	int mid = (l + r) >> 1;
	return query(now << 1, l, mid, a, b) + query(now<<1|1, mid + 1, r, a, b);
}

int find(int x) {
	return par[x] = (par[x] == x) ? x : find(par[x]);
}


int main() {
	int cs = 0;
	while(scanf("%d",&n) != EOF) {
	
		for(int i = 1; i < 4*MAX; i++) tree[i] = 0, par[i] = 0, A[i] = 0;

		for(int i = 1; i <= n; i++) {
			scanf("%lld",&A[i]);
			update(1, 1, n, i, A[i]);
		}
		
		for(int i = n; i >= 1; i--) {
			if (A[i] == 1) {
				par[i] = i;
				if (A[i+1] == 1) par[i] = par[i+1];
			}
		}
	
		cs++;
		printf("Case #%d:\n", cs);
		
		int q;
		scanf("%d",&q);
		while(q--) {
			int cmd, x, y;
			scanf("%d %d %d",&cmd, &x, &y);
			if (x > y) swap(x, y);
			if (cmd == 1) printf("%lld\n",query(1, 1, n, x, y));
			else {
				for(int i = x; i <= y; i++) {
					if (A[i] == 1) {
						i = find(par[i]);
						continue;
					}
					A[i] = sqrt(A[i]);
					//printf("%d %d\n",i, A[i]);
					if (A[i] == 1) {
						par[i] = i;
						if (A[i + 1] == 1) par[i] = find(par[i + 1]);
						if (A[i - 1] == 1) par[i-1] = par[i];
					}
					update(1, 1, n, i, A[i]);
				}
			}
		}
		
		printf("\n");
	}
}