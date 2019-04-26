#include<bits/stdc++.h>
using namespace std;

#define pii pair<int,int>
#define f first
#define s second
#define mp make_pair
#define pb push_back
#define pf push_front

inline int ask_interactive(int x) {
	printf("? %d\n",x);
	fflush(stdout);
	int has;
	scanf("%d",&has);
	return has;
}

#define LL long long
#define INF 1e9
#define MAX 1005

char c[MAX][MAX];
int n, m;
int dist[MAX][MAX][4];
bool flag[MAX][MAX];
int states;

queue<pair<int,pii> > q;

inline void flood(int x, int y, int d) {
	if (x >= 0 && y >= 0 && x < n && y < m && flag[x][y] == false) {
		dist[x][y][states] = d;
		flag[x][y] = true;
		if (c[x][y] == '.') q.push(mp(d,mp(x,y)));
	}
}

int shortest(char id1) {
	// reset
		while(!q.empty()) q.pop(); 
		memset(flag,0,sizeof(flag));
	// reset
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if (c[i][j] == id1) {
				q.push(mp(0,mp(i,j)));
				dist[i][j][states] = 0;
				flag[i][j] = true;
			}
		}
	}
	
	while(!q.empty()) {
		pair<int,pii> top = q.front(); q.pop();
		int D = top.f; 
		int nx = top.s.f, ny = top.s.s;
		flood(nx + 1, ny, D + 1);
		flood(nx, ny + 1, D + 1);
		flood(nx - 1, ny, D + 1);
		flood(nx, ny - 1, D + 1);
	}
}

int pairs(int id1, char id2) {
	int ans = INF;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if (c[i][j] == id2) {
				if (dist[i][j][id1] != -1) {
					ans = min(ans, dist[i][j][id1]);
				}
			}
		}
	}
	return (ans == INF) ? 0 : ans;
}

int main(){
	
	memset(dist,-1,sizeof(dist));
	
	scanf("%d %d",&n, &m);
	
	for(int i = 0; i < n; i++) scanf("%s",&c[i]);
	
	// for(int i = 0; i < n; i++) printf("%s\n",c[i]);
	
	states = 1; shortest('1');
	states = 2; shortest('2');
	states = 3; shortest('3');
	
	int s12 = pairs(1, '2') - 1;
	int s13 = pairs(1, '3') - 1;
	int s23 = pairs(2, '3') - 1;
	
	int res = -1;
	if (s12 == -1 || s13 == -1 || s23 == -1) goto END;
	if (s12 == 0) {res = min(s23,s13); goto END;}
	if (s13 == 0) {res = min(s12,s23); goto END;}
	if (s23 == 0) {res = min(s12,s13); goto END;}
	res = INF;
	res = min(res, s12 + s13);
	res = min(res, s12 + s23);
	res = min(res, s13 + s23);
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			res = min(res, dist[i][j][1] + dist[i][j][2] + dist[i][j][3] - 2);
		}
	}
	
	printf("%d\n",res);
	return 0;
	END:; printf("%d\n",res);
	return 0;
}