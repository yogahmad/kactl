#include<bits/stdc++.h>
using namespace std;

typedef vector<int> VD; // rubah double
typedef vector<VD> VVD;
typedef vector<int> VI;

int MinCostMatching(const VVD &cost, VI &Lmate, VI &Rmate) { // rubah double
  int n = int(cost.size());

  // construct dual feasible solution
  VD u(n);
  VD v(n);
  for (int i = 0; i < n; i++) {
    u[i] = cost[i][0];
    for (int j = 1; j < n; j++) u[i] = min(u[i], cost[i][j]);
  }
  for (int j = 0; j < n; j++) {
    v[j] = cost[0][j] - u[0];
    for (int i = 1; i < n; i++) v[j] = min(v[j], cost[i][j] - u[i]);
  }
  
  // construct primal solution satisfying complementary slackness
  Lmate = VI(n, -1);
  Rmate = VI(n, -1);
  int mated = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (Rmate[j] != -1) continue;
      if (fabs(cost[i][j] - u[i] - v[j]) < 1e-10) {
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
  
  // repeat until primal solution is feasible
  while (mated < n) {
    
    // find an unmatched left node
    int s = 0;
    while (Lmate[s] != -1) s++;
    
    // initialize Dijkstra
    fill(dad.begin(), dad.end(), -1);
    fill(seen.begin(), seen.end(), 0);
    for (int k = 0; k < n; k++) 
      dist[k] = cost[s][k] - u[s] - v[k];
    
    int j = 0;
    while (true) {
      
      // find closest
      j = -1;
      for (int k = 0; k < n; k++) {
        if (seen[k]) continue;
        if (j == -1 || dist[k] < dist[j]) j = k;
      }
      seen[j] = 1;
      
      // termination condition
      if (Rmate[j] == -1) break;
      
      // relax neighbors
      const int i = Rmate[j];
      for (int k = 0; k < n; k++) {
        if (seen[k]) continue;
        const int new_dist = dist[j] + cost[i][k] - u[i] - v[k]; // rubah double
        if (dist[k] > new_dist) {
          dist[k] = new_dist;
          dad[k] = j;
        }
      }
    }
    
    // update dual variables
    for (int k = 0; k < n; k++) {
      if (k == j || !seen[k]) continue;
      const int i = Rmate[k];
      v[k] += dist[k] - dist[j];
      u[i] -= dist[k] - dist[j];
    }
    u[s] += dist[j];
    
    // augment along path
    while (dad[j] >= 0) {
      const int d = dad[j];
      Rmate[j] = Rmate[d];
      Lmate[Rmate[j]] = j;
      j = d;
    }
    Rmate[j] = s;
    Lmate[s] = j;
    
    mated++;
  }
  
  int value = 0; //rubah double
  for (int i = 0; i < n; i++)
    value += cost[i][Lmate[i]];
  
  return value;
}

typedef pair<int,int> pii;
#define f first
#define s second
#define mp make_pair


int dist(pii a, pii b) {
	return abs(a.f - b.f) + abs(a.s - b.s);
}

pii arr[20];

int main() {
	int tc, n;
	int board = 0;
	while(scanf("%d",&n) && n) {
		
		for(int i = 0; i < n; i++) {
			scanf("%d %d",&arr[i].f, &arr[i].s);
		}
		VI a(n);
		VI b(n);
		
		int ans = 100000;
		
		// horizontal
		for(int x = 1; x <= n; x++) {
			VVD cost;
			for(int i = 0; i < n; i++) {
				VI adj(n);
				for(int y = 1; y <= n; y++) {
					adj[y-1] = dist(arr[i], mp(x, y));
				}
				cost.push_back(adj);
			}
			// printf("WTF %d\n", n);
			ans = min(ans, MinCostMatching(cost, a, b));
			// printf("WTFX %d\n", n);
		}
		
		// printf("PINDAH\n");
		// vertical
		for(int y = 1; y <= n; y++) {
			VVD cost;
			for(int i = 0; i < n; i++) {
				VI adj(n);
				for(int x = 1; x <= n; x++) {
					adj[x-1] = dist(arr[i], mp(x, y));
				}
				cost.push_back(adj);
			}
			// printf("2WTF %d\n", n);
			ans = min(ans, MinCostMatching(cost, a, b));
			// printf("2WTFX %d\n", n);
		}
		
		for(int xx = 0; xx < 2; xx++) {
			VVD cost;
			for(int i = 0; i < n; i++) {
				VI adj(n);
				for(int k = 1; k <= n; k++) {
					if (xx == 0) adj[k-1] = dist(arr[i], mp(k,k));
					else adj[k-1] = dist(arr[i], mp(n-k+1,k));
				}
				cost.push_back(adj);
			}
			ans = min(ans, MinCostMatching(cost, a, b));
		}
		
		printf("Board %d: %d moves required.\n",++board, ans);
	}
}