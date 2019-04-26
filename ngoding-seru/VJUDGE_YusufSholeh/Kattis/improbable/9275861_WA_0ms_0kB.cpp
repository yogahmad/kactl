#include<bits/stdc++.h>
using namespace std;

const int MAX = 105;

int r, c;
int arr[MAX][MAX];
int row[MAX];
int col[MAX];

vector<int> v[MAX];
int vis[MAX];
int with[MAX];
int kanan[MAX];

bool match(int x) {
	int size = v[x].size();
	for(int i = 0; i < size; i++) {
		int next = v[x][i];
		if (vis[next] == -1) {
			vis[next] = 1;
			if (with[next] == -1 || match(with[next])) {
				with[next] = x;
				kanan[x] = next;
				return true;
			}
		}
	}
	return false;
}

int main() {
	int tot = 0;
	
	scanf("%d %d",&r, &c);
	for(int i = 1; i <= r; i++) 
		for(int j = 1; j <= c; j++) {
			scanf("%d",&arr[i][j]);
			tot += max(arr[i][j] - 1, 0);
		}
		
		
	for(int i = 1; i <= r; i++)
		for(int j = 1; j <= c; j++)
			row[i] = max(row[i], arr[i][j] - 1);
		
	for(int i = 1; i <= c; i++)
		for(int j = 1; j <= r; j++)
			col[i] = max(col[i], arr[j][i] - 1);
		
	for(int i = 1; i <= r; i++)
		for(int j = 1; j <= c; j++)
			if (row[i] == col[j] && row[i] != 0 && arr[i][j] != 0) {
				v[i].push_back(j);
			}
	
	int res = 0;
	memset(with,-1,sizeof(with));
	memset(kanan,-1,sizeof(kanan));
	for(int i = 1; i <= r; i++) {
		memset(vis,-1,sizeof(vis));
		if (match(i)) res += 1;
	}
	
	int ans = 0;
	for(int i = 1; i <= c; i++) {
		ans += col[i];
	}
	for(int i = 1; i <= r; i++) {
		if (kanan[i] == -1) ans += row[i];
	}
	
	// printf("%d %d\n",ans, tot);
	
	printf("%d\n",tot - ans);
}