#include <bits/stdc++.h>
using namespace std;

#define LL long long

const int MAX = 1e4 + 5;

int n;
int arr[MAX];

int main() {
    scanf("%d",&n);
    for(int i = 1; i <= n; i++) scanf("%d",&arr[i]);
    long long ans = 0;
    int ctr =0 ;
    while(true) {
        ctr += 1;
        for(int i = 1; i <= n; i++) {
            if (arr[i] < 0) {
                int nxt = i + 1;
                int prv = i - 1;
                if (nxt == n + 1) nxt = 1;
                if (prv == 0) prv = n;
                arr[i] = abs(arr[i]);
                arr[nxt] -= arr[i];
                arr[prv] -= arr[i];
                ans += 1;
            }
        }
        for(int i = 1; i <= n; i++) {
            if (arr[i] < 0) {
                goto next_while;
            }
        }

        break;
        next_while:;
    }

    printf("%lld\n",ans);
    return 0;
}   