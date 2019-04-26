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
#define MAX 100005

double EPS = 1e-9;
int INF = 1e9+7;;
long long INFLL = 1e17;
double pi = acos(-1);

bool bol[1300005];
int prime[MAX+MAX];
int X[MAX+MAX];
int top = 0;

int tree[4*MAX];

void update(int now, int l, int r, int pos, int val) {
	if (l == r) {
		tree[now] = val;
		return;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid) update(now<<1,l,mid,pos,val);
	else update(now<<1|1,mid+1,r,pos,val);
	tree[now] = max(tree[now<<1], tree[now<<1|1]);
}

int query(int now, int l, int r, int a, int b) {
	if (a > r || b < l) return 0;
	if (a <= l && r <= b) return tree[now];
	int mid = (l + r) >> 1;
	return max(query(now<<1,l,mid,a,b),query(now<<1|1,mid+1,r,a,b));
}

int main(){
	
	
	for(int i = 2; i < 1300000; i++) {
		if (bol[i] == false) {
			prime[++top] = i;
			// if (i < 100) printf("%d\n",i);
			for(int j = i+i; j < 1300000; j+= i) {
				bol[j] = true;
			}
		}
	}
	// printf("%d\n",top);
	
	int tc;
	scanf("%d",&tc);
	while(tc--) {
		int n, m;
		scanf("%d %d",&n, &m);
		for(int i = 1; i <= 4*m; i++) tree[i] = 0;
		for(int i = 1; i <= n; i++) X[i] = prime[i] % m;
		// for(int i = 1; i <= n; i++) printf("%d ",X[i]); printf("\n");
		
		int ans = 0;
		for(int i = 1; i <= n; i++) {
			int maks = query(1,1,n,X[i]+1,m) + 1;
			// printf("%d %d\n",maks,i-maks+1);
			ans += (i-maks+1);
			ans %= m;
			update(1,1,n,X[i],i);
		}
		
		printf("%d\n",ans);
	}
}