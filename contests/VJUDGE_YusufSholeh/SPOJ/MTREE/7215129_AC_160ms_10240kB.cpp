#include<bits/stdc++.h>
#define MAX 100005
#define LL long long
#define MOD 1000000007
using namespace std;

typedef pair<int,LL> pii;
#define f first
#define s second
#define mp make_pair

int n;
vector<pii> G[MAX];
LL dp[MAX];
LL bawah[MAX];
LL ans = 0;

void dfs(int now, int par) {
	int size = G[now].size();
	int leaf = 0;
	for(int i = 0; i < size; i++) {
		pii nxt = G[now][i];
		int next = nxt.f;
		LL cost = nxt.s;
		if (next == par) continue;
		leaf++;
		dfs(next, now);
	}
	
	bawah[now] = 1;
	if (leaf == 0) return;
	
	LL sum = 0;
	dp[now] = 0;
	
	for(int i = 0; i < size; i++) {
		pii nxt = G[now][i];
		int next = nxt.f;
		LL cost = nxt.s;
		if (next == par) continue;
		dp[now] = (dp[now] + ((bawah[now]*cost)%MOD)*bawah[next])%MOD;
		bawah[now] = (bawah[now] + cost*bawah[next])%MOD;
	}
	
	ans = (ans + dp[now])%MOD;
}

int main() {
	scanf("%d",&n);
	for(int i = 1; i < n; i++) {
		int u, v, w;
		scanf("%d %d %d",&u, &v, &w);
		G[u].push_back(mp(v, w));
		G[v].push_back(mp(u, w));
	}
	
	dfs(1, -1);
	printf("%lld\n",ans);
}