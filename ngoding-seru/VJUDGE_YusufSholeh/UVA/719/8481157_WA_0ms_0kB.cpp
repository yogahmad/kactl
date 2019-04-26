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
		// for(int i = 0; i < n; i++) printf("%d %d\n", i, SA[i]);
	}
	
	int computeLCP(int x, int y) {
		int ans = 0;
		for(int k = 19; k >= 0; k--) {
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

Suffix A;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		string s;
		cin >> s;
		int len = s.length();
		s += s;
		A.buildSuffix(s);
		
		for(int i = 0; i < len+len; i++) {
			int pjg = len*2 - A.SA[i];
			// cout << pjg << " " << A.SA[i] << endl;
			if (pjg >= len) {
				cout << A.SA[i]+1 << endl;
				break;
			}
		}
	}
}	