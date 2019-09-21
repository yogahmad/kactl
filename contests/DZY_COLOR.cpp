#include<bits/stdc++.h>
#define MAX 100005
#define LL long long
using namespace std;

int n, m;

typedef pair<LL, LL> pii;

int sb[322], eb[322];
LL sum_bracket[322];
LL sum_per[MAX];
LL pref_bracket[322][322];
LL sorted_bracket[322][322];
LL real_bracket[MAX];
LL new_per[MAX];
int no_bracket[MAX];
int cnt = 0;
pii lazy[322];

inline void propagate(int no) {
	if (lazy[no].first == 0) return;
	int a = sb[no], b = eb[no];
	for(int i = a; i <= b; i++) {
		sum_per[i] += abs(real_bracket[i] - new_per[no]) + lazy[no].second;
		sorted_bracket[no][i-a+1] = lazy[no].first;
		pref_bracket[no][i-a+1] = pref_bracket[no][i-a] + lazy[no].first;
		real_bracket[i] = lazy[no].first;
	}
	lazy[no] = make_pair(0, 0);
	new_per[no] = 0;
}

inline void update(int no, int l, int r, LL val) {
	int a = sb[no], b = eb[no];
	for(int i = a; i <= b; i++) {
		if (i >= l && i <= r) {
			sum_bracket[no] -= sum_per[i];
			sum_per[i] += abs(val - real_bracket[i]);
			sum_bracket[no] += sum_per[i];
			real_bracket[i] = val;
		}
		sorted_bracket[no][i-a+1] = real_bracket[i];
	}
	
	sort(sorted_bracket[no] + 1, sorted_bracket[no] + b-a+2);
	for(int i = a; i <= b; i++) pref_bracket[no][i-a+1] = pref_bracket[no][i-a] + sorted_bracket[no][i-a+1];
}

inline LL query(int l, int r) {
	LL ret = 0;
	for(int i = l; i <= r; i++) ret += sum_per[i];
	return ret;
}

int main() {
	scanf("%d %d",&n, &m);
	
	
	for(int i = 1; i <= n; i++) {
		if (i % 320 == 1) {
			eb[cnt] = i-1;
			cnt++;
			sb[cnt] = i;
		}
		no_bracket[i] = cnt;
	} eb[cnt] = n;
	
	LL ki = 0;
	for(int i = 1; i <= cnt; i++) {
		for(int j = 1; j <= eb[i]-sb[i]+1; j++) {
			sorted_bracket[i][j] = ++ki;
			pref_bracket[i][j] = pref_bracket[i][j-1]  + ki;
			real_bracket[ki] = ki;
		}
	}
	
	while(m--) {
		int typ, l, r;
		LL x;
		scanf("%d",&typ);
		
		if (typ == 1) {
			scanf("%d %d %lld",&l,&r,&x);
			int no_l = no_bracket[l];
			int no_r = no_bracket[r];
			
			if (no_l == no_r) {
				propagate(no_l);
				update(no_l, l, r, x);
			} else {
				propagate(no_l); propagate(no_r);
				update(no_l, l, eb[no_l], x);
				update(no_r, sb[no_r], r, x);
				for(int i = no_l+1; i <= no_r-1; i++) {
					if (lazy[i].first != 0) {
						sum_bracket[i] = sum_bracket[i] + (LL)(eb[i] - sb[i]+1)*(abs(x - lazy[i].first));
						lazy[i].second += abs(lazy[i].first - x);
						lazy[i].first = x;
						continue;
					}
					new_per[i] = x;
					lazy[i].first = x;
					lazy[i].second = 0;
					int bnyk = eb[i] - sb[i] + 1;
					int l = 1, r = bnyk, mid;
					int ans = 0;
					while(l <= r) {
						mid = (l + r) >> 1;
						if (sorted_bracket[i][mid] <= x) {
							ans = mid;
							l = mid + 1;
						} else r = mid - 1;
					}
					LL sisa = bnyk - ans;
					sum_bracket[i] = sum_bracket[i] + (LL)ans*x - pref_bracket[i][ans];
					sum_bracket[i] = sum_bracket[i] + pref_bracket[i][bnyk] - pref_bracket[i][ans] - (LL)sisa*x;
				}
			}
		} else {
			scanf("%d %d",&l,&r);
			int no_l = no_bracket[l];
			int no_r = no_bracket[r];
			
			
			
			LL ans = 0;
			if (no_l == no_r) {
				propagate(no_l);
				ans += query(l, r);
			} else {
				propagate(no_l); propagate(no_r);
				ans += query(l, eb[no_l]);
				ans += query(sb[no_r], r);
				for(int i = no_l + 1; i <= no_r - 1; i++) ans += sum_bracket[i];
			}
			printf("%lld\n",ans);
		}
		
		/*printf("===========\n");
		for(int i = 1; i <= n; i++) printf("%d ",real_bracket[i]); puts("");
		for(int i = 1; i <= n; i++) printf("%lld ",sum_per[i]); puts("");
		for(int i = 1; i <= cnt; i++) printf("%lld ",sum_bracket[i]); puts("");
		printf("===========\n");*/
	}
}
