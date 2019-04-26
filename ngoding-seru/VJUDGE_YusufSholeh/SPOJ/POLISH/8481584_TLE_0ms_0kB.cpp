#include<bits/stdc++.h>
#define LL long long
#define MOD 1000000007
using namespace std;

const int MAX = 1e5 + 5;
const int INF = 1e9;

class Element_suffix{
public:
	int rank_now, rank_pref, pos;
};

class Suffix{
private:
	bool same_rank(Element_suffix a, Element_suffix b) {
		return a.rank_now == b.rank_now && a.rank_pref == b.rank_pref;
	}
	void reset_freq(bool is_sort_now) {
		for(int i = 0; i <= end; i++) freq[i] = 0;
		for(int i = 0; i < n; i++) freq[ is_sort_now ? suf[i].rank_now+1 : suf[i].rank_pref+1 ]++;
		start[0] = 0;
		for(int i = 1; i <= end; i++) {
			start[i] = freq[i-1];
			freq[i] += freq[i-1];
		}
	}
public:
	int sorted[20][MAX], freq[MAX], start[MAX], SA[MAX], end, n;
	Element_suffix suf[MAX], tmp[MAX];
	void build_suffix(string s) {
		n = s.length();
		end = max(n, 1 << 8);
		for(int i = 0; i < n; i++) sorted[0][i] = (int)s[i];
		int step = 1;
		for(int cnt = 1; cnt < n; step++, cnt *= 2) {
			for(int i = 0; i < n; i++) {
				suf[i].rank_pref = sorted[step-1][i];
				suf[i].rank_now = (i + cnt < n) ? sorted[step-1][i+cnt] : -1;
				suf[i].pos = i;
			}
			reset_freq(1);
			for(int i = 0; i < n; i++) tmp[start[suf[i].rank_now+1]++] = suf[i];
			reset_freq(0);
			for(int i = 0; i < n; i++) suf[start[tmp[i].rank_pref+1]++] = tmp[i];
			for(int i = 0; i < n; i++) {
				sorted[step][suf[i].pos] = (i && same_rank(suf[i], suf[i-1])) ? sorted[step][suf[i-1].pos] : i;
			}
		} step--;
		for(int i = 0; i < n; i++) SA[sorted[step][i]] = i;
	}
};

int n;

Suffix A;

LL H[MAX];
LL bit[MAX];

void update(int pos, LL val) {
	for(int i = pos; i < n; i += (i & (-i))) {
		bit[i] += val;
		if (bit[i] >= MOD) bit[i] -= MOD;
	}
}

LL query(int pos) {
	LL ret = 0;
	for(int i = pos; i > 0; i -= (i & (-i))) {
		ret += bit[i];
		if (ret >= MOD) ret -= MOD;
	}
	return ret;
}

char INP[MAX];

int main() {
	
	while(scanf("%s",INP)!=EOF) {
		// cout << s << endl;
		int len = strlen(INP);
		string s = "";
		for(int i = 0; i < len; i++) s += INP[i];
		A.build_suffix(s);
		
		n = len;
		for(int i = 0; i <= len; i++) {
			H[i] = len - A.SA[i];
			bit[i] = 0;
		}
		
		LL ans = 0;
		for(int i = 0; i < len; i++) {
			LL tmp = query(H[i]-1);
			ans += tmp + 1;
			while(ans >= MOD) ans -= MOD;
			update(H[i], tmp + 1);
		}
		
		printf("%lld\n",ans);
	}
}	