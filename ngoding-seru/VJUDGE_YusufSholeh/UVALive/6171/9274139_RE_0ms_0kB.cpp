#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define f first
#define s second
#define mp make_pair

const int MAX_GRID = 300;

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
	if (c == 'W') now.f -= 1;
	if (c == 'S') now.s -= 1;
	if (c == 'E') now.f += 1;
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
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	origin.f = MAX_GRID/2;
	origin.s = MAX_GRID/2;
	
	int T = 0;
	while(cin >> T) { 
		if (T == 0) return 0;
		memset(state,0,sizeof(state));
		head = origin;
		visit(head);
		
		string s; getline(cin, s);
		getline(cin, s);
		for(int i = 0; i < s.size(); i++) {
			int j = i;
			int num = 0;
			while(!isalpha(s[j])) {
				num = (10 * num + ((int)s[j] - '0'));
				j += 1;
			}
			i = j;
			for(int k = 0; k < num; k++) {
				move(head, s[j]);
				visit(head);
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
		cout << ans << endl;
	}
	
	return 0;
}