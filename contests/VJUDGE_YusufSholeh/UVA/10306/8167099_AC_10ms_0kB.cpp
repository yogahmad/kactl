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
#define MAX 100005
#define INF 10000000

int tc;
int m, s;

int dp[45][305][305];
int X[45], Y[45];

int f(int i, int x, int y) {
	if (i > m) return INF;
	if (x*x + y*y > s*s) return INF;
	if (x*x + y*y == s*s) return 0;
	
	int &ret = dp[i][x][y];
	if (ret >= 0) return ret;
	ret = 0;
	
	int skip = f(i+1,x,y);
	int ambil = f(i,x+X[i],y+Y[i]) + 1;
	return ret = min(skip, ambil);
}

int main(){
	scanf("%d",&tc);
	while(tc--) {
		scanf("%d %d",&m, &s);
		
		memset(dp,-1,sizeof(dp));
		
		for(int i = 1; i <= m; i++) {
			scanf("%d %d",&X[i], &Y[i]);
		}
		
		int ans = f(1,0,0);
		
		if (ans == INF) printf("not possible\n");
		else printf("%d\n",ans);
	}
}
