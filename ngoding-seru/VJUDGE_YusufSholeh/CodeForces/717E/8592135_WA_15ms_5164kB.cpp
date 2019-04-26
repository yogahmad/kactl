#include<bits/stdc++.h>
using namespace std;

#define MAX 200005

int color[MAX];
int n;

vector<int> v[MAX];
vector<int> seq;

void dfs(int now, int par) {
	seq.push_back(now);
	if (now != 1) color[now] = 1 - color[now];
	int size = v[now].size();
	for(int i = 0; i < size; i++) {
		int next = v[now][i];
		if (next == par) continue;
		dfs(next, now);
	}
	
	for(int i = 0; i < size; i++) {
		int next = v[now][i];
		if (next == par) continue;
		if (color[next] == 0) {
			seq.push_back(next);
			color[next] = 1 - color[next];
			seq.push_back(now);
			color[now] = 1 - color[now];
		}
	}
	
	if (par != -1) {
		seq.push_back(par);
		color[par] = 1 - color[par];
	}
}

int main() {
	scanf("%d",&n);
	int all_black = 1;
	for(int i = 1; i <= n; i++) {
		scanf("%d",&color[i]);
		if (color[i] == -1) {
			color[i] = 0;
			all_black = 0;
		}
	}
	
	if (all_black == 1) {
		printf("1\n");
		return 0;
	}
	
	for(int i = 1; i < n; i++) {
		int a, b;
		scanf("%d %d",&a, &b);
		v[a].push_back(b);
		v[b].push_back(a);
	}
	
	dfs(1, -1);
	
	for(int i = 0; i < (int)seq.size(); i++) {
		if (i==(int)seq.size()-1) {
			printf("%d\n",seq[i]);
		} else {
			printf("%d ",seq[i]);
		}
	}
	
	return 0;
}
