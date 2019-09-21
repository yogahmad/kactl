#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define f first
#define s second
#define mp make_pair

int R, N;
pii restaurant[305];
pii order[305];


typedef vector<int> VD;
typedef vector<VD> VVD;
typedef vector<int> VI;

int MinCostMatching(const VVD &cost, VI &Lmate, VI &Rmate) {
	int n = (int)cost.size();
	
	VD u(n);
	VD v(n);
	
	for(int i = 0; i < n; i++) {
		u[i] = cost[i][0];
		for(int j = 1; j < n; j++) u[i] = min(u[i], cost[i][j]);
	}
	for(int j = 0; j < n; j++) {
		v[j] = cost[0][j] - u[0];
		for(int i = 1; i < n; i++) v[j] = min(v[j], cost[i][j] - u[i]);
	}
	
	Lmate = VI(n, -1);
	Rmate = VI(n, -1);
	int mated = 0;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if (Rmate[j] != -1) continue;
			if (abs(cost[i][j] - u[i] - v[j]) < 0) {
				Lmate[i] = j;
				Rmate[j] = i;
				mated++;
				break;
			}
		}
	}
	
	VD dist(n);
	VI dad(n);
	VI seen(n);
	
	while(mated < n) {
		int s = 0;
		while(Lmate[s] != -1) s++;
		
		fill(dad.begin(), dad.end(), -1);
		fill(seen.begin(), seen.end(), 0);
		
		for(int k = 0; k < n; k++) dist[k] = cost[s][k] - u[s] - v[k];
		
		int j = 0;
		
		while(true) {
			j = -1;
			for(int k = 0; k < n; k++) {
				if (seen[k]) continue;
				if (j == -1 || dist[k] < dist[j]) j = k;
			}
			seen[j] = 1;
			if (Rmate[j] == -1) break;
			
			const int i = Rmate[j];
			for(int k = 0; k < n; k++) {
				if (seen[k]) continue;
				const int new_dist = dist[j] + cost[i][k] - u[i] - v[k];
				if (dist[k] > new_dist) {
					dist[k] = new_dist;
					dad[k] = j;
				}
			}
		}
		
		for(int k = 0; k < n; k++) {
			if (k == j || !seen[k]) continue;
			const int i = Rmate[k];
			v[k] += dist[k] - dist[j];
			u[i] -= dist[k] - dist[j];
		}
		
		while(dad[j] >= 0) {
			const int d = dad[j];
			Rmate[j] = Rmate[d];
			Lmate[Rmate[j]] = j;
			j = d;
		}
		
		Rmate[j] = s;
		Lmate[s] = j;
		mated++;
	}
	
	int value = 0;
	for(int i = 0; i < n; i++) 
		value += cost[i][Lmate[i]];
	return value;
}

int dist(pii a, pii b) {
	return abs(a.f - b.f) + abs(a.s - b.s);
}

int main() {
	while(scanf("%d %d",&R, &N) != EOF) {
		for(int i = 0; i < R; i++) {
			scanf("%d %d",&restaurant[i].f, &restaurant[i].s);
		}
		for(int i = 0; i < N; i++) {
			scanf("%d %d",&order[i].f, &order[i].s);
		}
		
		VVD cost;
		
		for(int i = 0; i < R; i++) {
			VI adj(R);
			for(int j = 0; j < N; j++) adj[j] = dist(restaurant[i], order[j]);
			for(int j = N; j < R; j++) adj[j] = 0;
			cost.push_back(adj);
		}
		
		VI a(R);
		VI b(R);
		printf("%d\n",MinCostMatching(cost, a, b));
	}
}
