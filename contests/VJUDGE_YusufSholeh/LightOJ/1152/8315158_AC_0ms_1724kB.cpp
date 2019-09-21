#include<bits/stdc++.h>
using namespace std;
#define MAX 1005
int r, c;

char s[50][50];
vector<int> v[MAX];
int vis[MAX];
int with[MAX];
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

bool checkInGrid(int x, int y) {
	if (x >= 0 && y >= 0 && x < r && y < c) return 1;
	return 0;
}

bool isAlone(int x, int y) {
	if (checkInGrid(x-1,y) && s[x-1][y] == '*') return false;
	if (checkInGrid(x+1,y) && s[x+1][y] == '*') return false;
	if (checkInGrid(x,y-1) && s[x][y-1] == '*') return false;
	if (checkInGrid(x,y+1) && s[x][y+1] == '*') return false;
	return true;
}

bool isGold(int x, int y) {
	if (checkInGrid(x,y) && s[x][y] == '*') return true;
	return false;
}

inline int node(int x, int y){
	return x*c + y;
}

bool udah[MAX];

int total_nodes = 0;

void done(int x, int y) {
	if (udah[node(x,y)] == false) {
		udah[node(x,y)] = true;
		// printf("%d %d\n",x,y);
		total_nodes++;
	}
}


int main() {
	int tc; scanf("%d",&tc); 
	for(int cs = 1; cs <= tc; cs++) {
		scanf("%d %d",&r,&c);
		for(int i = 0; i < r; i++) {
			scanf("%s",s[i]);
		}
		int ans = 0;
		for(int i = 0; i < r; i++) {
			for(int j = 0; j < c; j++) {
				if (s[i][j] == '*' && isAlone(i,j)) {
					ans++;
				}
			}
		}
		
		memset(udah,false,sizeof(udah));
		for(int i = 0; i < MAX; i++) v[i].clear();
		total_nodes = 0;
		for(int i = 0; i < r; i++) {
			for(int j = 0; j < c; j++) {
				if ((i+j)%2 == 0 && s[i][j] == '*') {
					if (isGold(i,j+1)) {
						done(i,j);
						done(i,j+1);
						v[node(i,j)].push_back(node(i,j+1));
						// printf("TEST1 %d %d\n",i,j);
					}
					if (isGold(i,j-1)) {
						done(i,j);
						done(i,j-1);
						v[node(i,j)].push_back(node(i,j-1));
						// printf("TEST2 %d %d\n",i,j);
					}
					if (isGold(i-1,j)) {
						done(i,j);
						done(i-1,j);
						v[node(i,j)].push_back(node(i-1,j));
						// printf("TEST3 %d %d\n",i,j);
					}
					if (isGold(i+1,j)) {
						done(i,j);
						done(i+1,j);
						v[node(i,j)].push_back(node(i+1,j));
						// printf("TEST4 %d %d\n",i,j);
					}
				}
			}
		}
		
		int max_bipar = 0;
		memset(with,-1,sizeof(with));
		for(int i = 0; i < 500; i++) {
			day++;
			if (match(i)) max_bipar++;
		}
		
		// printf("%d %d\n",total_nodes, max_bipar);
		
		printf("Case %d: ",cs);
		
		
		//max_bipar + total_nodes - 2*max_bipar
		
		printf("%d\n",ans + total_nodes - max_bipar);
	}
}