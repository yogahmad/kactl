#include<bits/stdc++.h>
#define MAX 1005
#define LL long long
#define MOD 1000000007LL
using namespace std;
char cmd[1005];

LL dp[MAX][MAX];
LL prefup[MAX][MAX];
LL prefdn[MAX][MAX];
int n;

int main() {
	while(scanf("%s",&cmd) != EOF){
		n = strlen(cmd);
		
		for(int i = 0; i <= n + 1; i++)
			for(int j = 0; j <= n + 1; j++)
				dp[i][j] = prefdn[i][j] = 0;
		
		dp[n+1][0] = 1;
		prefdn[n+1][0] = 1;
		for(int i = n; i >= 1; i--) {
			int sisa = n - i + 1;
			for(int down = 0; down <= sisa; down++) {
				int up = sisa - down;
				
				if (i == 0 || cmd[i-1] == 'I' || cmd[i-1] == '?')
					dp[i][down] += prefdn[i+1][sisa-1] - ((down == 0) ? 0 : prefdn[i+1][down-1]);
				if (i == 0 || cmd[i-1] == 'D' || cmd[i-1] == '?')
					dp[i][down] += ((down == 0) ? 0 : prefdn[i+1][down-1]);
				
				dp[i][down] %= MOD;
				while(dp[i][down] < 0) dp[i][down] += MOD;
			}
			
			for(int down = 0; down <= sisa; down++) {
				prefdn[i][down] = prefdn[i][max(0,down-1)] + dp[i][down];
				prefdn[i][down] %= MOD;
			}
		}
		
		LL ans = 0;
		for(int i = 0; i <= n; i++) 
			ans = (ans + dp[1][i])%MOD;
		
		printf("%lld\n",ans);
	}
}