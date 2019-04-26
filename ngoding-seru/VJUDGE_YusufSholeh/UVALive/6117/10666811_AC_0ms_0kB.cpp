#include <bits/stdc++.h>
using namespace std;

#define LL long long

typedef pair<int,int> pii;
#define f first
#define s second
#define mp make_pair

const int MAXN = 35;

LL t, n, l, r;
LL fact[MAXN];
LL C[MAXN][MAXN];
LL dp[MAXN][MAXN];

void generatecombin() {
	fact[0] = 1;
	for(LL i = 1; i <= 20; i++) fact[i] = i * fact[i-1];
	for(int i = 0; i < MAXN; i++) {
		C[i][0] = 1;
		for(int j = 1; j <= i; j++) C[i][j] = C[i-1][j] + C[i-1][j-1];
	}
}


LL f(LL x, LL rem) {
	if (rem < 0) return 0;
	if (x == 0) return (rem == 0) ? 1 : 0;

	LL &ret = dp[x][rem];
	if (ret >= 0) return ret;

	ret = 0;
	for(int i = 0; i < x; i++) {
		ret += f(i, rem - 1) * C[x-1][i] * fact[x-i-1];
	}
	return ret;
}

int main() {
	generatecombin();
	memset(dp, -1, sizeof dp);

	scanf("%lld",&t);
	while(t--) {
		scanf("%lld %lld %lld",&n, &l, &r);
		
		LL ans = 0;
		for(int piv = 1; piv <= n; piv++) {
			LL ki = f(piv - 1, l - 1);
			LL ka = f(n - piv, r - 1);
			ans += ki * ka * C[n-1][piv-1];
		}

		printf("%lld\n",ans);
	}
}