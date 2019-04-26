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
#define MAX 100005

double EPS = 1e-9;
int INF = 1e9+7;;
long long INFLL = 1e17;
double pi = acos(-1);

LL a, b;

vector<pii> v[MAX];
bool flag[MAX];
int dist[MAX];

int main(){
	int tc;
	scanf("%d",&tc);
	for(int cs = 1; cs <= tc; cs++) {
		int n, m, s, t;
		scanf("%d %d %d %d",&n, &m, &s, &t);
		s++; t++;
		for(int i = 1; i <= n; i++) dist[i] = 2e9;
		for(int i = 1; i <= m; i++) {
			int u, V, w;
			scanf("%d %d %d",&u, &V, &w);
			u++; V++;
			v[u].push_back(mp(V,w));
			v[V].push_back(mp(u,w));
		}
		
		memset(flag,false,sizeof(flag));
		priority_queue<pii, vector<pii>, greater<pii> > pq;
		
		pq.push(mp(0,s));
		dist[s] = 0;
		
		while(!pq.empty()) {
			pii top = pq.top();
			pq.pop();
			int from = top.s;
			int D = top.f;
			
			if (flag[from]) continue;
			flag[from] = true;
			dist[from] = D;
			
			int size = v[from].size();
			for(int i = 0; i < size; i++) {
				int next = v[from][i].f;
				int jar = v[from][i].s;
				
				if (dist[next] > dist[from] + jar) {
					dist[next] = dist[from] + jar;
					pq.push(mp(dist[next], next));
				}
			}
		}
		
		printf("Case #%d: ",cs);
		if (dist[t] == 2e9) printf("unreachable\n");
		else printf("%d\n",dist[t]);
		
		for(int i = 1; i <= n; i++) v[i].clear();
	}
}