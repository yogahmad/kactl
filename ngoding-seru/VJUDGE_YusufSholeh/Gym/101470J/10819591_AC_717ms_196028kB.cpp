#include <bits/stdc++.h>
using namespace std;

const int TEST_MAX = 105;

int n, m;
int mat[TEST_MAX][TEST_MAX];
long long ans = 0;

// 0 - 3 (0:SW, 1:SE, 2:NE, 3:NW)
// 0 : Kiri bawah
// 1 : kanan bawah
// 2 : kanan atas
// 3 : kiri atas

void print_mat() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
}

void getDraw(int posx, int posy, int powerx, int powery, int t, int &c1, int &c2) {
    if (t == 0 || t == 3) { // left
        c1 = max(0, posy - powery + 1);
        c2 = posy;
    } else { // right
        c1 = posy;
        c2 = min(n-1,posy + powery - 1);
    }
}

int totnode = 0;
struct node {
    // tree component
    int l, r;               // this node cover range from l to r (column cover)
    bool nyala, lazy;       // nyala = from (l, r) the point is up. lazy = lazy this node
    int ple, pri;           // -> pointer to left & right node seg (0 means termimnal, doesnt have child)

    int NEW(int L, int R) {
        ple = 0, pri = 0, nyala = 0, lazy = 0; // NEW NODE MUST FRESH
        l = L, r = R; //CREATE NEW COMPONENT
        return totnode;
    }
} tree[10000000];


void propagate(int cur) {
    int l = tree[cur].l, r = tree[cur].r;
    int mid = (l + r) >> 1;
    if (l != r) {
        // printf("propagate %d %d\n",l, r);
        if (tree[cur].ple == 0) tree[cur].ple = tree[++totnode].NEW(l, mid); 
        if (tree[cur].pri == 0) tree[cur].pri = tree[++totnode].NEW(mid+1, r);
        tree[tree[cur].ple].lazy ^= tree[cur].lazy;
        tree[tree[cur].pri].lazy ^= tree[cur].lazy;
        tree[cur].lazy = 0;
    }
}    

void update(int cur, int a, int b) {
    if(tree[cur].lazy == 1) propagate(cur);
    int l = tree[cur].l, r = tree[cur].r;
    if (a > r || b < l) return;
    // printf("UPDATE %d %d\n",l, r);
    if (a <= l && r <= b) {
        tree[cur].lazy ^= 1;
        propagate(cur);
        return;
    }
    int mid = (l + r) >> 1;
    if (tree[cur].ple == 0) tree[cur].ple = tree[++totnode].NEW(l, mid); 
    if (tree[cur].pri == 0) tree[cur].pri = tree[++totnode].NEW(mid+1, r);
    update(tree[cur].ple, a, b);
    update(tree[cur].pri, a, b);
} 

void traverse(int cur, bool bawa, int l, int r) {
    // printf("%d %d %d\n",bawa, l, r);
    int mid = (l + r) >> 1;
    if (l == r) {
        bawa ^= tree[cur].lazy;
        // printf("WKASIOK BAWA %d\n");
        if (bawa) ans += (r - l + 1);
        return;
    }
    if (cur == 0) {
        // printf("WKAOK\n");
        if (bawa) ans += (r - l + 1);
        return;
    }
    traverse(tree[cur].ple, bawa ^ tree[cur].lazy, l, mid);
    traverse(tree[cur].pri, bawa ^ tree[cur].lazy, mid+1,r);
}

const int MAXN = 3e4 + 5;

int ROOT[MAXN];

int main() {
    freopen("j.in","r",stdin);
    scanf("%d",&n);

    for(int i = 0; i < n; i++) ROOT[i] = tree[++totnode].NEW(0, n-1);

    scanf("%d",&m);
    while(m--) {
        int a, b, p, t;
        scanf("%d %d %d %d",&a, &b, &p, &t);

        if (t == 0) {
            b -= 1;
        } else if (t == 1 ) {
            // tetep
        } else if (t == 2 ) {
            a -= 1;
        } else if (t == 3 ) {
            a -= 1; b -= 1;
        }

        int dx, dy, pos = a;
        if (t >= 2) {
            dx = -1;   
        } else {
            dx = +1;
        }

        for(int x = a, powx = 1, powy = p; /**/ powx <= p; /**/ x += dx, powx += 1, powy -= 1) {
            if (x == -1 || x == n) break;

            int c1, c2;
            getDraw(x, b, powx, powy, t, c1, c2);               
            
            // printf("powx, powy : %d %d\n",powx, powy);
            // printf("%d %d %d\n",x, c1, c2);
            // for(int i = c1; i <= c2; i++) { mat[x][i] += 1; }
            update(ROOT[x], c1, c2);
            // print_mat();
        }

        // printf("FINAL MAT : \n");
        // print_mat();
    }

    for(int i = 0; i < n; i++) traverse(ROOT[i], 0, 0, n-1);

    printf("%lld\n",ans);
    return 0;
}