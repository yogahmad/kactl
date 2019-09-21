#include<bits/stdc++.h>
using namespace std;
#define MAX 1005
int c, d, v;
vector<int> G[MAX];
int vis[MAX];
int with[MAX];
int day = 0;

bool match(int x) {
	int size = G[x].size();
	for(int i = 0; i < size; i++) {
		int next = G[x][i];
		// printf("NOW %d %d\n",x, next);
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

string cat_lover[MAX][2];
string dog_lover[MAX][2];
int ct, dt;

inline int parseToInt(string str) {
	int len = str.length();
	int ans = 0;
	for(int i = 1; i < len; i++) {
		int angka = (int)str[i] - '0';
		ans = 10*ans + angka;
	}
	return ans;
}

int main() {
	int tc; scanf("%d",&tc);
	while(tc--) {
		scanf("%d %d %d",&c, &d, &v);
		for(int i = 1; i < MAX; i++) G[i].clear();
		ct = 0, dt = 0;
		for(int i = 1; i <= v; i++) {
			string a, b;
			cin >> a >> b;
			if (a[0] == 'C') {
				ct++;
				cat_lover[ct][0] = a;
				cat_lover[ct][1] = b;
			} else {
				dt++;
				dog_lover[dt][0] = a;
				dog_lover[dt][1] = b;
			}
		}
		for(int i = 1; i <= ct; i++) {
			for(int j = 1; j <= dt; j++) {
				if (cat_lover[i][0] == dog_lover[j][1] || dog_lover[j][0] == cat_lover[i][1]) {
					// printf("%d %d\n",i, j);
					G[i].push_back(j);
				}
			}
		}
		
		memset(with,-1,sizeof(with));
		int ans = 0;
		for(int i = 1; i <= ct; i++) {
			day++;
			if (match(i)) ans++;
		}
		// printf("MATCH %d\n",ans);
		printf("%d\n",v - ans);
	}
}