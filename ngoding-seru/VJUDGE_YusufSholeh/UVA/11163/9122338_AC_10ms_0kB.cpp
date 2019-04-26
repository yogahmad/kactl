#include<bits/stdc++.h>
using namespace std;

const int MAXN = 41;

int warshall[MAXN][MAXN];
int natural[MAXN];
int arr[MAXN], n;
int jump[4][4] = {{-3, -1, 4, -4},{1, 3, 4, -4},{1, -1, 4, -4}, {1, -1, 4, -4}};
inline void copy_natural() {
	for(int i = 0; i < MAXN; i++) arr[i] = natural[i];
}

inline void init() {
	for(int i = 0; i < MAXN; i++) 
		for(int j = 0; j < MAXN; j++) 
			warshall[i][j] = 1e9;
	for(int i = 0; i < MAXN; i++) warshall[i][i] = 0;
	for(int i = 1; i < MAXN; i++) {
		for(int j = 0; j < 4; j++) {
			if (i + jump[i % 4][j] > 0 && i + jump[i % 4][j] < MAXN) {
				warshall[i][i + jump[i % 4][j]] = 1;
				warshall[i + jump[i % 4][j]][i] = 1;
			}
		}
	}
	
	for(int k = 1; k < MAXN; k++) {
		for(int i = 1; i < MAXN; i++) {
			for(int j = 1; j < MAXN; j++) {
				warshall[i][j] = min(warshall[i][j], warshall[i][k] + warshall[k][j]);
			}
		}
	}
	
}

int depth = 0;
int natural_pos = 0;
int pos[MAXN];
bool dfs(int now, int step, int kira, int jaguar, int lastjaguar) {
	if (kira == 0) return true;
	if (step + kira > depth) return false;
	//printf("WTF step, kira, jaguar : %d %d %d\n",step, kira, jaguar);
	for(int i = 0; i < 4; i++) {
		int Swap = jaguar + jump[jaguar % 4][i];
		if (Swap > 0 && Swap <= n && Swap != lastjaguar) {
			int Kira2 = kira - warshall[arr[Swap]][Swap] + warshall[arr[Swap]][jaguar];
			swap(arr[jaguar], arr[Swap]);
			if (dfs(now-1,step+1,Kira2, Swap, jaguar)) return true;
			swap(arr[jaguar], arr[Swap]);
		}
	}
	return false;
}
 
int main() {
	init();
	int tc, cs = 0;
	while(scanf("%d",&n) != EOF) {
		if (n == 0) break;
		for(int i = 1; i <= n; i++) scanf("%d",&natural[i]);
		int ans = 0;
		depth = 0;
		int kira = 0, jaguar;
		for(int i = 1; i <= n; i++) {
			if (natural[i] == 1) jaguar = i;
			else {
				// printf("%d %d\n",i, warshall[i][natural[i]]);
				kira += warshall[i][natural[i]];
			}
		}
		while(true) {
			copy_natural();
			if (dfs(ans, 0, kira, jaguar, -1)) {
				printf("Set %d:\n%d\n",++cs,ans);
				break;
			}
			ans += 1;
			depth = ans;
		}
	}
}