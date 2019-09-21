#include<bits/stdc++.h>
using namespace std;

const int MAX = 100005;
const int MAXK = 45;

int n, m;
int K[MAX];
int P[MAX][MAXK];
int LE[MAX];

typedef pair<int,int> pii;
#define f first
#define s second
#define mp make_pair

vector<pii> A[MAX];
int ans[MAX];

void compute(int id, int l, int r) {
	for(int i = l; i <= r; i++) LE[i] = l;
	for(int k = 2; k <= 40; k++) {
		int pre = l;
		int prev = -1;
		int now = 0;
		int last_0 = MAX*2;
		for(int i = l; i <= r; i++) {
			int real = A[id][i].f;
			if (K[real] % k != 0) now = -1;
			else now = A[id][i].s % k;
			
			if (now == -1) last_0 = min(last_0, i);
			
			if (i == l) {
				prev = now;
				continue;
			}
			
			if (now == -1) LE[i] = max(LE[i], pre);
			else {
				if (prev == -1 || now == prev) {
					LE[i] = max(LE[i], pre);
					if (prev == -1) prev = now;
				} else {
					pre = min(i, last_0);
					LE[i] = max(LE[i],min(i, last_0));
					prev = now;
				}
				last_0 = MAX*2;
			}
		}
	}
	
	for(int i = l; i <= r; i++) {
		// printf("ZZ %d %d\n",i, LE[i]);
		ans[id] = max(ans[id], i-LE[i]+1);
	}
}

int main() {
	scanf("%d %d",&n, &m);
	for(int i = 1; i <= n; i++){
		scanf("%d",&K[i]);
		for(int j = 1; j <= K[i]; j++) {
			scanf("%d",&P[i][j]);
			A[P[i][j]].push_back(mp(i, j));
		}
	}
	
	for(int i = 1; i <= m; i++) {
		int sz = A[i].size();
		for(int j = 0; j < sz; j++) {
			int l = j, r = j;
			
			while(r < sz - 1 && A[i][r + 1].f == A[i][r].f + 1) {
				r += 1;
			}
			
			if (r - l + 1 == 1) continue;
			
			// printf("ASD %d %d %d\n",i, l, r);
			compute(i, l, r);
			
			j = r;
		}
		if (A[i].size() > 0) ans[i] = max(ans[i], 1);
	}
	
	for(int i = 1; i <= m; i++) 
		printf("%d\n",ans[i]);
}