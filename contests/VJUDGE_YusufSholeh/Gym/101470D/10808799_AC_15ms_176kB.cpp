#include <bits/stdc++.h>
using namespace std;

bool go(int x, int y, int p) {
    int sisa = x;

    if (sisa % p == 0) sisa = y - 1;
    else if (sisa % p == 1) sisa = y;
    else return false;

    if (sisa % p == 0) sisa = x - 1;
    else if (sisa % p == 1) sisa = x;
    else return false;

    if (sisa % p == 0) sisa = y - 2;
    else if (sisa % p == 1) sisa = y - 1;
    else return false;

    if (sisa % p == 0) return true;
    return false;
}

int main() {
    freopen("d.in", "r", stdin);
    int x, y;
    scanf("%d %d",&x, &y);
    int q;
    scanf("%d",&q);
    while(q--) {
        int p;
        scanf("%d",&p);
        if (go(x, y, p) || go(y, x, p)) printf("YES\n");
        else printf("NO\n");
    }
}