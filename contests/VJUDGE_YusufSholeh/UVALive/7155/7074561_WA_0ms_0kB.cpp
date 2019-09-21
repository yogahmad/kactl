#include<bits/stdc++.h>
#define MAX 55
using namespace std;
typedef pair<int,int> pii;
typedef pair<pii,pii> ppp;
#define f first
#define s second
#define mp make_pair
int n, m;
char G[MAX][MAX];
vector<pii> abj[129];
char cmd[10005];
int flag[51][51][10001];
pii kiri[52][52], kanan[52][52], atas[52][52], bawah[52][52];

queue<ppp> pq;

inline void go(int dist, int now, pii chk) {
	if (chk.f >= 0 && chk.s >= 0 && chk.f < n && chk.s < m)
		pq.push(mp( mp(now, dist + 1), chk));
}

int main() {
	
	int cs = 0;
	
	while(scanf("%d %d",&n, &m) != EOF) {
		cs++;
		for(int i = 0; i < 129; i++) abj[i].clear();
		memset(G, '\0', sizeof(G));
		for(int i = 0; i <= n; i++) 
			for(int j = 0; j <= m; j++) 
				kiri[i][j] = mp(i, j - 1),
				kanan[i][j] = mp(i, j + 1),
				atas[i][j] = mp(i - 1, j),
				bawah[i][j] = mp(i + 1, j);
		
		for(int i = 0; i < n; i++) 
			scanf("%s",&G[i]);
		
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				if (j && G[i][j-1] == G[i][j]) kiri[i][j] = kiri[i][j-1];
				if (i && G[i-1][j] == G[i][j]) atas[i][j] = atas[i-1][j];
			}
		}
		
		for(int i = n-1; i >= 0; i--) {
			for(int j = m-1; j >= 0; j--) {
				if (G[i][j + 1] == G[i][j]) kanan[i][j] = kanan[i][j + 1];
				if (G[i + 1][j] == G[i][j]) bawah[i][j] = bawah[i + 1][j];
			}
		}
		
		scanf("%s",&cmd);
		int len = strlen(cmd);
		cmd[len] = '*';
		len++;
		
		int fi = int(cmd[0]);
		pq.push(mp(mp(0, 0), mp(0, 0)));
		
		while(!pq.empty()) {
			ppp top = pq.front();
			pq.pop();
			
			int x = top.s.f;
			int y = top.s.s;
			
			if (G[x][y] == cmd[top.f.f]) {
				top.f.f += 1;
				top.f.s += 1;
			}
			
			if (top.f.f == len) {
				printf("%d\n", top.f.s);
				while(!pq.empty()) pq.pop();
				break;
			}
			
			if (flag[x][y][top.f.f] == cs) continue;
			flag[x][y][top.f.f] = cs;
			
			go(top.f.s, top.f.f, kanan[x][y]);
			go(top.f.s, top.f.f, kiri[x][y]);
			go(top.f.s, top.f.f, atas[x][y]);
			go(top.f.s, top.f.f, bawah[x][y]);
		}
		
		for(int i = 0; i < len; i++) cmd[i] = '\0';
	}
}