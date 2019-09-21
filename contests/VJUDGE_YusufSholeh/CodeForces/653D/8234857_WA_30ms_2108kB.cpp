#include<bits/stdc++.h>
#define MAX 55
using namespace std;

const double INF = 1e9 + 5;

int source, sink;
int n, m;
int A[505], B[505];
double C[505];
int parent[MAX], visited[MAX];
double tcap[MAX][MAX];
double cap[MAX][MAX];
double augment;
double x;

void back(int v, double minnow) {
	if (source == v) {
		augment = minnow;
		// printf("WTF ASDOUSho %.5lf\n",augment);
	} else if (parent[v] != -1) {
		back(parent[v], min(minnow, cap[parent[v]][v]));
		cap[parent[v]][v] -= augment;
		cap[v][parent[v]] += augment;
	}
}

int main() {
	scanf("%d %d %lf",&n, &m, &x);
	for(int i = 1; i <= m; i++) {
		int a, b, c;
		scanf("%d %d %d",&a, &b, &c);
		A[i] = a, B[i] = b, C[i] = (double)c;
		tcap[a][b] = c;
	}
	
	double l = 0, r = 1000000000;
	while(fabs(r-l) > 1e-8) {
		double mid = (l + r)/2.0;
		
		memset(cap, 0, sizeof(cap));
		for(int i = 1; i <= m; i++) {
			cap[A[i]][B[i]] = floor(C[i]/mid);
			// printf("%.5lf\n",cap[A[i]][B[i]]);
		}
		
		source = 1;
		sink = n;
		double ans = 0;
		while (true) {
			memset(parent, -1, sizeof parent);
			memset(visited, 0, sizeof visited);
			queue<int> q; q.push(source); 
			visited[source] = 1;
			while (!q.empty()) {
				int f = q.front(); 
				q.pop();
				if (f == sink) break;
				for (int t = 1; t <= n; t++) {
					if (cap[f][t] > 0 && !visited[t])
						q.push(t), visited[t] = 1, parent[t] = f;
				}
			}
			// printf("WTF %d\n",visited[sink]);
			if (visited[sink] == 0)  break;
			augment = 0;
			back(sink, 1e9+5);
			ans += augment;
		}
		
		// printf("%.5lf %.5lf %.5lf %.5lf\n",ans,l,r,mid);
		if (ans >= x) {
			l = mid;
		} else {
			r = mid;
		}
	}
	printf("%.8lf\n",l*x);
}