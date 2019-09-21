#include <bits/stdc++.h>
using namespace std;

#define LL long long
const LL limit = 1e12 + 5;

LL t, n, closest, a[7];

void upd(LL k) {if (abs(k - t) <= abs(t-closest)) closest = k;}

void rec(int elem) {
    if (closest == t || elem == 1) return;
    for(int i = 0; i < elem; i++) {
        LL prv = a[i];
        for(int j = i + 1; j < elem; j++) {
            swap(a[j], a[elem-1]);

            a[i] += a[elem-1];
            upd(a[i]);
            if (a[i] != 0) rec(elem - 1);
            a[i] = prv;

            a[i] -= a[elem-1];
            upd(a[i]);
            if (a[i] != 0) rec(elem - 1);
            a[i] = prv;

            
            if (a[elem-1] != 0) {
                a[i] /= a[elem-1];
                upd(a[i]);
                if (a[i] != 0) rec(elem - 1);
                a[i] = prv;
            }
            
            a[i] *= a[elem-1];
            if (a[i] > -limit && a[i] < limit) {
                upd(a[i]);
                if (a[i] != 0) rec(elem - 1);
            }
            a[i] = prv;

            swap(a[j], a[elem-1]);
        }
    }
}

int main(){
    while(1) {
        scanf("%lld %lld",&t, &n);
        if (n == 0) return 0;
        closest = limit;
        for(int i = 0; i < n; i++) {
            scanf("%lld",&a[i]);
            upd(a[i]);
        }
        rec(n);
        printf("%lld\n",closest);
    }
}