#include<bits/stdc++.h>
using namespace std;
#define MAX 1005
int r, c, n;

vector<int> v[MAX*2];
int vis[MAX*2];
int with[MAX*2];
int flag[MAX*2];
int day = 0;

bool match(int x) {
	int size = v[x].size();
	for(int i = 0; i < size; i++) {
		int next = v[x][i];
		if (vis[next] != day) {
			vis[next] = day;
			if (with[next] == -1 || match(with[next])) {
				with[next] = x;
				with[x] = next;
				return true;
			}
		}
	}
	return false;
}

int main() {
	while(true) {
		scanf("%d %d %d",&r, &c, &n);
		
		if (r == 0 && c == 0 && n == 0) return 0;
		for(int i = 1; i < MAX; i++) v[i].clear();
		for(int i = 1; i <= n; i++) {
			int a, b;
			scanf("%d %d",&a, &b);
			v[a].push_back(r + b);
		}
		day++;
		int ans = 0;
		memset(with,-1,sizeof(with));
		for(int i = 1; i <= r; i++) {
			day++;
			if (match(i)) ans++;
		}
		
		printf("%d",ans);
		
		queue<int> q;
		for(int i = 1; i <= r; i++) {
			if (with[i] == -1) {
				q.push(i);
				// printf("SAD %d\n",i);
			}
		}
		
		memset(flag,-1,sizeof(flag));
		while(!q.empty()) {
			int now = q.front();
			q.pop();
			
			// printf("WTF %d\n",now);
			flag[now] = 1;
			if (now > r) {
				if (with[now] != -1) {
					q.push(with[now]);
					flag[with[now]] = 1;
				}
				continue;
			}
			
			
			for(int i = 0, len = v[now].size(); i < len; i++) {
				int next = v[now][i];
				// printf("FTW %d\n",next);
				if (flag[next] == -1) {
					flag[next] = 1;
					q.push(next);
				}
			}
		}
		
		for(int i = r+1; i <= r+c; i++) {
			if (flag[i] == 1) {
				printf(" c%d",i-r);
			}
		}
		
		for(int i = 1; i <= r; i++) {
			if (flag[i] == -1) {
					printf(" r%d",i);
			}
		}
		
		
		printf("\n");
	}
}