#include<bits/stdc++.h>
#define MAX 100005
using namespace std;

int n;
int sorted[19][MAX];
char s[MAX];

struct suffix{
	int rank_pref, rank_now, pos;
} suf[MAX];

bool cmp(suffix a, suffix b) {
	if (a.rank_pref == b.rank_pref) return a.rank_now < b.rank_now;
	return a.rank_pref < b.rank_pref;
}

inline int compute_lcp(int x, int y) {
	int ans = 0;
	for(int k = 18; k >= 0; k--) {
		if (x + (1 << k) - 1 < n && y + (1 << k) - 1 < n && sorted[k][x] == sorted[k][y]) {
			x += (1 << k);
			y += (1 << k);
			ans += (1 << k);
		}
	}
	return ans;
}

int main() {
	while(scanf("%s", &s)) {
		if (s[0] == '*') break;
		
		n = strlen(s);
		for(int i = 0; i < n; i++)
			sorted[0][i] = int(s[i]);
		
		for(int step = 1, cnt = 1; cnt < n; step++, cnt *= 2) {
			for(int i = 0; i < n; i++) {
				suf[i].rank_pref = sorted[step-1][i];
				suf[i].rank_now  = (i + cnt < n) ? sorted[step-1][i + cnt] : -1;
				suf[i].pos = i;
			}
			
			sort(suf, suf + n, cmp);
			
			for(int i = 0; i < n; i++) {
				sorted[step][suf[i].pos] = (i && suf[i].rank_pref == suf[i-1].rank_pref && suf[i].rank_now == suf[i-1].rank_now) ? sorted[step][suf[i-1].pos] : i;
			}
		}
		
		long long res = 0;
		long long pref = 0;
		for(int i = 0; i < n-1; i++) {
			int x = suf[i].pos;
			int y = suf[i + 1].pos;
			long long cur = compute_lcp(x, y);
			res += max(0LL, cur - pref);
			pref = cur;
		}
		
		printf("%lld\n", res);
	}
}