#include<bits/stdc++.h>
#define LL long long
#define MOD 1000000007
#define MAX 5005
using namespace std;

LL pang(LL x, LL y) {
	if (y == 1) return x;
	LL res = pang(x, y/2);
	res = (res * res)%MOD;
	if (y & 1) return (res * x)%MOD;
	return res;
}

LL dp[MAX][MAX];
int n, len;
char K[MAX];
LL f(int i, int x) {
	if (x == 0) {
		if (i == len) return 1;
		return 0;
	}
	LL &ret = dp[i][x];
	if (ret >= 0) return ret;
	ret = f(max(i-1,0),x-1);
	ret += 2LL*f(i+1,x-1);
	ret %= MOD;
	return ret;
}

int main() {
	scanf("%d",&n);
	scanf("%s",K);
	len = strlen(K);
	memset(dp,-1,sizeof(dp));
	//cout << f(0, n) << " " << len << endl;
	printf("%lld\n",(f(0,n)*pang(pang(2,len),MOD-2))%MOD);
}