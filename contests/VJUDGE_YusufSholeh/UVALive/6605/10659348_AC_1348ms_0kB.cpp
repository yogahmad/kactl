#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAXW = 1005;
const int MOD = 10007;

int n, w, cnt;
int C[MAXN*3][MAXN*3];
int dp[MAXN][MAXN][MAXW];
int what[MAXN], how_many[MAXN];

void generatecombin() {
    for(int i = 0; i < MAXN*3; i++) {
        C[i][0] = 1;
        for(int j = 1; j <= i; j++) C[i][j] = (C[i-1][j] + C[i-1][j-1])%MOD;
    }
}

int f(int now, int k, int W) {
    if (W == 0) return 1;
    if (W < 0 || now > cnt) return 0;

    int &ret = dp[now][k][W];
    if (ret != -1) return ret;

    ret = 0;
    for(int i = 0; i <= how_many[now]; i++) {
        int next = f(now + 1, k + i, W - i * what[now]);
        ret = (ret + next * C[k + i][i])%MOD;
    }

    return ret;
}

int main() {
    generatecombin();

    int t; scanf("%d",&t);
    for(int cs = 1; cs <= t; cs++) {

        map<int,int> compress;
        scanf("%d %d",&n, &w);
        for(int i = 1; i <= n; i++) {
            int k; scanf("%d",&k);
            compress[k] += 1;
        }

        cnt = 0;
        for(pair<int,int> elem : compress) {
            what[++cnt] = elem.first;
            how_many[cnt] = elem.second;
        }

        // Memset DP
        for(int i = 0; i <= cnt + 1; i++) 
            for(int j = 0; j <= n; j++) 
                for(int k = 0; k <= w; k++) 
                    dp[i][j][k] = -1; 

        int ans = 0;
        int curw = w;
        int curk = 0;
        for(int i = 1; i <= cnt; i++) {
            for(int j = 0; j < how_many[i]; j++) {
                int how_many_prv = 1;
                int total_items  = curk + j;
                for(int k = 1; k < i; k++) {
                    how_many_prv = (how_many_prv * C[total_items][how_many[k]])%MOD;
                    total_items -= how_many[k];
                }
                
                int exact = 0;
                for(int rem = 0; rem < what[i]; rem++) {
                    int needed = (curw - j * what[i]) - rem;
                    if (needed >= 0) exact = (exact + f(i + 1, curk + j, needed))%MOD;
                }
                
                ans = (ans + how_many_prv * exact)%MOD;
            }
            curw -= what[i] * how_many[i];
            curk += how_many[i];
        }
        
        printf("Case %d: %d\n",cs, ans);
    }
}