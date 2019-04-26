#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define f first
#define s second
#define mp make_pair

#define LL long long
const LL limit = 1e8 + 5;

LL t, n, closest, a[7];

void upd(LL k) {if (abs(k - t) <= abs(t-closest)) closest = k;}

map<LL, int> maps[1<<8+2];

int main(){
    srand(time(NULL));
    while(1) {
        scanf("%lld %lld",&t, &n);
        if (n == 0) return 0;
        closest = limit;
        for(int i = 0; i < n; i++) {
            scanf("%lld",&a[i]);
            upd(a[i]);
            maps[1<<i][a[i]] += 1;
        }

        for(int mask = 0; mask < (1 << n); mask++) {
            if (__builtin_popcount(mask) == 1) continue;
            for(int j = (mask - 1) & mask; j; j=(j-1)&mask) {
                int k = mask - j;

                // printf("%d %d\n",maps[j].size(), maps[k].size());
                for(pii numbers : maps[j]) {
                    for(pii numbers2 : maps[k]) {
                        maps[mask][numbers.f + numbers2.f] = 1;
                        maps[mask][numbers.f - numbers2.f] = 1;
                        maps[mask][numbers2.f - numbers.f] = 1;
                        if ((LL)numbers.f * numbers2.f < limit) maps[mask][numbers.f * numbers2.f] = 1;
                        if (numbers2.f != 0) maps[mask][numbers.f / numbers2.f] = 1;
                        if (numbers.f  != 0) maps[mask][numbers2.f / numbers.f] = 1;
                    }
                }

                if (maps[mask].count(t)) {
                    closest = t;
                    goto next_tc;
                }
            }
        }

        if (true) {
            map<LL,int>::iterator it = maps[(1<<n)-1].lower_bound(t);
            if (it != maps[(1<<n)-1].end()) upd(it->first);
            if (it != maps[(1<<n)-1].begin()) it--, upd(it->first);
        }


        next_tc:;
        printf("%lld\n",closest);
        for(int i = 0; i < (1<<8); i++) maps[i].clear();
    }
}