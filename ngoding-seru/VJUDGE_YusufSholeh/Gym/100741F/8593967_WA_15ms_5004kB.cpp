#include<bits/stdc++.h>
using namespace std;

#define MAXN 305
#define MAX 90005
#define INF 1e9

int n, N;
int arr[MAXN][MAXN];
int num[MAX];
int vis[MAX], day = 0;
int answer[MAX];
int with[MAX];
vector<int> v[MAX];

bool match(int now) {
	int size = v[now].size();
	for(int i = 0; i < size; i++) {
		int next = v[now][i];
		if (vis[next] != day) {
			vis[next] = day;
			if (with[next] == -1 || match(with[next])) {
				with[next] = now;
				answer[now] = next;
				return true;
			}
		}
	}
	return false;
}

int MCBM() {
	day++;
	int ans = 0;
	memset(vis,0,sizeof(vis));
	memset(with,-1,sizeof(with));
	for(int i = 1; i <= 2*n; i++) {
		day++;
		if (match(i)) ans++;
	}
	return ans;
}

int main() {
	map<int,int> maps;
	map<int,int> rev;
	scanf("%d",&n);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			scanf("%d",&arr[i][j]);
			maps[arr[i][j]]++;
		}
	}
	int cnt = 0;
	for(map<int,int>::iterator it = maps.begin(); it != maps.end(); it++) {
		rev[it->first] = ++cnt;
		num[cnt] = it->first;
	}
	
	for(int diag = 1; diag <= n; diag++) {
		int col = 1;
		int row = diag;
		
		while(row > 0) {
			//cout << diag << " " << rev[arr[row][col]] << endl;
			v[diag].push_back(rev[arr[row][col]]);
			row--, col++;
		}
	}
	
	for(int diag = n+1; diag < n+n; diag++) {
		int col = diag - n + 1;
		int row = n;
		while(col <= n) {
			//cout << diag << " WTF " << rev[arr[row][col]] << endl;
			v[diag].push_back(rev[arr[row][col]]);
			row--, col++;
		}
	}
	
	int max_bipar = MCBM();
	//cout << max_bipar << endl;
	if (max_bipar != 2*n - 1) {
		printf("NO\n");
	} else {
		printf("YES\n");
		for(int i = 1; i < n+n; i++) {
			int result = answer[i];
			if (i == n+n-1) {
				printf("%d\n",num[result]);
			} else {
				printf("%d ",num[result]);
			}
		}
	}
}
