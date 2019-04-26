#include<bits/stdc++.h>
#define MAX 100005
using namespace std;

struct elementSuffix {
	int rankNow, rankPref, pos;
};

class Suffix {
private:
	bool sameRank(elementSuffix a, elementSuffix b) {
		return a.rankNow == b.rankNow && a.rankPref == b.rankPref;
	}
	void resetFreq(bool isSortNow) {
		for(int i = 0; i <= end; i++) freq[i] = 0;
		for(int i = 0; i < n; i++) freq[isSortNow ? (suf[i].rankNow+1) : (suf[i].rankPref+1)]++;
		start[0] = 0; 
		for(int i = 1; i <= end; i++) {
			start[i] = freq[i-1];
			freq[i] += freq[i-1];
		}
	}
public:
	elementSuffix suf[MAX], tmp[MAX];
	int freq[MAX], start[MAX], sorted[20][MAX], SA[MAX];
	int end, n;
	void buildSuffix(string s) {
		n = s.length();
		end = max(n, 1 << 8);
		int step = 1;
		for(int i = 0; i < n; i++) sorted[0][i] = (int)s[i];
		for(int cnt = 1; cnt < n; step++, cnt *= 2) {
			for(int i = 0; i < n; i++) {
				suf[i].rankPref = sorted[step-1][i];
				suf[i].rankNow = (i + cnt < n) ? sorted[step-1][i+cnt] : -1;
				suf[i].pos = i;
			}
			resetFreq(1);
			for(int i = 0; i < n; i++) tmp[start[suf[i].rankNow+1]++] = suf[i];
			resetFreq(0);
			for(int i = 0; i < n; i++) suf[start[tmp[i].rankPref+1]++] = tmp[i];
			for(int i = 0; i < n; i++) sorted[step][suf[i].pos] = (i && sameRank(suf[i], suf[i-1])) ? sorted[step][suf[i-1].pos] : i;
		} step--;
		for(int i = 0; i < n; i++) SA[sorted[step][i]] = i;
	}
	int computeLCP(int x, int y) {
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
int H[MAX];

#define LL long long
typedef pair<LL, LL> pLL;
#define height first
#define CNT second
#define mp make_pair
pLL st[MAX];
int top = 0;
int main() {
	string s;
	cin >> s;
	A.buildSuffix(s);
	
	int len = s.length();
	LL ans = len;
	for(int i = 0; i < len-1; i++) {
		H[i] = A.computeLCP(A.SA[i], A.SA[i+1]);
		// printf("%d %d\n",i, H[i]);
	}
	
	H[len] = 0;
	
	for(int i = 0; i < len; i++) {
		LL cnt = 0;
		while(top > 0 && st[top].height >= H[i]) {
			ans = max(ans, (st[top].CNT + cnt + 1) * st[top].height);
			cnt += st[top].CNT;
			top--;
		}			
		st[++top] = mp(H[i], cnt+1);
	}
	
	printf("%lld\n",ans);
}