#include<bits/stdc++.h>
using namespace std;

#define LL long long

LL A, B, C;

inline LL f(LL x) {
	return (A * x + x % B) % C;
}

int track = 1;

const int MAKS = 20000000;

pair<LL, LL> floyd_cycle_finding(LL x0) {
	LL tortoise = f(x0), hare = f(f(x0));
	while(tortoise != hare) {
		if (track >= MAKS) {
			return make_pair(-1,-1);
		}
		track += 2;
		tortoise = f(tortoise);
		hare = f(f(hare));
	}
	
	int mu = 0;
	hare = tortoise;
	tortoise = x0;
	while(tortoise != hare) {
		tortoise = f(tortoise);
		hare = f(hare);
		++mu;
	}
	
	int lambda = 1;
	hare = f(tortoise);
	
	while(tortoise != hare) {
		hare = f(hare);
		++lambda;
	}
	
	return make_pair(mu, lambda + mu);
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	scanf("%lld %lld %lld",&A, &B, &C);
	printf("%lld\n",floyd_cycle_finding(1).second);
}
