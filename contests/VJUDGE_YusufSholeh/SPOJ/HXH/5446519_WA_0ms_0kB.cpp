#include<bits/stdc++.h>
#define MAX 505
using namespace std;
int tc, n;
char p[MAX][MAX];
int dp[MAX][MAX];
int dp2[MAX][MAX];

int main() {
	scanf("%d",&tc);
	while(tc--) {
		scanf("%d",&n); getchar();
		for(int i = 0; i < n; i++) {
			scanf("%s",&p[i]);
			for(int j = 0; j < n; j++) {
				dp[i][j] = -(1<<20); 
				dp2[i][j] = -(1<<20);
				if (p[i][j] == '#') continue; dp[0][0] = 0;
				if (i) dp[i][j] = (dp[i - 1][j] > dp[i][j]) ? dp[i - 1][j] : dp[i][j];
				if (j) dp[i][j] = (dp[i][j - 1] > dp[i][j]) ? dp[i][j - 1] : dp[i][j];
				if (p[i][j] == '*') dp[i][j] += 1;
			}
		}
		for(int i = n - 1; i >= 0; i--) {
			for(int j = n - 1; j >= 0; j--) {
				if (p[i][j] == '#') continue; dp2[n - 1][n - 1] = 0;
				if (i < n - 1) dp2[i][j] = (dp2[i + 1][j] > dp2[i][j]) ? dp2[i + 1][j] : dp2[i][j];
				if (j < n - 1) dp2[i][j] = (dp2[i][j + 1] > dp2[i][j]) ? dp2[i][j + 1] : dp2[i][j];
				if (p[i][j] == '*') dp2[i][j] += 1;
			}
		}
		int ans = -(1<<20);
		for(int i = n - 1, j = 0; i >= 0; i--,j++) {
			int res = dp[i][j] + dp2[i][j] - (p[i][j] == '*');
			// printf("%d %d %d %d\n",i,j,dp[i][j],dp2[i][j]);
			if (res > ans) ans = res;
		}
		printf("%d\n",ans);
	}
}