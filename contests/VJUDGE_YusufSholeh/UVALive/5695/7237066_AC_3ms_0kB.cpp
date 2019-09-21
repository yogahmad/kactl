#include<bits/stdc++.h>
#define LL long long
#define max 205
#define INF 1000000000
using namespace std;

int dp[max][max][2][2];
int d[max], t[max];

int f(int l, int r, int ki, int ka) {
	if (l == r) return dp[l][r][ki][ka] = 0;
	
	if (dp[l][r][ki][ka] != -1) return dp[l][r][ki][ka];
	
	if (ki == 1 && ka == 0) {
		
		int pindahki = f(l+1, r, ki, ka);
		int pindahka = f(l+1, r, 1-ki, 1-ka);
		pindahki = (pindahki == -2) ? INF : pindahki + d[l+1] - d[l];
		pindahka = (pindahka == -2) ? INF : pindahka + d[r]  -  d[l];
		if (pindahki == INF && pindahka == INF) return -2;
		int minn = min(pindahki, pindahka);
		if (t[l] > minn) return dp[l][r][ki][ka] = minn;
		return dp[l][r][ki][ka] = -2;
		
	} else if (ki == 0 && ka == 1) {
		
		int pindahki = f(l, r-1, 1-ki,1-ka);
		int pindahka = f(l, r-1, ki, ka);
		pindahki = (pindahki == -2) ? INF : pindahki +   d[r] - d[l];
		pindahka = (pindahka == -2) ? INF : pindahka + d[r] - d[r-1];	
		if (pindahki == INF && pindahka == INF) return -2;
		int minn = min(pindahki, pindahka);
		if (t[r] > minn) return dp[l][r][ki][ka] = minn;
		return dp[l][r][ki][ka] = -2;
	} else {
		return dp[l][r][ki][ka] = -2;
	}
}

vector<int> ans;
void bt(int l, int r, int ki, int ka) {
	if (l == r) {
		ans.push_back(l);
		return;
	}
	
	if (ki) ans.push_back(l);
	if (ka) ans.push_back(r);
	
	if (ki == 1 && ka == 0) {
		
		int pindahki = f(l+1, r, ki, ka);
		int pindahka = f(l+1, r, 1-ki, 1-ka);
		pindahki = (pindahki == -2) ? INF : pindahki + d[l+1] - d[l];
		pindahka = (pindahka == -2) ? INF : pindahka + d[r]  -  d[l];
		
		int moveki = 0, moveka = 0;
		
		if (pindahki < pindahka) moveki = 1;
		else moveka = 1;
		
		if (moveki) bt(l+1,r,ki,ka);
		else bt(l+1,r,1-ki,1-ka);
		
	} else if (ki == 0 && ka == 1) {
		
		int pindahki = f(l, r-1, 1-ki,1-ka);
		int pindahka = f(l, r-1, ki, ka);
		pindahki = (pindahki == -2) ? INF : pindahki +   d[r] - d[l];
		pindahka = (pindahka == -2) ? INF : pindahka + d[r] - d[r-1];	
		
		int moveki = 0, moveka = 0;
		
		if (pindahki < pindahka) moveki = 1;
		else moveka = 1;
		
		if (moveki) bt(l,r-1,1-ki,1-ka);
		else bt(l,r-1,ki,ka);
		
	}
}

int main() {
	int n;
	while(scanf("%d",&n) != EOF) {
		for(int i = 1; i <= n; i++) scanf("%d",&t[i]);
		for(int i = 1; i <= n; i++) scanf("%d",&d[i]);
		
		memset(dp, -1, sizeof(dp));
		
		ans.clear();
		if (f(1, n, 1, 0) != -2) {
			bt(1, n, 1, 0);
			int size = ans.size();
			printf("%d",ans[0]);
			for(int i = 1; i < size; i++) printf(" %d",ans[i]);
			printf("\n");
			continue;
		}
		if (f(1, n, 0, 1) != -2) {
			bt(1, n, 0, 1);
			int size = ans.size();
			printf("%d",ans[0]);
			for(int i = 1; i < size; i++) printf(" %d",ans[i]);
			printf("\n");
			continue;
		}
		printf("Mission Impossible\n");
	}
}