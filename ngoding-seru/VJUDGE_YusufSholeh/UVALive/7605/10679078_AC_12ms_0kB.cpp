#include <bits/stdc++.h>
using namespace std;

#define LL long long

typedef pair<LL, LL> pii;
#define f first
#define s second
#define mp make_pair

const int MAX = 1e5 + 5;

LL n, x1[MAX], x2[MAX], h[MAX];

vector<pii> tree[MAX*4][2];

// 0 == buat garis dx > 0 (dari kiri ke kanan) 
// ((-dy)(x[i]) + (dx)(y[i]) + (dy)a - (dx)b) / sqrt(dx^2 + dy^2)
LL calc(LL dx, LL dy, LL a, LL b, LL xi, LL yi) { return -dy * xi + dx * yi + dy*a - dx*b; }
LL cross(pii p, pii q, pii r) { return((p.f - q.f)*(r.s - q.s) - (p.s - q.s)*(r.f - q.f)); }

void upper_hull(vector<pii> &v) {
    vector<pii> res;
    int n = v.size();

	for(int i = 0; i < n; i++) {
        while ((res.size() >= 2) && (cross(res[res.size() - 2], res[res.size() - 1], v[i]) <= 0)) 
            res.pop_back();
		res.push_back(v[i]);
    }
    
	v = res;
}

void build(int now, int l, int r) {
    for(int i = l; i <= r; i++) {
        tree[now][0].push_back(mp(x2[i], h[i]));
        tree[now][1].push_back(mp(x1[i], h[i]));
    }
    upper_hull(tree[now][0]);
    upper_hull(tree[now][1]);

    /*
    printf("segment %d sampai %d :\n",l, r);
    for(int i = 0; i < tree[now][0].size(); i++) printf("%d %d\n",tree[now][0][i].f, tree[now][0][i].s);
    printf("tree next\n");
    for(int i = 0; i < tree[now][1].size(); i++) printf("%d %d\n",tree[now][1][i].f, tree[now][1][i].s);
    */

    if (l == r) return;
    int mid = (l + r) >> 1;
    build(now << 1, l, mid);
    build(now << 1 | 1, mid + 1, r);
}

bool ada(int Type, int now, int l, int r, LL a, LL b, LL dx, LL dy) {
    int get = 0;
    int le = 0, ri = tree[now][Type].size()-1;
    LL ans = -1;
    while(le <= ri) {
        pii ki = tree[now][Type][le + (ri - le)/3];
        pii ka = tree[now][Type][ri - (ri - le)/3];
        LL fki = calc(dx, dy, a, b, ki.f, ki.s);
        LL fka = calc(dx, dy, a, b, ka.f, ka.s);
        if (Type == 0) {
            if (fki >= 0 || fka >= 0) return true;
            if (fki < fka) le = le + (ri - le)/3 + 1;
            else ri = ri - (ri - le)/3 - 1;
        } else {
            if (fki <= 0 || fka <= 0) return true;
            if (fki > fka) le = le + (ri - le)/3 + 1;
            else ri = ri - (ri - le)/3 - 1;
        }
    }
    return false;
}

int go(int Type, int now, int l, int r, LL a, LL b, LL dx, LL dy) {
    // printf("Type %d masuk ke %d %d\n",Type, l, r);    
    if (l == r) {
        if (Type == 0) {
            if ( cross(mp(a, b), mp(a + dx, b + dy), mp(x1[l], 0)) >= 0 ) return l+1;
            return 0;
        } else {
            if ( cross(mp(a, b), mp(a + dx, b + dy), mp(x2[l], 0)) <= 0 ) return l+1;
            return 0;
        }
        return 0;
    } 
    int mid = (l + r) >> 1;

    if (Type == 0) {
        if (ada(Type, now<<1, l, mid, a, b, dx, dy)) return go(Type, now << 1, l, mid, a, b, dx, dy);
        return go(Type, now << 1 | 1, mid + 1, r, a, b, dx, dy);
    } else {
        if (ada(Type, now<<1|1, mid + 1, r, a, b, dx, dy)) return go(Type, now << 1 | 1, mid + 1, r, a, b, dx, dy);
        return go(Type, now << 1, l, mid, a, b, dx, dy);
    }
}

int main() {
    while(scanf("%lld",&n) != EOF) {
        for(int i = 0; i < n; i++) scanf("%lld %lld %lld",&x1[i], &x2[i], &h[i]);
        for(int i = 0; i <= 4*n; i++) tree[i][0].clear(), tree[i][1].clear();
        build(1, 0, n-1);
        int q; scanf("%d",&q);
        while(q--) {
            LL a, b, dx, dy; 
            scanf("%lld %lld %lld %lld",&a, &b, &dx, &dy);
            if (dx == 0) {
                int ans = -1;
                int l = 0, r = n-1;
                while(l <= r) {
                    int mid = (l + r) >> 1;
                    if (x2[mid] <= a) {
                        ans = mid;
                        l = mid + 1;
                    } else r = mid - 1;
                }
                if (ans == -1) {
                    if (x1[0] <= a && a <= x2[0]) printf("1\n");
                    else printf("0\n");
                } else if (ans == n-1) {
                    if (x2[ans] < a) printf("0\n");
                    else printf("%d\n",n);
                } else {
                    if (x2[ans] == a) printf("%d\n",ans+1);
                    else {
                        if (x1[ans+1] > a) printf("0\n");
                        else printf("%d\n",ans+2);
                    }
                }
            } else {
                int Type = (dx > 0) ? 0 : 1;
                bool awal = ada(Type, 1, 0, n-1, a, b, dx, dy);
                if (awal == false) {
                    printf("0\n");
                    continue;
                }
                // printf("ASD\n");    
                // note that disini masih bisa 0
                printf("%d\n",go(Type, 1, 0, n-1, a, b, dx, dy));
            }   
        }
    }
}


