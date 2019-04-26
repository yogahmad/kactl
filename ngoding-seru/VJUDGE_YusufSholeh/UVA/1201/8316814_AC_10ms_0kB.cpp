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



inline int calculateMinutes(int sx, int sy, int tx, int ty) {
	return abs(sx - tx) + abs(sy - ty);
}
struct rides{
	int hour;
	int minute;
	int atMinutes;
	int goMinutes;
	int sx, sy;
	int tx, ty;
	void init() {
		atMinutes = hour*60 + minute;
		goMinutes = calculateMinutes(sx, sy, tx, ty);
	}
	void print() {
		printf("TEST RIDES\n");
		printf("%d:%d %d %d %d %d\n",hour,minute,sx,sy,tx,ty);
	}
};
rides arr[MAX];

int main() {
	int tc; scanf("%d",&tc);
	while(tc--) {
		scanf("%d",&n);
		for(int i = 1; i <= n; i++) {
			scanf("%d:%d %d %d %d %d",&arr[i].hour, &arr[i].minute, &arr[i].sx, &arr[i].sy, &arr[i].tx, &arr[i].ty);
			arr[i].init();
		}
		for(int i = 1; i <= n; i++) {
			for(int j = i + 1; j <= n; j++) {
				if (arr[i].atMinutes + arr[i].goMinutes + calculateMinutes(arr[i].tx, arr[i].ty, arr[j].sx, arr[j].sy) < arr[j].atMinutes) {
					
					v[i].push_back(j);
				}
			}
		}
		
		int ans = 0;
		memset(with,-1,sizeof(with));
		for(int i = 1; i <= n; i++) {
			day++;
			if (match(i)) ans++;
		}
		
		printf("%d\n",n - ans);
		
		for(int i = 1; i <= n; i++) v[i].clear();
	}	
}