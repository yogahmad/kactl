/**
 * Author: Chen Xing
 * Date: 2009-10-13
 * License: CC0
 * Source: N/A
 * Description: Find a maximum matching in a bipartite graph.
 * Status: Tested on oldkattis.adkbipmatch and SPOJ:MATCHING
 * Usage: node from 1..n ||  0 is NIL
 * left side 1..n || right side n+1..n+m
 * G = {0} U {1..n} U {n+1..n+m}
 * Time: O(\sqrt{V}E)
 */
#pragma once

bool bfs() {
  queue<int> q;
  for(int i = 1 ; i <= n ; i++)
    if(match[i] == 0) {
      dist[i] = 0;
      q.push(i);
    }
    else
      dist[i] = INF;
  dist[0] = INF;
  
  while(!q.empty()) {
    int cur = q.front();
    q.pop();
    if(cur) {
      for(int nex : adj[cur]) {
        if(dist[match[nex]] == INF) {
          dist[match[nex]] = dist[cur] + 1;
          q.push(match[nex]);
        }
      }
    }
  }
  return dist[0] != INF;    
}
int dfs(int now) {
  if(now == 0) return 1; // found 1 augmenting path
  for(int nex : adj[now]) {
    if(dist[match[nex]] == dist[now] + 1 && dfs(match[nex])) {
      match[nex] = now;
      match[now] = nex;
      return 1;
    }
  }
  dist[now] = INF;
  return 0;
}
int hopcroftKarp() {
  int ret = 0;
  memset(match, 0, sizeof match);
  while(bfs()) {
    for(int i = 1 ; i <= n ; i++)
      if(match[i] == 0)
        ret += dfs(i);
  }  
  return ret;
}
