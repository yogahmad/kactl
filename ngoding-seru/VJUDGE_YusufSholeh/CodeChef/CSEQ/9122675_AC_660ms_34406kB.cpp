#include<bits/stdc++.h>
using namespace std;

#define LL long long 
#define MAX 2000000
#define MOD 1000003

LL fact[MAX];
LL invfact[MAX];

LL pow(LL base, LL expo, LL M) {
	LL res = 1;
	base %= M;
	while(expo > 0) {
		if( expo & 1) res = (res * base)%M;
		base = (base * base)%M;
		expo >>= 1;
	}
	return res;
}

inline LL inverse(LL a, LL M) {
	return (pow(a, M-2, M));
}

void pre_fact(LL batas, LL M) {
	fact[0] = fact[1] = invfact[0] = invfact[1] = 1;
	for(LL i = 2; i <= batas; i++) {
		fact[i] = (i * fact[i - 1])%M;
		invfact[i] = inverse(fact[i], M);
	}
}


inline LL nCk(LL a, LL b, LL M) {
	if(b < 0|| a < b) return 0;
	LL ans = (fact[a] * invfact[a-b])%M;
	ans = (ans * invfact[b])%M;
	return ans;
}

inline LL lucas(LL a, LL b, LL M) {
	if (a == 0 && b == 0) return 1;
	LL n = a%M, k = b%M;
	if(n < k) return 0;
	return (nCk(n, k, M) * lucas(a/M, b/M, M));
}

int main() {
	pre_fact(MAX-1, MOD);
	int tc; scanf("%d",&tc);
	while(tc--) {
		LL n, r, l;
		scanf("%lld %lld %lld",&n, &l, &r);
		printf("%lld\n",(lucas(n + r - l + 1, n, MOD) - 1 + MOD)%MOD);
	}
}