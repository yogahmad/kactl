#include<bits/stdc++.h>
using namespace std;
#define MAX 405
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

string s[MAX][2];


int main() {
	while(true) {
		int n; scanf("%d",&n);
		
		if (n == 0) return 0;
		
		for(int i = 0; i < MAX; i++) v[i].clear();	
		
		for(int i = 1; i <= n; i++) {
			cin >> s[i][0] >> s[i][1];
		}
		
		for(int i = 1; i <= n; i++) {
			int valki = (int)s[i][0][0] - 'A';
			int valka = (int)s[i][1][0] - 'A';
			v[valki].push_back(valka);
		}
		
		int ans = 0;
		memset(with,-1,sizeof(with));
		for(int i = 0; i < MAX; i++) {
			day++;
			if (match(i)) ans++;
		}
		
		printf("%d\n",ans);
	}
}