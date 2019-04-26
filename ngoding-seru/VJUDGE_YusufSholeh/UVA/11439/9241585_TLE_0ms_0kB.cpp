#include<bits/stdc++.h>
using namespace std;

#define SZ(x) (int)x.size()

int lca(vector<int> &match, vector<int> &base, vector<int> &p, int a, int b) {
	vector<bool> used(SZ(match));
	while(true) {
		a = base[a];
		used[a] = true;
		if (match[a] == -1) break;
		a = p[match[a]];
	}
	while(true) {
		b = base[b];
		if (used[b]) return b;
		b = p[match[b]];
	}
	return -1;
}

void markPath(vector<int> &match, vector<int> &base, vector<bool> &blossom, vector<int> &p, int v, int b, int children) {
	for(; base[v] != b; v = p[match[v]]) {
		blossom[base[v]] = blossom[base[match[v]]] = true;
		p[v] = children;
		children = match[v];
	}
}

int findPath(vector<vector<int> > &graph, vector<int> &match, vector<int> &p, int root) {
	int n = SZ(graph);
	vector<bool> used(n);
	for(int i = 0; i < (int)p.size(); i++) p[i] = -1;
	vector<int> base(n);
	for(int i = 0; i < n; i++) base[i] = i;
	
	used[root] = true;
	int qh = 0;
	int qt = 0;
	vector<int> q(n);
	q[qt++] = root;
	while(qh < qt) {
		int v = q[qh++];
		for(int i = 0; i < (int)graph[v].size(); i++) {
			int to = graph[v][i];
			if (base[v] == base[to] || match[v] == to) continue;
			if (to == root || match[to] != -1 && p[match[to]] != -1) {
				int curbase = lca(match, base, p, v, to);
				vector<bool> blossom(n);
				markPath(match, base, blossom, p, v, curbase, to);
				markPath(match, base, blossom, p, to, curbase, v);
				for(int i = 0; i < n; i++) {
					if (blossom[base[i]]) {
						base[i] = curbase;
						if (!used[i]) {
							used[i] = true;
							q[qt++] = i;
						}
					}
				}
			} else {
				p[to] = v;
				if (match[to] == -1) return to;
				to = match[to];
				used[to] = true;
				q[qt++] = to;
			}
		}
	}
	return -1;
}

int maxMatching(vector<vector<int> > graph) {
	int n = SZ(graph);
	vector<int> match(n,-1);
	vector<int> p(n);
	for(int i = 0; i < n; i++) {
		if (match[i] == -1) {
			int v = findPath(graph, match, p, i);
			while(v != -1) {
				int pv = p[v];
				int ppv = match[pv];
				match[v] = pv;
				match[pv] = v;
				v = ppv;
			}
		}
	}
	
	int matches = 0;
	for(int i = 0; i < n; i++) {
		if (match[i] != -1) {
			++matches;
		}
	}
	
	return matches/2;
}

int tc, cs(0);
int cost[155][155];
int main() {
	scanf("%d",&tc);
	while(tc--) {
		int n; scanf("%d",&n);
		n = (1 << n);
		for(int i = 0; i < n; i++) {
			for(int j = i + 1; j < n; j++) {
				scanf("%d",&cost[i][j]);
			}
		}
		
		int ans = 0;
		int l = 0, r = 1000000000;
		while(l <= r) {
			int mid = (l + r) >> 1;
			vector<vector<int> > graph;
			for(int i = 0; i < n; i++) {
				vector<int> tmp;
				graph.push_back(tmp);
			}
			for(int i = 0; i < n; i++) {
				for(int j = i+1; j < n; j++) {
					if (cost[i][j] >= mid) {
						graph[i].push_back(j);
						graph[j].push_back(i);
					}
				}
			}
			
			int cur = maxMatching(graph);
			
			//printf("%d %d\n",mid, cur);
			if (cur >= n/2) {
				l = mid + 1;
				ans = mid;
			} else {
				r = mid - 1;
			}
		}
		
		printf("Case %d: %d\n",++cs, ans);
	}
}
