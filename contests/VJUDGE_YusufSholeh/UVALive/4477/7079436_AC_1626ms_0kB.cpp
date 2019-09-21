#include<bits/stdc++.h>
#define MAX 100005
using namespace std;

int lg[MAX];
inline void precomp() {
	for(int i = 0; i < MAX; i++) {
		int T = 0;
		for(T = 1; (1 << T) <= i; T++);
		lg[i] = T;
	}
}

int n;
int sorted[20][MAX];
int LCP[MAX];
char s[MAX];

struct suffix{
	int rank_pref, rank_now, pos;
};
int freq[MAX];
int start[MAX];
int SA[MAX];
suffix tmp[MAX], suf[MAX];



inline bool samerank(suffix a, suffix b) {
	return a.rank_pref == b.rank_pref && a.rank_now == b.rank_now;
}

inline int compute_lcp(int x, int y) {
	int ans = 0;
	for(int k = lg[n]; k >= 0; k--) {
		int shift = (1 << k);
		if (x + shift - 1 < n && y + shift - 1 < n && sorted[k][x] == sorted[k][y]) {
			x += shift;
			y += shift;
			ans += shift;
		}
	}
	return ans;
}

int main() {
	
	precomp();
	while(scanf("%s", &s) != EOF) {
		if (s[0] == '*') break;
		
		n = strlen(s);
		
		int end = (n <= 256) ? 256 : n;
		for(int i = 0; i < n; i++)
			sorted[0][i] = int(s[i]);
		
		int last;
		for(int step = 1, cnt = 1; cnt < n; step++, cnt *= 2) {
			int id = step;
			last = id;
			for(int i = 0; i < n; i++) {
				suf[i].rank_pref = sorted[id-1][i];
				suf[i].rank_now  = (i + cnt < n) ? sorted[id-1][i + cnt] : -1;
				suf[i].pos = i;
				freq[i] = 0;
			} freq[n] = 0;
			
			if (end == 256) 
				for(int i = 0; i <= 256; i++) freq[i] = 0;
			
			for(int i = 0; i < n; i++) 
				freq[suf[i].rank_now+1]++;
			
			start[0] = 0;

			for(int i = 1; i <= end; i++) {
				start[i] = freq[i-1];
				freq[i] += freq[i-1];
			}
			
			for(int i = 0; i < n; i++) 
				tmp[start[suf[i].rank_now+1]++] = suf[i],
				freq[i] = 0;
			freq[n] = 0;
			
			if (end == 256) 
				for(int i = 0; i <= 256; i++) freq[i] = 0;
			
			for(int i = 0; i < n; i++) 
				freq[suf[i].rank_pref+1]++;
			
			start[0] = 0;
			for(int i = 1; i <= end; i++) {
				start[i] = freq[i-1];
				freq[i] += freq[i-1];
			}
			
			for(int i = 0; i < n; i++)
				suf[start[tmp[i].rank_pref+1]++] = tmp[i];
			
			for(int i = 0; i < n; i++)
				sorted[id][suf[i].pos] = (i && samerank(suf[i-1], suf[i])) ? sorted[id][suf[i-1].pos] : i;
		}
		
		for(int i = 0; i < n; i++) 
			SA[sorted[last][i]] = i;
		
		
		long long res = 0;
		int pref = 0;
		
		for(int i = 0; i < n-1; i++) {			
			int cur = compute_lcp(SA[i], SA[i+1]);
			res += (cur >= pref) ? cur-pref : 0;
			pref = cur;
		}
		
		printf("%lld\n",res);
	}
}
