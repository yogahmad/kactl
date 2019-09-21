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

int arr1[MAX];
int arr2[MAX];

int main() {
	// srand(time(NULL));
	
	int tc; scanf("%d",&tc);
	for(int cs = 1; cs <= tc; cs++) {
		int n, m; 
		
		scanf("%d",&n);for(int i = 1; i <= n; i++) scanf("%d",&arr1[i]);
		scanf("%d",&m);for(int i = 1; i <= m; i++) scanf("%d",&arr2[i]);
		
		for(int i = 1; i <= n; i++) {
			if (arr1[i] == 0) continue;
			for(int j = 1; j <= m; j++) {
				if (arr2[j] % arr1[i] == 0) {
					v[i].push_back(j);
				}
			}
		}
		
		int ans = 0;
		memset(with,-1,sizeof(with));
		for(int i = 0; i < MAX; i++) {
			day++;
			if (match(i)) ans++;
		}
		
		printf("Case %d: ",cs);
		printf("%d\n",ans);
		
		for(int i = 0; i < MAX; i++) v[i].clear();
	}
}