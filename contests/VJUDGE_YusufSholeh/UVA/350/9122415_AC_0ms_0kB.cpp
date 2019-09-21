#include<bits/stdc++.h>
using namespace std;

int Z, I, M;
int f(int L) {
    return (( Z * L + I ) % M);
}

pair<int, int> floyd_cycle_finding(int x0) {
    int tortoise = f(x0), hare = f(f(x0));
    while( tortoise != hare ) {
        tortoise = f(tortoise);
        hare = f(f(hare));
    }

    int mu = 0;
    hare = tortoise;
    tortoise = x0;
    while( tortoise != hare ) {
        tortoise = f(tortoise);
        hare = f(hare);
        ++mu;
    }
	
    int lambda = 1;
    hare = f(tortoise);

    while( tortoise != hare ) {
        hare = f(hare);
        ++lambda;
    }

    return make_pair(mu, lambda);
}

int main() {
	int L, cs = 0;
	while(scanf("%d %d %d %d", &Z, &I, &M, &L)) {
        if(Z == 0 && I == 0 && M == 0 && L == 0) break;
        printf("Case %d: %d\n", ++cs, floyd_cycle_finding(L).second);
    }
	return 0;
}