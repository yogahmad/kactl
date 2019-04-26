#include<bits/stdc++.h>
#define LL long long
using namespace std;

int n;
const int MAX = 600005;
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
	int sorted[21][MAX], freq[MAX], start[MAX], SA[MAX], end, n, ceentete;
	Element_suffix suf[MAX], tmp[MAX];
	void build_suffix(string s) {
		memset(sorted,0,sizeof(sorted));
		memset(SA,0,sizeof(SA));
		n = s.length();
		end = max(n, 600001);
		ceentete = 1;
		for(int i = 0; i < n; i++) {
			sorted[0][i] = (int)s[i];
			if (s[i] == '{') {sorted[0][i] += ceentete++;}
		}
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
		if (n == 1) SA[0] = 0;
	}
	int compute_lcp(int x, int y) {
		int ans = 0;
		for(int k = 19; k >= 0; k--) {
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
string gabung;
int total_length(0);
LL cost[MAX];
int idx[MAX];
LL LCP[MAX];
int L[MAX], R[MAX], bit[MAX];

void update(int pos, int val) {
	if (pos == 0) {
		bit[pos] = min(bit[pos], val);
		pos++;
	}
	for(int i = pos; i < MAX; i += (i & (-i))) {
		bit[i] = min(bit[i], val);
	}
}

int query(int pos) {
	if (pos < 0) return pos;
	int ret = bit[0];
	for(int i = pos; i > 0; i -= (i & (-i))) {
		ret = min(ret, bit[i]);
	}
	return ret-1;
}

void update2(int pos, int val) {
	if (pos == 0) {
		bit[pos] = max(bit[pos],val);
		pos++;
	}
	for(int i = pos; i < MAX; i += (i & (-i))) {
		bit[i] = max(bit[i], val);
	}
}

int query2(int pos) {
	if (pos < 0) return pos;
	int ret = bit[0];
	for(int i = pos; i > 0; i -= (i & (-i))) {
		ret = max(ret, bit[i]);
	}
	return ret+1;
}

LL ans[MAX];
LL res;
int id[MAX];

LL sum = 0;

LL pjg[MAX];
LL psum[MAX];
int done[MAX];
bool awal[MAX];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n;
	gabung = "";
	
	for(int i = 0; i < n; i++) {
		string s;
		cin >> s;
		gabung += s;
		int sz = gabung.size();
		int len = s.size();
		awal[sz-len] = true;
		total_length += len;
		for(int j = sz-1; j >= sz-len; j--) idx[j] = i;
		pjg[i] = len;
		gabung += '{';
	}
	
	A.build_suffix(gabung);
	
	for(int i = 0; i < total_length; i++) {
		LCP[i] = A.compute_lcp(A.SA[i], A.SA[i+1]);
		id[i] = idx[A.SA[i]];
	}
	
	for(int i = 0; i < n; i++) cin >> cost[i];
	
	for(int i = 0; i < MAX; i++) bit[i] = INF;
	update(0, total_length);
	for(int i = total_length-1; i >= 0; i--) {
		R[i] = query(LCP[i]-1);
		update(LCP[i],i);
	}
	for(int i = 0; i < MAX; i++) bit[i] = -INF;
	update2(0,-1);
	for(int i = 0; i < total_length; i++) {
		L[i] = query2(LCP[i]-1);
		update2(LCP[i],i);
	}
	
	res = 0;
	
	if (n == 1) res = max(res, cost[0] * pjg[0]);
	
	for(int i = 0; i < total_length; i++) {
		LL now = id[i];
		psum[i] = cost[now];
		if (i) psum[i] += psum[i-1];
	} psum[total_length] = psum[total_length-1];
	for(int i = 0; i < total_length; i++) {
		LL now = id[i];
		done[i] = max(done[i], (int)LCP[i]);
		done[i+1] = max(done[i+1], (int)LCP[i]);
		if (awal[A.SA[i]] && (done[i] != pjg[now] && i < total_length-1)) {
			res = max(res, cost[now] * pjg[now]);
		}
		if (i < total_length-1 && (L[i] == -1 || R[i] == -1)) {
			res = max(res, cost[now] * pjg[now]);
			continue;
		}
		if (L[i] > 0)
			res = max(res, LCP[i] * (psum[R[i]+1] - psum[L[i]-1]));
		else 
			res = max(res, LCP[i] * (psum[R[i]+1]));
	}
	
	printf("%lld\n",res);
}