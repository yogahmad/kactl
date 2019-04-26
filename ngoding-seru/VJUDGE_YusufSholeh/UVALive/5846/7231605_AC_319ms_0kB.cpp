#include<bits/stdc++.h>
#define LL long long
using namespace std;
int hub[1005][1005];
int pref[1005][1005];
LL cnt[1005];
int main() {
	int tc;
	scanf("%d",&tc);
	while(tc--) {
		LL n, ans;
		scanf("%lld",&n);
		ans = 0;
		for(int i = 1; i <= n; i++) cnt[i] = 0;
		for(int i = 1; i < n; i++) 
			for(int j = i + 1; j <= n; j++)
				scanf("%d",&hub[i][j]), hub[j][i] = hub[i][j];
		for(int i = 1; i <= n; i++) 
			for(int j = 1; j <= n; j++) 
				pref[i][j] = pref[i][j-1] + hub[i][j];
		for(int i = n; i >= 1; i--) {
			int j = i;
			do {
				j--; 
				if (j == 0) j = n;
				if (j == i) break;
				if (!hub[i][j] && i > j) ans += pref[j][j] + pref[j][n] - pref[j][i];
				//printf("%d %d\n: %d %d %d\n",i, j, pref[j][j], pref[j][n], pref[j][i]);
				if (!hub[i][j] && i < j) ans += pref[j][j] - pref[j][i];
				//printf("%d %d\n: %d %d\n",i, j, pref[j][j],  pref[j][i]);
				//else ans += (n - abs(i - j) - pref[j][j] + pref[j][n] - pref[j][i]);
			} while(j != i);
		}
		
		//printf("%d\n",ans);
		printf("%lld\n",n*(n-1)*(n-2)/6	- ans);
	}
}			