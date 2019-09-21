

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int VAL = 2e6 + 5;
const int LG = 21;

int tc;
int arr[VAL];
int v[N];
long long dp[VAL][LG];

int main() {
    scanf("%d",&tc);
    while(tc--) {
        int n;
        
        
        memset(arr, 0, sizeof arr);
        
        scanf("%d",&n);
        
        assert(n <= N);
        
        for(int i = 1; i <= n; i++) {
            int x;
            scanf("%d",&x);
            assert(x <= (1<<20));
            arr[x] += 1;
            v[i] = x;
        }
        
        for(int i = 0; i < (1<<20); i++) {
            dp[i][0] = arr[i];
            
            if (i & 1) {
                dp[i][0] += arr[i ^ 1];    
            }
            
            for(int j = 1; j < 20; j++) {
                dp[i][j] = dp[i][j-1];
                
                if (i & (1 << j)) {
                    dp[i][j] = dp[i][j] + dp[i ^ (1 << j)][j - 1];
                }
            }
        }
        
        long long ans = 0;
        for(int i = 1; i <= n; i++) {
            ans = ans + dp[(1<<20)-1-v[i]][19];
        }
        
        printf("%lld\n",ans);
    }
}
