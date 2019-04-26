#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define f first
#define s second
#define mp make_pair

int M;
pii f(pii L) { // first modulo, second hasil
    L.f *= 10;
	return mp(L.f % M, L.f / M);
}

pii floyd_cycle_finding(int x) {
	pii x0 = mp(x, 0);
    pii tortoise = f(x0), hare = f(f(x0));
    while( tortoise.first != hare.first ) {
        tortoise = f(tortoise);
        hare = f(f(hare));
    }

	
	// printf("%d %d\n",tortoise.first, hare.first);

	if (tortoise.first == 0) {
		tortoise = x0; printf(".");
		while(tortoise.first != 0) {
			tortoise = f(tortoise);
			printf("%d",tortoise.second);
		} printf("\n");
		printf("This expansion terminates.\n\n");
		return mp(0,0);
	}
	
	printf(".");
    int mu = 0;
    hare = tortoise;
    tortoise = x0;
    while( tortoise.first != hare.first ) {
        tortoise = f(tortoise);
		printf("%d",tortoise.second);
        hare = f(hare);
        ++mu;
    }
	
    int lambda = 1;
    hare = f(tortoise);
	printf("%d",hare.second);
    while( tortoise.first != hare.first ) {	
        hare = f(hare);
		printf("%d",hare.second);
        ++lambda;
    }

	// printf("\n%d %d\n",mu, lambda);
	
	printf("\n");
	printf("The last %d digits repeat forever.\n",lambda);
	printf("\n");
}

int main() {
	int a, b;
	while(scanf("%d %d",&a, &b) && (a + b > 0)) {
		M = b;
		floyd_cycle_finding(a);
	}
}