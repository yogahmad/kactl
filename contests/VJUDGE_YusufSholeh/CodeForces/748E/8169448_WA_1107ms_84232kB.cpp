#include<bits/stdc++.h>
using namespace std;


#define pii pair<int,int>
#define f first
#define s second
#define mp make_pair
#define pb push_back

inline int ask_interactive(int x) {
	printf("? %d\n",x);
	fflush(stdout);
	int ret;
	scanf("%d",&ret);
	return ret;
}

#define LL long long
#define MAXN 1000005
#define MAXM 10000005
#define INF 10000000

int n, k;
LL dp[MAXM+2];
int arr[MAXN];

int main(){
	scanf("%d %d",&n, &k);
	
	LL tot = 0;
	for(int i = 1; i <= n; i++) {
		scanf("%d",&arr[i]);
		tot += arr[i];
	}
	if (tot < k) return printf("-1\n"),0;
	
	int l = 1, r = MAXM;
	
	int ans = 0;
	while(l <= r) {
		int mid = (l + r) >> 1;
		memset(dp,0,sizeof(dp)); 
		int last = 0;
		for(int i = mid; i < MAXM; i++) {
			if (i/2 >= mid && (i+1)/2 >= mid) {
				last = i;
				break;
			}
			dp[i] = 1;
		}
		for(int i = last; i < MAXM; i++) dp[i] = dp[i/2] + dp[(i+1)/2];
		LL sum = 0;
		for(int i = 1; i <= n; i++) sum += dp[arr[i]];
		// printf("%lld\n",sum);
		if (sum >= (LL)k) {
			ans = mid;
			l = mid + 1;
		} else r = mid - 1;
	}
	printf("%d\n",ans);
}
