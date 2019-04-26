#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define f first
#define s second
#define mp make_pair

#define LL long long
const LL limit = 1e7 + 5;
const int MAX = 150;

LL t, n, closest, a[7];
int occ[limit+limit];
int day = 0;

void upd(LL k) {if (abs(k - t) <= abs(t-closest)) closest = k;}

vector<int> v[MAX];
int global_mask = 0;

inline void ins(int num) {
    if (num < -limit || num > limit) return;
    if (occ[num+limit] != day) {
        occ[num+limit] = day;
        if (num != 0) v[global_mask].push_back(num);
    }  
}

int main(){
    srand(time(NULL));
    while(1) {
        scanf("%lld %lld",&t, &n);
        if (n == 0) return 0;
        closest = limit;
        for(int i = 0; i < n; i++) {
            scanf("%lld",&a[i]);
            upd(a[i]);
            if (a[i] != 0) v[1<<i].push_back(a[i]);
        }

        for(int mask = 0; mask < (1 << n); mask++) {
            if (__builtin_popcount(mask) == 1) continue;
            global_mask = mask;
            for(int j = (mask - 1) & mask; j; j=(j-1)&mask) {
                int k = mask - j;
                day += 1;
                for(int n1 : v[j]) {
                    ins(n1);
                    for(int n2 : v[k]) {
                        ins(n2);
                        ins(n1 + n2);
                        ins(n1 - n2);
                        if (abs((LL)n1 * n2) < limit) ins(n1 * n2);
                        ins(n1 / n2);
                        ins(n2 / n1);
                    }
                }
                
                if (occ[t+limit] == day) {
                    closest = t;
                    goto next_tc;
                }
            }
        }

        if (true) {
            for(int numbers : v[(1<<n)-1]) upd(numbers);
        }


        next_tc:;
        printf("%lld\n",closest);
        for(int i = 0; i < MAX; i++) v[i].clear();
    }
}