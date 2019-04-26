#include<bits/stdc++.h>
using namespace std;

const int MAX = 200005;

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
		for(int i = 0; i < n; i++) freq[is_sort_now ? suf[i].rank_now + 1 : suf[i].rank_pref + 1]++;
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
		if (n == 0) SA[0] = 0;
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

Suffix A, B, C;

string a, b;

int main() {
	cin >> a;
	A.build_suffix(a);
	
	long long ans1 = 0;
	int n = a.length();
	for(int i = 0; i < n; i++) {
		ans1 += n - A.SA[i];
		if (i != n-1) {
			ans1 -= A.compute_lcp(A.SA[i], A.SA[i+1]);
		}
	}
	
	long long ans2 = 0;
	cin >> b;
	B.build_suffix(b);
	int m = b.length();
	for(int i = 0; i < m; i++) {
		ans2 += m - B.SA[i];
		if (i != m-1) {
			ans2 -= B.compute_lcp(B.SA[i], B.SA[i+1]);
		}
	}
	
	a += '{';
	a += b;
	C.build_suffix(a);
	int o = a.length();
	long long ans3 = 0;
	for(int i = 0; i < o; i++) {
		ans3 += o - C.SA[i];
		if (i != o-1) {
			ans3 -= C.compute_lcp(C.SA[i], C.SA[i+1]);
		}
	}
	
	//cout << ans3 << endl;
	ans3 -= ((n+1) * (m+1));
	
	//cout << o << endl;
	//cout << ans1 << " " << ans2 << " " << ans3 << endl;
	printf("%lld\n",ans3*2 - ans1 - ans2);
	
	return 0;
}
