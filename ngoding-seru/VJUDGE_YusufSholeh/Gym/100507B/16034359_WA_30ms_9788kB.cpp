#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define f first
#define s second
#define mp make_pair

const int N = 1e5 + 5;
const int MAXN = N;

int n;
int k[N], m[N];
vector<int> v[N];
vector<int> g[N];
vector<int> p[N];
vector<int> new_graph[MAXN];

set<int> dp[N];
int low[MAXN], num[MAXN], vis[MAXN];
int scc_root[MAXN];
vector<int> stek;
int cnt;

void tarjan(int v) {
  low[v] = num[v] = cnt++;
  vis[v] = 1; // mark as inside stack
  stek.push_back(v);
  for(int nex : g[v]) {
    if(vis[nex] == 0) tarjan(nex);
    if(vis[nex] == 1) low[v] = min(low[v],low[nex]);
  }
  if(low[v] == num[v]) {
    while(1) {
      int u = stek.back(); stek.pop_back();
      vis[u] = 2; // mark as out of stack and has been processed
      scc_root[u] = v;
      if(u == v) break;
    }
  }
}

bool bol[N];
void calc(int now) {
  if (bol[now]) return;
  bol[now] = true;
  for(int next : new_graph[now]) {
    calc(next);
    if ((int)dp[now].size() < 2) {
      if (k[next] != 0) {
        dp[now].insert(k[next]);
      }
      for(int val : dp[next]) {
        if ((int)dp[now].size() < 2) {
          dp[now].insert(val);
        }
      }
    }
  }
}

int main() {
  scanf("%d",&n);
  for(int i = 1; i <= n; i++) {
    scanf("%d",&k[i]);
    scanf("%d",&m[i]);
    for(int j = 1; j <= m[i]; j++) {
      int x;
      scanf("%d",&x);
      v[i].push_back(x);
      p[x].push_back(i);
    }
  }

  for(int i = 1; i <= n; i++) {
    for(int next : p[i]) {
      if (k[i] == 0) {
        g[i].push_back(next);
      }
    }
  }

  memset(vis, 0, sizeof vis);
  for(int i = 1; i <= n; i++) {
    if (vis[i] != 2) {
      tarjan(i);
    }
  }

  for(int i = 1; i <= n; i++) if (k[i] == 0) {
    for(int next : g[i]) {
      int root = scc_root[i];
      int next_root = scc_root[next];
      if (next_root != root) {
        new_graph[root].push_back(next_root);
      }
    }
  }

  for(int i = 1; i <= n; i++) {
    if (k[i] == 0) {
      calc(i);
    }
  }

  for(int i = 1; i <= n; i++) {
    if (k[i] == 0) {
      int root = scc_root[i];
      int root_one = scc_root[1];
      if (dp[root].size() > 1) {
        printf("unknown unknown\n");
      } else if (dp[root].size() == 0) {
        printf("sober sober\n");
      } else {
        if (root == root_one) {
          printf("unknown unknown\n");
        } else {
          printf("%d %d\n",*dp[root].begin(), *dp[root].begin());
        }
      }
    } else {
      set<int> now;
      for(int next : p[i]) {
        if (k[next] == 0) {
          int root = scc_root[next];
          for(int val : dp[root]) {
            now.insert(val);
          }
        } else {
          now.insert(k[next]);
        }
      }

      if (now.size() == 0) {
        printf("sober %d\n",k[i]);
      } else if (now.size() == 1) {
        if (i != 1) {
          printf("%d %d\n",*now.begin(), k[i]);
        } else {
          printf("unknown %d\n",k[i]);  
        }
      } else {
        printf("unknown %d\n",k[i]);
      }
    }
  }

  return 0;
}