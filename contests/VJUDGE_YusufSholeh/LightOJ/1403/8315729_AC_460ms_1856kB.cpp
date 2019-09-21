#include<bits/stdc++.h>
using namespace std;
#define MAX 1005
int n;

vector<int> v[MAX];
int vis[MAX];
int with[MAX];
int flag[MAX];
int day = 0;

bool match(int x) {
	int size = v[x].size();
	for(int i = 0; i < size; i++) {
		int next = v[x][i];
		if (vis[next] != day) {
			vis[next] = day;
			if (with[next] == -1 || match(with[next])) {
				with[next] = x;
				return true;
			}
		}
	}
	return false;
}

int main() {
	// srand(time(NULL));
	
	int tc; scanf("%d",&tc);
	for(int cs = 1; cs <= tc; cs++) {
		int n, m; scanf("%d %d",&n, &m);
		for(int i = 1; i <= m; i++) {
			int a, b;
			scanf("%d %d",&a, &b);
			v[a].push_back(b);
		}
		// for(int i = 1; i <= n; i++) {
			// random_shuffle(v[i].begin(), v[i].end());
		// }
		
		int ans = 0;
		memset(with,-1,sizeof(with));
		for(int i = 0; i < MAX; i++) {
			day++;
			if (match(i)) ans++;
		}
		
		printf("Case %d: ",cs);
		printf("%d\n",n - ans);
		
		for(int i = 1; i <= n; i++) v[i].clear();
	}
}