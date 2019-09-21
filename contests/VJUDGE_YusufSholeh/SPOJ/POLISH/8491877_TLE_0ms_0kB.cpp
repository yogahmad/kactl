#include<bits/stdc++.h>
#define MOD 1000000007
using namespace std;

const int MAX = 1e5 + 5;
const int INF = 1e9;

string s;

class Element_suffix{
public:
	int rank_now, rank_pref, pos;
};

class Suffix{
private:
	inline bool same_rank(Element_suffix a, Element_suffix b) {
		return a.rank_now == b.rank_now && a.rank_pref == b.rank_pref;
	}
	inline void reset_freq(bool is_sort_now) {
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
	vector<Element_suffix> v[MAX];
	void build_suffix() {
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
			for(int i = 0; i < n; i++) v[suf[i].rank_now+1].push_back(suf[i]);
			int top = 0;
			for(int i = 0; i <= end; i++) {
				int size = v[i].size();
				for(int j=0; j<size;j++) suf[top++] = v[i][j];
				v[i].clear();
			} top = 0;
			for(int i = 0; i < n; i++) v[suf[i].rank_pref+1].push_back(suf[i]);
			for(int i = 0; i <= end; i++) {
				int size = v[i].size();
				for(int j = 0; j < size; j++) suf[top++] = v[i][j];
				v[i].clear();
			}
			for(int i = 0; i < n; i++) {
				sorted[step][suf[i].pos] = (i && same_rank(suf[i], suf[i-1])) ? sorted[step][suf[i-1].pos] : i;
			}
		} step--;
		for(int i = 0; i < n; i++) SA[sorted[step][i]] = i;
		// for(int i = 0; i < n; i++) printf("%d %d\n",i,SA[i]);
	}
};

int n;

Suffix A;

int H[MAX];
int bit[MAX];

inline void update(int pos, int val) {
	for(int i = pos; i < n; i += (i & (-i))) {
		bit[i] += val;
		if (bit[i] >= MOD) bit[i] -= MOD;
	}
}

inline int query(int pos) {
	int ret = 0;
	for(int i = pos; i > 0; i -= (i & (-i))) {
		ret += bit[i];
		if (ret >= MOD) ret -= MOD;
	}
	return ret;
}

int main() {
	
	while(cin >> s) {
		// cout << s << endl;
		A.build_suffix();
		int len = s.length();
		
		n = len;
		for(int i = 0; i <= len; i++) {
			H[i] = len - A.SA[i];
			bit[i] = 0;
		}
		
		int ans = 0;
		for(int i = 0; i < len; i++) {
			int tmp = query(H[i]-1);
			ans += tmp + 1;
			while(ans >= MOD) ans -= MOD;
			assert(H[i] != 0);
			update(H[i], tmp + 1);
		}
		
		printf("%d\n",ans);
	}
}	