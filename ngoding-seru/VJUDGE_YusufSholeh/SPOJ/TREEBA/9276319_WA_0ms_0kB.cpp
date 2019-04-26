#include<bits/stdc++.h>
using namespace std;

const int PJG_STRING = 10005;

#define LL long long

const LL base = 27;

int tc;
int M, K;
int N;
char str[PJG_STRING];
int dp[PJG_STRING][11][2];

map<LL, int> maps;

int f(int pos, int sisa, bool bol) {
	
	if (pos == N || sisa == 0) return 0;
	
	int &ret = dp[pos][sisa][bol];
	if (ret >= 0) return ret;
	ret = 0;
	
	// LAGI SKIP :
	if (bol) { // NGGA SKIP ATAU SKIP
		return ret = max(f(pos, sisa, false), f(pos + 1, sisa, true));
	}
	
	// SKIP :
	ret = f(pos + 1, sisa - 1, true);
	
	LL hash = 0;
	for(int i = pos; i < pos + 20; i++) {
		if (i == N) break;
		hash = hash * base + ((int)str[i] - 'a' + 1);
		if (maps.count(hash)) ret = max(ret, f(i + 1, sisa, false) + 1);
	}
	
	return ret;
}

int main() {
	scanf("%d",&tc);
	
	char tmp[25];
	while(tc--) {
		scanf("%d %d",&M, &K);
		scanf("%s",str);
		N = strlen(str);
		
		// printf("ASD %s\n",str);
		for(int i = 1; i <= M; i++) {
			scanf("%s",tmp);
			int len = strlen(tmp);
			LL x = 0;
			for(int j = 0; j < len; j++) {
				x = x * base + ((int)tmp[j] - 'a' + 1);
			}
			// printf("%lld\n",x);
			maps[x] += 1;
		}
		
		memset(dp,-1,sizeof(dp));
		printf("%d\n",f(0,K,0));
	}
}