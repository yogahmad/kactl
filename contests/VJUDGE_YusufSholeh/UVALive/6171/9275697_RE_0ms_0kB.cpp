#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define f first
#define s second
#define mp make_pair

const int MAX_GRID = 80;

int tc;
int state[MAX_GRID][MAX_GRID];
int temp[MAX_GRID][MAX_GRID];
int day = 0;
int vis[MAX_GRID][MAX_GRID];

pii origin;
pii head, natural_head;

void visit(pii cell) {
	state[cell.f][cell.s] = 1;
}

void move(pii &now, char c) {
	if (c == 'N') now.s += 1;
	else if (c == 'W') now.f -= 1;
	else if (c == 'S') now.s -= 1;
	else if (c == 'E') now.f += 1;
	else assert(0);
}

void copy_natural() {
	for(int i = 0; i < MAX_GRID; i++)
		for(int j = 0; j < MAX_GRID; j++)
			state[i][j] = temp[i][j];
	head = natural_head;
}

void print(pii now) {
	printf("coord : %d %d\n",now.f, now.s);
}

int global = 1;
int FINAL = 0;
int mulai_step = 0;
void flood(pii now) {
	if (now.f == 0 || now.s == 0 || now.f == MAX_GRID || now.s == MAX_GRID) {
		global = 0;
		return;
	}
	if (state[now.f][now.s] == 1 || vis[now.f][now.s] == day) return;
	vis[now.f][now.s] = day;
	flood(mp(now.f + 1, now.s));
	flood(mp(now.f - 1, now.s));
	flood(mp(now.f, now.s + 1));
	flood(mp(now.f, now.s - 1));
}

void dfs(pii now, int step) {
	if (step != mulai_step && state[now.f][now.s] == 1) return;
	if (step == 0) {
		day += 1;
		flood(mp(now.f + 1, now.s));
		flood(mp(now.f - 1, now.s));
		flood(mp(now.f, now.s + 1));
		flood(mp(now.f, now.s - 1));
		if (global == 1) FINAL = 1;
		global = 1;
		return;
	}
	state[now.f][now.s] = 1;
	dfs(mp(now.f + 1, now.s), step - 1);
	dfs(mp(now.f - 1, now.s), step - 1);
	dfs(mp(now.f, now.s + 1), step - 1);
	dfs(mp(now.f, now.s - 1), step - 1);
	state[now.f][now.s] = 0;
}


int main() {
	
	origin.f = MAX_GRID/2;
	origin.s = MAX_GRID/2;
	
	int T = 0;
	char c, s[150];
	while(scanf("%d",&T) && T) { 
		if (T == 0) return 0;
		memset(state,0,sizeof(state));
		head = origin;
		visit(head);
		
		gets(s); gets(s);
		istringstream in(s);
		for(int i = 0; i < T; i++) {
			int num;
			while(in >> num >> c) {
				// printf("XX %d %c\n",num,c);
				for(int k = 0; k < num; k++) {
					move(head, c);
					visit(head);
				}
			}
		}
		
		for(int i = 0; i < MAX_GRID; i++)
			for(int j = 0; j < MAX_GRID; j++) {
				temp[i][j] = state[i][j];
				// if (state[i][j] == 1) printf("X %d %d\n",i, j);
			}
		natural_head = head;
		
		int ans = 6;
		for(int i = 0; i < 6; i++) {
			mulai_step = i;
			copy_natural();
			
			global = 1;
			FINAL = 0;
			dfs(head, i);
			
			if (FINAL == 1) {
				ans = i;
				break;
			}
		}
		printf("%d\n",ans);
	}
	
	return 0;
}