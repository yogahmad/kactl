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
	int compute_lcp(int x, int y) {
		int ans = 0;
		for(int k = 20; k >= 0; k--) {
			int s = (1 << k);
			if (x + s - 1 < n && y + s - 1 < n && sorted[k][x] == sorted[k][y]) {
				ans += s;
				x += s;
				y += s;
			}
		}
		return ans;
	}
};
Suffix A;

LL H[MAX];
LL bit[MAX];

void update(int pos, LL val) {
	for(int i = pos; i < MAX; i += (i & (-i))) {
		bit[i] += val;
		if (bit[i] >= MOD) bit[i] -= MOD;
	}
}

LL query(int pos) {
	LL ret = 0;
	for(int i = pos; i > 0; i -= (i & (-i))) {
		ret += bit[i];
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	string s;
	while(cin >> s) {
		// cout << s << endl;
		A.build_suffix(s);
		int len = s.length();
		memset(bit,0,sizeof(bit));
		
		for(int i = 0; i < len; i++) {
			H[i] = len - A.SA[i];
			// cout << H[i] << endl;
		}
		
		LL ans = 0;
		for(int i = 0; i < len; i++) {
			LL tmp = query(H[i]-1);
			ans += tmp + 1;
			ans %= MOD;
			update(H[i], tmp + 1);
		}
		
		cout << ans << endl;
	}
}	