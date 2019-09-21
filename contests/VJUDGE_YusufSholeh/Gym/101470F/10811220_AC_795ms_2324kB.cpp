#include <bits/stdc++.h>
using namespace std;

const int MAX = 6e4 + 5;
const int SQ = 250;

typedef pair<int,int> pii;
#define f first
#define s second
#define mp make_pair

int tc;
int n, k;
int arr[MAX], tmp[MAX];

pii a[SQ+5][SQ+5];
int sb[MAX], eb[MAX], no_bracket[MAX], sz[MAX], cnt;
int lazy[MAX];

void propagate(int now) {
    if (lazy[now] == 0) return;
    for(int i = 1; i <= sz[now]; i++) {
        a[now][i].f += lazy[now];
    }
    lazy[now] = 0;
}

void update(int now, int p, int q) {
    for(int i = 1; i <= sz[now]; i++) {
        int id = a[now][i].s;
        if (p <= id && id <= q) {
            a[now][i].f += 1;
        }
    }
    sort(a[now] + 1, a[now] + sz[now] + 1);
}

int main() {
    freopen("f.in", "r", stdin);
    while(scanf("%d %d",&n, &k) != EOF) {
        for(int i = 1; i <= n; i++) {
            scanf("%d",&arr[i]);
            tmp[i] = arr[i];
        }

        cnt = 0;
        for(int i = 1; i <= n; i++) {
            if (i % SQ == 1) {
                eb[cnt] = i-1;
                cnt++;
                sb[cnt] = i;
            }
            no_bracket[i] = cnt;
        } eb[cnt] = n;

        for(int i = 1; i <= cnt; i++) {
            int ptr = 0;
            for(int j = sb[i]; j <= eb[i]; j++) {
                ++ptr;
                a[i][ptr] = mp(arr[j], j);
            }
            sz[i] = ptr;
            sort(a[i] + 1, a[i] + sz[i] + 1);
        }

        sort(tmp + 1, tmp + n + 1);
        int med = tmp[(n+1)/2];

        while(k--) {
            int p, q;
            scanf("%d %d",&p, &q);

            int bra_p = no_bracket[p];
            int bra_q = no_bracket[q];
            
            if (bra_p == bra_q) {
                propagate(bra_p);
                update(bra_p, p, q);
            } else {
                propagate(bra_p); 
                propagate(bra_q);
                update(bra_p, p, eb[bra_p]);
                update(bra_q, sb[bra_q], q);
                for(int i = bra_p + 1; i <= bra_q - 1; i++) {
                    lazy[i] += 1;
                }
            }


            int kecil = 0, sama = 0;
            for(int i = 1; i <= cnt; i++) {
                // printf("ISI BRACKET %d %d\n",i, sz[i]);
                // for(int j = 1; j <= sz[i]; j++) printf("%d ",a[i][j].f + lazy[i]); printf("\n");
                int l = 1, r = sz[i];
                int low = 0, same = 0;
                while(l <= r) {
                    int mid = (l + r) >> 1;
                    if (a[i][mid].f + lazy[i] < med) {
                        l = mid + 1;
                        low = mid;
                    } else {
                        r = mid - 1;
                    }
                }
                l = 1, r = sz[i];
                while(l <= r) {
                    int mid = (l + r) >> 1;
                    if (a[i][mid].f + lazy[i] <= med) {
                        l = mid + 1;
                        same = mid;
                    } else {
                        r = mid - 1;
                    }
                }
                // printf("LOW %d SAME %d\n",low, same);
                if (low != 0) kecil += low;
                if (same != 0) sama += same - low;
            }

            // printf("KECIL, SAMA : %d %d\n",kecil, sama);

            if (kecil <= n/2 && kecil + sama > n/2) {
                med += 0;
            } else {
                med += 1;
            }

            printf("%d\n",med);
        }


        for(int i = 1; i <= n; i++) {
            sb[i] = eb[i] = lazy[i] = sz[i] = no_bracket[i] = 0;
        }
    }
}