#include<bits/stdc++.h>
#define MOD 1000000007
using namespace std;

const int MAX = 100005;
const int INF = 1e9;

struct Element_suffix{
	int rank_now, rank_pref, pos;
}; 

string s;
int sorted[17][MAX], freq[MAX], start[MAX], SA[MAX], end;
Element_suffix suf[MAX], tmp[MAX];
vector<Element_suffix> v[MAX];


struct Suffix{
	bool same_rank(Element_suffix a, Element_suffix b) {
		return a.rank_now == b.rank_now && a.rank_pref == b.rank_pref;
	}
	void build_suffix() {
		int n = s.length();
		end = max(n, 10000);
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
	}
};

int n;


int H[MAX];
int bit[MAX];

void update(int pos, int val) {
	for(int i = pos; i <= n; i += (i & (-i))) {
		bit[i] += val;
		bit[i] %= MOD;
	}
}

int query(int pos) {
	int ret = 0;
	for(int i = pos; i > 0; i -= (i & (-i))) {
		ret += bit[i];
		ret %= MOD;
	}
	return ret;
}


Suffix A;

int main() {
	
	int cnt = 0;
	
	while(cin >> s) {
		
		
		cnt += (int)s.length();
		if (cnt > 1000) assert(0);
		
		A.build_suffix();
		int len = s.length();
		
		n = len;
		for(int i = 0; i <= len; i++) {
			H[i] = len - SA[i];
			bit[i] = 0;
		}
		
		int ans = 0;
		for(int i = 0; i < len; i++) {
			int tmp = query(H[i]-1);
			ans += tmp + 1;
			ans %= MOD;
			assert(H[i] != 0);
			update(H[i], tmp + 1);
		}
		
		
		printf("%d\n",ans);
	}
}	