#include<bits/stdc++.h>
using namespace std;

const int MAXN = 12;

int warshall[MAXN][MAXN];
int d[] = {1, 3, 6, 12};
int natural[MAXN];
int arr[MAXN];

inline void copy_natural() {
	for(int i = 0; i < MAXN; i++) arr[i] = natural[i];
}

inline void init() {
	for(int i = 0; i < MAXN; i++) for(int j = 0; j < MAXN; j++) warshall[i][j] = 1e9;
	for(int i = 0; i < MAXN; i++) warshall[i][i] = 0;
	for(int i = 0; i < MAXN; i++) {
		for(int k = 0; k < 4; k++) {
			if (i + d[k] < MAXN && (i/d[k+1] == (i+d[k])/d[k+1])) {
				warshall[i][i+d[k]] = 1;
				warshall[i+d[k]][i] = 1;
			}
		}
	}
	
	for(int k = 0; k < MAXN; k++) {
		for(int i = 0; i < MAXN; i++) {
			for(int j = 0; j < MAXN; j++) {
				warshall[i][j] = min(warshall[i][j], warshall[i][k] + warshall[k][j]);
			}
		}
	}
	
}

int depth = 0;
int natural_pos = 0;
int pos[MAXN];
bool dfs(int now, int step) {
	int kira = 0;
	
	for(int i = 0; i < MAXN; i++) {
		if (arr[i] != 0) {
			kira += warshall[i][arr[i]];
		}
	}
	
	if (kira == 0) return true;
	if (now == 0 || step + kira > depth) return false;
	
	
	for(int i = 0; i < MAXN; i++) {
		for(int k = 0; k < 4; k++) {
			if (i + d[k] < MAXN && (arr[i] == 0 || arr[i+d[k]] == 0) && (i/d[k+1] == (i+d[k])/d[k+1])) {
				swap(arr[i], arr[i+d[k]]);
				if (dfs(now-1, step+1)) return true;
				swap(arr[i], arr[i+d[k]]);
			}
		}
	}		
	return false;
}

int main() {
	init();
	int tc;
	scanf("%d",&tc);
	while(tc--) {
		for(int i = 0; i < MAXN; i++) scanf("%d",&natural[i]);
		for(int i = 0; i < MAXN; i++) if (natural[i] == 0) natural_pos = i;
		int ans = 0;
		depth = 0;
		while(true) {
			copy_natural();
			if (dfs(ans, 0)) {
				printf("%d\n",ans);
				break;
			}
			ans += 1;
			depth = ans;
		}
	}
}