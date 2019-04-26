/** Maximum Matching on General Graph **/
/* Blossom | O(V^3) */
 
#include<bits/stdc++.h>
using namespace std;

#define SZ(x) (int)x.size() 

int lca(vector<int>&match, vector<int>&base, vector<int>&p,int a,int b){
  vector<bool> used(SZ(match));
  while(true){
    a = base[a];
    used[a]=true;
    if(match[a]==-1)break;
    a = p[match[a]];
  }
  while(true){
    b = base[b];
    if(used[b])return b;
    b = p[match[b]];
  }
  return-1;
}
 
void markPath(vector<int>&match, vector<int>&base, vector<bool>&blossom, vector<int>&p,int v,int b,int children){
  for(; base[v]!= b; v = p[match[v]]){
    blossom[base[v]]= blossom[base[match[v]]]=true;
    p[v]= children;
    children = match[v];
  }
}
 
int findPath(vector<vector<int> > &graph, vector<int> &match, vector<int> &p,int root){
  int n = SZ(graph);
  vector<bool> used(n);
  for(int i = 0; i < p.size(); i++) p[i] = -1;
  vector<int> base(n);
  for(int i =0; i < n;++i) base[i]= i;
 
  used[root]=true;
  int qh =0;
  int qt =0;
  vector<int> q(n);
  q[qt++]= root;
  while(qh < qt){
    int v = q[qh++];
    for(int i = 0; i < graph[v].size(); i++) {
      int to = graph[v][i];
      if(base[v]== base[to]|| match[v]== to)continue;
      if(to == root || match[to]!=-1&& p[match[to]]!=-1){
        int curbase = lca(match, base, p, v, to);
        vector<bool> blossom(n);
        markPath(match, base, blossom, p, v, curbase, to);
        markPath(match, base, blossom, p, to, curbase, v);
        for(int i =0; i < n;++i){
          if(blossom[base[i]]){
            base[i]= curbase;
            if(!used[i]){
              used[i]=true;
              q[qt++]= i;
            }
          }
        }
      }else if(p[to]==-1){
        p[to]= v;
        if(match[to]==-1)return to;
        to = match[to];
        used[to]=true;
        q[qt++]= to;
      }
    }
  }
  return-1;
}
 
int maxMatching(vector<vector<int> > graph){
  int n = SZ(graph);
  vector<int> match(n,-1);
  vector<int> p(n);
  for(int i =0; i < n;++i){
    if(match[i]==-1){
      int v = findPath(graph, match, p, i);
      while(v !=-1){
        int pv = p[v];
        int ppv = match[pv];
        match[v]= pv;
        match[pv]= v;
        v = ppv;
      }
    }
  }
 
  int matches =0;
  for(int i =0; i < n;++i){
    if(match[i]!=-1){
      ++matches;
    }
  }
  return matches /2;
}

int main() {
	int tc;
	scanf("%d",&tc);
	while(tc--) {
		int n, m;
		scanf("%d %d",&n, &m);
		
		vector< vector<int> > graph;
		vector<int> tmp;
		for(int i = 0; i < n; i++) graph.push_back(tmp);
		
		for(int i = 1; i <= m; i++) {
			int a, b;
			scanf("%d %d",&a, &b); a--; b--;
			graph[a].push_back(b);
			graph[b].push_back(a);
		}
		
		int ans = maxMatching(graph);
		
		
		printf(ans == (n+1)/2 ? "YES" : "NO"); printf("\n");
	}
	return 0;
}