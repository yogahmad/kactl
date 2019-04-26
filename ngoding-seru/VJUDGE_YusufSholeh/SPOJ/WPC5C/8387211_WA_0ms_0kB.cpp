#include<bits/stdc++.h>
#define MAX 100005
#define LL long long
using namespace std;

const int INF = 1e9;

struct elementSuffix{
	int rankNow, rankPref, pos;
};

class Suffix{
private:
	void resetFreq(bool isSortNow) {
		for(int i = 0; i <= end; i++) freq[i] = 0;
		for(int i = 0; i < n; i++) freq[isSortNow ? (suf[i].rankNow+1) : (suf[i].rankPref+1)]++;
		start[0] = 0;
		for(int i = 1; i <= end; i++) {
			start[i] = freq[i-1];
			freq[i] += freq[i-1];
		}
	}
	bool sameRank(elementSuffix a, elementSuffix b) {
		return a.rankPref == b.rankPref && a.rankNow == b.rankNow;
	}
	
public:
	elementSuffix tmp[MAX], suf[MAX];
	int freq[MAX], start[MAX], sorted[20][MAX], SA[MAX], n, end;
	void buildSuffix(string s) {
		n = s.length();
		end = max(n, 1 << 8);	
		int step = 1;
		for(int i = 0; i < n; i++) sorted[0][i] = (int)s[i] - 'a';
		for(int cnt = 1; cnt < n; step++, cnt *= 2) {
			for(int i = 0; i < n; i++) {
				suf[i].rankNow = (i + cnt < n) ? sorted[step-1][i+cnt] : -1;
				suf[i].rankPref = sorted[step-1][i]; 
				suf[i].pos = i;
			}
			resetFreq(1);
			for(int i = 0; i < n; i++) tmp[start[suf[i].rankNow+1]++] = suf[i];
			resetFreq(0);
			for(int i = 0; i < n; i++) suf[start[tmp[i].rankPref+1]++] = tmp[i];		
			for(int i = 0; i < n; i++) sorted[step][suf[i].pos] = (i && sameRank(suf[i-1], suf[i])) ? sorted[step][suf[i-1].pos] : i;
		} step--;
		for(int i = 0; i < n; i++) SA[sorted[step][i]] = i; 
	}
	
	int computeLCP(int x, int y) {
		int ans = 0;
		for(int k = 20; k >= 0; k--) {
			int shift = (1 << k);
			if (x + shift - 1 < n && y + shift - 1 < n && sorted[k][x] == sorted[k][y]) {
				ans += shift;
				x += shift;
				y += shift;
			}
		}
		return ans;
	}
};

int n, end;
int ind[MAX];
LL F[MAX];
string input;
Suffix A;

int tree[4*MAX];
bool done[4*MAX];

void update(int now, int l, int r, int a, int b, int val) {
	if (done[now]) return;
	if (r < a || b < l) return;
	if (a <= l && r <= b) {
		if (val == -1) done[now] = true;
		else tree[now] = min(tree[now], val);
		return;
	}
	int mid = (l + r) >> 1;
	update(now * 2, l, mid, a, b, val);
	update(now * 2 + 1, mid + 1, r, a, b, val);
}

void dfs(int now, int l, int r, int minVal) {
	if (done[now]) minVal = tree[now];
	if (l == r) {
		F[l] = minVal;
		return;
	}
	minVal = min(minVal, tree[now]);
	int mid = (l + r) >> 1;
	dfs(now * 2, l, mid, minVal);
	dfs(now * 2 + 1, mid + 1, r, minVal);
}

int main() {
	scanf("%d",&n);
	cin >> input;
	A.buildSuffix(input);

	memset(F,-1,sizeof(F));
	for(int i = 0; i <= 4*n; i++) tree[i] = INF;
	
	for(int i = 0; i < n; i++) {
		int realIndex = A.SA[i];
		int length = n - realIndex;
		update(1, 1, n, 1, length, realIndex);
		int lcpNext = (i < n) ? A.computeLCP(A.SA[i], A.SA[i+1]) : 0;
		update(1, 1, n, lcpNext+1, length, -1);
	}
	
	dfs(1, 1, n, INF);
	
	sort(F + 1, F + n + 1);
	LL ans = 0;
	LL pref = 0;
	for(LL i = 1; i <= n; i++) {
		ans = ans - pref + i*F[i];
		pref += F[i];
		// printf("%lld %lld\n",i, F[i]);
	}
	
	printf("%lld\n",ans);
}	