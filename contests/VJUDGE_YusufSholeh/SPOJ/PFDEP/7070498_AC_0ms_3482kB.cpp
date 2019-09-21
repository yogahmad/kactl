#include<bits/stdc++.h>
#define MAX 105
using namespace std;
int n, m;
int G[MAX][MAX];
int in_deg[MAX];
priority_queue<int, vector<int>, greater<int> > pq;
int main() {
	scanf("%d %d",&n, &m);
	for(int i = 1; i <= m; i++) {
		int t0, k, t;
		scanf("%d %d",&t0, &k);
		for(int j = 1; j <= k; j++) {
			scanf("%d",&t);
			G[t][t0] = 1;
		}
		in_deg[t0] += k;
	}
	
	for(int i = 1; i <= n; i++) 
		if (in_deg[i] == 0)
			pq.push(i);
	
	bool space = false;
	while(!pq.empty()) {
		int top = pq.top();
		pq.pop();
		(space == true) ? printf(" ") : space = true;
		printf("%d",top);
		
		for(int i = 1; i <= n; i++) {
			if (G[top][i]) {
				in_deg[i]--;
				if (in_deg[i] == 0) pq.push(i);
			}
		}	
	}
	printf("\n");
}