#include <bits/stdc++.h>
using namespace std;

#define LL long long

typedef pair<int,int> pii;
typedef pair<int,pii> pip;
#define f first
#define s second
#define mp make_pair

const int MAXX = 1e6 + 5;
const int INF  = 1e9;

int r, c, R, K, P;

void print_grid(vector< vector<LL> > W) {
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            printf("%d ",W[i][j]);
        }
        printf("\n");
    }
}

struct seg{
    int n;
    vector<pip> tree; // (value, (min_pos, max_pos));
    vector<LL> values;

    void merge(int now, int l, int r) {
        if (tree[l].f == tree[r].f) {
            tree[now] = mp(tree[l].f, mp(tree[l].s.f, tree[r].s.s));
        } else if (tree[l].f > tree[r].f) {
            tree[now] = tree[l];
        } else {
            tree[now] = tree[r];
        }
    }

    void init(vector<LL> INP) {
        n = INP.size();
        values = INP;
        tree.resize(4*n);
        build(1, 0, n - 1);
    }

    void build(int now, int l, int r) {
        if (l == r) {
            tree[now] = mp(values[l], mp(l, l));
            return;
        }
        int mid = (l + r) >> 1;
        build(now << 1, l, mid);
        build(now << 1 | 1, mid + 1, r);
        merge(now, now<<1, now<<1|1);
    }

    void update(int now, int l, int r, int pos) {
        if (l == r) {
            tree[now] = mp(tree[now].f-1, mp(l, l));
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) update(now << 1, l, mid, pos);
        else update(now << 1 | 1, mid + 1, r, pos);
        merge(now, now<<1, now<<1|1);
    }

    // mode = true  : search MAX
    // mode = false : search MIN

    int ride(int now, int l, int r, bool mode, int layer) {
        if (l == r) return l;
        int mid = (l + r) >> 1;
        if (mode == 0) {
            if (tree[now<<1].f >= layer) return ride(now<<1, l, mid, mode, layer);
            return ride(now<<1|1, mid+1, r, mode, layer);
        } else {
            if (tree[now<<1|1].f >= layer) return ride(now<<1|1, mid + 1, r, mode, layer);
            return ride(now<<1, l, mid, mode, layer);
        }
    }

    int query(int now, int l, int r, int a, int b, bool mode, int layer) {
        if (r < a || l > b) return mode ? -INF : INF;
        if (a <= l && r <= b) {
            if (tree[now].f >= layer) {
                return ride(now, l, r, mode, layer);
            } else {
                return mode ? -INF : INF;
            }
        }
        int mid = (l + r) >> 1;
        if (mode == 0) {
            int go_left = query(now << 1, l, mid, a, b, mode, layer);
            if (go_left != INF) return go_left;
            int go_righ = query(now << 1 | 1, mid + 1, r, a, b, mode, layer);
            return go_righ;
        } else {
            int go_righ = query(now << 1 | 1, mid + 1, r, a, b, mode, layer);
            if (go_righ != -INF) return go_righ;
            int go_left = query(now << 1, l, mid, a, b, mode, layer);
            return go_left;
        }
    }
    
};

seg Trow[MAXX];
seg Tcol[MAXX];

int main() {
    // freopen("c.in", "r", stdin);
    scanf("%d %d %d %d %d",&r, &c, &R, &K, &P);

    vector< vector<LL> > W;
    for(int i = 1; i <= r; i++) {
        vector<LL> C;
        for(int j = 1; j <= c; j++) {
            LL num;
            scanf("%lld",&num);
            C.push_back(num);
        }
        W.push_back(C);
    }

    for(int i = 0; i < c; i++) {
        vector<LL> tmp;
        for(int j = 0; j < r; j++) tmp.push_back(W[j][i]);
        Tcol[i].init(tmp);
    }
    for(int i = 0; i < r; i++) {
        Trow[i].init(W[i]);
    }
    
    while(K--) {
        char cmd[5];
        scanf("%s", cmd);
        int pos, layer;
        scanf("%d %d",&pos, &layer);
        pos--;

        if (cmd[0] == 'W' || cmd[0] == 'E') {
            if (cmd[0] == 'W') {
                int now = -1;
                for(int destroyed = 1; destroyed <= R; destroyed++) {
                    if (now == c-1) break;
                    int next = Trow[pos].query(1, 0, c-1, now+1, c-1, 0, layer);
                    if (next != INF) {
                        W[pos][next] -= 1;
                        Trow[pos].update(1, 0, c-1, next);
                        Tcol[next].update(1, 0, r-1, pos);
                        now = next;
                    }
                }
            } else {
                int now = c;
                for(int destroyed = 1; destroyed <= R; destroyed++) {
                    if (now == 0) break;
                    int next = Trow[pos].query(1, 0, c-1, 0, now-1, 1, layer);
                    if (next != -INF) {
                        W[pos][next] -= 1;
                        Trow[pos].update(1, 0, c-1, next);
                        Tcol[next].update(1, 0, r-1, pos);
                        now = next;
                    }
                }
            }
        } else {
            if (cmd[0] == 'N') {
                int now = -1;
                for(int destroyed = 1; destroyed <= R; destroyed++) {
                    if (now == r-1) break;
                    int next = Tcol[pos].query(1, 0, r-1, now+1, r-1, 0, layer);
                    if (next != INF) {
                        W[next][pos] -= 1;
                        Tcol[pos].update(1, 0, r-1, next);
                        Trow[next].update(1, 0, c-1, pos);
                        now = next;
                    }
                }   
            } else {
                int now = r;
                for(int destroyed = 1; destroyed <= R; destroyed++) {
                    if (now == 0) break;
                    int next = Tcol[pos].query(1, 0, r-1, 0, now-1, 1, layer);
                    if (next != -INF) {
                        W[next][pos] -= 1;
                        Tcol[pos].update(1, 0, r-1, next);
                        Trow[next].update(1, 0, c-1, pos);
                        now = next;
                    }
                }
            }
        }
        // print_grid(W);
    }

    LL maks = 0;
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            LL i_min_1 = (i == 0) ? 0 : W[i-1][j];
            LL j_min_1 = (j == 0) ? 0 : W[i][j-1];
            LL i_min_1_j_min_1 = (i > 0 && j > 0) ? W[i-1][j-1] : 0;
            W[i][j] += i_min_1 + j_min_1 - i_min_1_j_min_1;

            if (i-P+1 >= 0 && j-P+1 >= 0) {
                LL i_min_p = (i-P >= 0) ? W[i-P][j] : 0;
                LL j_min_p = (j-P >= 0) ? W[i][j-P] : 0;
                LL i_min_p_j_min_p = (i-P >= 0 && j-P >= 0) ? W[i-P][j-P] : 0;
                LL sum = W[i][j] - i_min_p - j_min_p + i_min_p_j_min_p;
                if (sum >= maks) maks = sum;
            }
        }
    }

    printf("%lld\n",maks);
    return 0;
}