#include<bits/stdc++.h>
#define LL long long
#define MOD 1000000007
#define MAX 1000005
using namespace std;
int n, x, maks;
int freq[MAX];
int dp[MAX][21];
int P[MAX];

inline int mod(int x) {
	if (x >= MOD) x -= MOD;
	return x;
}

inline int cfreq(int x) {
	if (x >= MAX) return 0;
	return freq[x];
}

inline int cdp(int x, int y) {
	if (x >= MAX) return 0;
	return dp[x][y];
}

int main() {
	scanf("%d",&n);
	for(int i = 1; i <= n; i++) {
		scanf("%d",&x);
		maks = max(maks, x);
		freq[x]++;
	}
	
	P[0] = 1;
	for(int i = 1; i <= 1000000; i++) P[i] = mod(2*P[i-1]);
	for(int i = maks; i >= 0; i--) {
		dp[i][0] = freq[i];
		if ((i & 1) == 0) dp[i][0] += cfreq(i|1);
		for(int j = 1; j <= 20; j++) {
			dp[i][j] = dp[i][j-1];
			
			if ((i & (1 << j)) == 0)
				dp[i][j] += cdp(i|(1<<j),j-1);
		}
	}
	
	P[0] = 1;
	int ans = 0;
	for(int i = 0; i <= maks; i++) {
		int cnt = __builtin_popcount(i);
		int val = P[dp[i][20]]-1;
		if (cnt % 2 == 0) ans = mod(ans + val);
		else ans = mod(ans - val);
		if (ans < 0) ans += MOD;
	}
	
	printf("%d\n",ans);
}
