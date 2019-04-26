#include <bits/stdc++.h>
using namespace std;

struct Node { // Splay tree. Root's pp contains tree's parent.
    Node *p = 0, *pp = 0, *c[2];
    bool flip = 0;
  int dist = 1;
    Node() { dist = 1; c[0] = c[1] = 0; fix(); }
    void fix() {
        if (c[0]) c[0]->p = this;
        if (c[1]) c[1]->p = this;
        dist = 1;
    if (c[0]) dist += c[0]->dist;
    if (c[1]) dist += c[1]->dist;
        // (+ update sum of subtree elements etc. if wanted)
    }
    void push_flip() {
        if (!flip) return;
        flip = 0; swap(c[0], c[1]);
        if (c[0]) c[0]->flip ^= 1;
        if (c[1]) c[1]->flip ^= 1;
    }
    int up() { return p ? p->c[1] == this : -1; }
    void rot(int i, int b) {
        int h = i ^ b;
        Node *x = c[i], *y = b == 2 ? x : x->c[h], *z = b ? y : x;
        if ((y->p = p)) p->c[up()] = y;
        c[i] = z->c[i ^ 1];
        if (b < 2) {
            x->c[h] = y->c[h ^ 1];
            z->c[h ^ 1] = b ? x : this;
        }
        y->c[i ^ 1] = b ? this : x;
        fix(); x->fix(); y->fix();
        if (p) p->fix();
        swap(pp, y->pp);
    }
    void splay() { /// Splay this up to the root. Always finishes without flip set.
        for (push_flip(); p; ) {
            if (p->p) p->p->push_flip();
            p->push_flip(); push_flip();
            int c1 = up(), c2 = p->up();
            if (c2 == -1) p->rot(c1, 2);
            else p->p->rot(c2, c1 != c2);
        }
    }
    Node* first() { /// Return the min element of the subtree rooted at this, splayed to the top.
        push_flip();
        return c[0] ? c[0]->first() : (splay(), this);
    }
};

struct LinkCut {
    vector<Node> node;
    LinkCut(int N) : node(N) {}

    void link(int u, int v) { // add an edge (u, v)
        // assert(!connected(u, v));
        if (connected(u, v)) return;
        make_root(&node[u]);
        node[u].pp = &node[v];
    }
    void cut(int u, int v) { // remove an edge (u, v)
        if (!connected(u,v)) return;
        Node *x = &node[u], *top = &node[v];
        make_root(top); x->splay();
        // assert(top == (x->pp ?: x->c[0]));
        if (x->pp) x->pp = 0;
        else {
            x->c[0] = top->p = 0;
            x->fix();
        }
    }
    bool connected(int u, int v) { // are u, v in the same tree?
        Node* nu = access(&node[u])->first();
        return nu == access(&node[v])->first();
    }
    void make_root(Node* u) { /// Move u to root of represented tree.
        access(u);
        u->splay();
        if(u->c[0]) {
            u->c[0]->p = 0;
            u->c[0]->flip ^= 1;
            u->c[0]->pp = u;
            u->c[0] = 0;
            u->fix();
        }
    }
    Node* access(Node* u) { /// Move u to root aux tree. Return the root of the root aux tree.
        u->splay();
        if (u->c[1]) {
            u->c[1]->p = 0; u->c[1]->pp = u;
        }
        u->c[1]=0;
        u->fix();
        while (Node* pp = u->pp) {
            pp->splay(); u->pp = 0;
            if (pp->c[1]) {
                pp->c[1]->p = 0; pp->c[1]->pp = pp; }
            pp->c[1] = u; pp->fix(); u = pp;
        }
        return u;
    }
  int get_dist(int x) {
        make_root(&node[x]);
        return access(&node[1])->dist;
  }
};

const int N = 1e5 + 5;
int n, m;
int a[N];
vector<int> g[N];
int P[N][19];

const int LG = 19;

void build() {
  for(int j = 1; j < LG; j++) {
    for(int i = 1; i <= n; i++) {
      if (P[i][j-1] != -1) {
        P[i][j] = P[P[i][j-1]][j-1];
      } else {
        P[i][j] = -1;
      }
    }
  }
}

int get_par(int a, int x) {
  for(int j = LG-1; j >= 0; j--) {
    if (x & (1 << j)) {
      if (P[a][j] == -1) {
        return 1;      
      } else {
        a = P[a][j];
      }
    }
  }
  return a;
}

void dfs(int now, int par) {
  P[now][0] = par;
  for(int next : g[now]) {
    if (next == par) continue;
    dfs(next, now);
  }
}

int main() {
  scanf("%d %d",&n, &m);
  for(int i = 1; i <= n; i++) scanf("%d",&a[i]);
  for(int i = 1; i < n; i++) {
    int u, v;
    scanf("%d %d",&u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(1, -1);

  build();

  LinkCut graph(n+2);

  for(int i = 2; i <= n; i++) {
    int x = get_par(i, a[i]);
        // printf("%d %d\n",i, x);
    graph.link(i, x);
  }

  for(int i = 1; i <= m; i++) {
    int t;
    scanf("%d",&t);
    if (t == 1) {
      int node, x;
      scanf("%d %d",&node, &x);
      int anchor = get_par(node, x);
      graph.cut(node, get_par(node, a[node]));
      graph.link(node, anchor);
      a[node] = x;
    } else {
      int x;
      scanf("%d",&x);
      if (x != 1) printf("%d\n",graph.get_dist(x)-1);
            else printf("0\n");
    }
  }

  return 0;
}
