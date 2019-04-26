#include<bits/stdc++.h>
using namespace std;

#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front

inline int ask_interactive(int x) {
	printf("? %d\n",x);
	fflush(stdout);
	int has;
	scanf("%d",&has);
	return has;
}

#define pq priority_queue
#define rep(k,i,j) for(int k = (int)i;k<(int)j;k++)
#define repd(k,i,j) for(int k = (int)i;k>=(int)j;k--)
#define LL long long

double EPS = 1e-9;
int INF = 1e9+7;;
long long INFLL = 1e17;
double pi = acos(-1);

LL a, b;

bool flag[105];

int main(){
	int n, m;
	scanf("%d %d",&n, &m);
	memset(flag,0,sizeof(flag));
	for(int i = 1; i <= n; i++) {
		int x;
		scanf("%d",&x);
		for(int j = 1; j <= x; j++) {
			int y;
			scanf("%d",&y);
			flag[y] = true;
		}
	}
	
	// int zz = 0;
	for(int i = 1; i <= m; i++) {
		if (flag[i] == false) {
			printf("NO\n");
			return 0;
		}
	}
	printf("YES\n");
}