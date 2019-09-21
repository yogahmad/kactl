#include<bits/stdc++.h>
using namespace std;

#define pii pair<int,int>
#define f first
#define s second
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

#define LL long long
#define MAX 300005

double EPS = 1e-9;
int INF = 1e9+7;;
long long INFLL = 1e17;
double pi = acos(-1);

int n;
pii arr[MAX];

LL ans[MAX];
int main(){
	scanf("%d",&n);
	for(int i = 1; i <= n; i++) {
		int k; scanf("%d",&k); arr[i].f = k;
		arr[i].s = i;
	}
	
	sort(arr + 1, arr + n + 1);
	
	LL maks = arr[1].f;
	ans[arr[1].s] = arr[1].f;
	for(int i = 2; i <= n; i++) {
		LL maxi = max(maks + 1, (LL)arr[i].f);
		ans[arr[i].s] = maxi;
		maks = maxi;
	}
	
	for(int i = 1; i <= n; i++)  {
		if (i != n) printf("%lld ",ans[i]);
		else printf("%lld\n",ans[i]);
	}
}