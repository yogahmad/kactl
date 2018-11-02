/**
 * Author: Chen Xing
 * Date: 2009-10-13
 * License: CC0
 * Source: N/A
 * Description: Flow algorithm with guaranteed complexity $O(V^2E)$.
 * Status: Working
 */
#pragma once

struct edge{
  int to, rev;
  int flow, cap;
};
vector<edge> G[MAXE];
inline void add(int s, int t, int cap) {
  edge a = {t, G[t].size(), 0, cap};
  edge b = {s, G[s].size(), 0, 0};
  G[s].push_back(a);
  G[t].push_back(b);
}
inline bool search() {
  for(int i = 0; i <= n + 1; i++) dist[i] = -1;
  dist[source] = 0;
  int tail = 0;
  q[tail] = source;
  for(int head = 0; head <= tail; head++) {
    int u = q[head];
    int sz = G[u].size();
    for(int i = 0; i < sz; i++) {
      int v = G[u][i].to;
      if (dist[v] < 0 && G[u][i].flow < G[u][i].cap) {
        dist[v] = dist[u] + 1;
        q[++tail] = v;
      }
    }
  }
  return dist[sink] >= 0;
}
int dinic(int now, int flo) {
  if (now == sink)
    return flo;
  int size = G[now].size();
  for(int &i = work[now]; i < size; i++) {
    int to = G[now][i].to, flow = G[now][i].flow, cap = G[now][i].cap, rev = G[now][i].rev;
    if (flow >= cap) continue;
    if (dist[to] == dist[now] + 1) {
      int fflow = dinic(to, min(flo, cap - flow));
      if (fflow) {
        G[now][i].flow += fflow;
        G[to][rev].flow -= fflow;
        return fflow;
      }
    }
  } 
  return 0;
}
inline int maxflow() {
  int ans = 0;
  while(search()) {
    for(int i = 0; i <= n + 1; i++) work[i] = 0;
    while(true) {
      int res = dinic(source, INF);
      if (res == 0) break;
      ans += res;
    }
  }
  return ans;
}
