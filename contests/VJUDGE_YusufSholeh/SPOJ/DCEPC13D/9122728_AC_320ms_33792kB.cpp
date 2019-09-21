#include<bits/stdc++.h>
using namespace std;

#define LL long long 
#define MAX 2000000
#define MOD 1000003

LL fact[MAX];
LL invfact[MAX];

int prime[15] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

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

LL result[20];
LL Mi[20];
LL yi[20];

int main() {
	int tc; scanf("%d",&tc);
	while(tc--) {
		LL n, k, m;
		scanf("%lld %lld %lld",&n, &k, &m);
		
		memset(result,-1,sizeof(result));
		LL ans = 0;
		for(int i = 0; i < 15; i++) {
			if (m % prime[i] == 0) {
				pre_fact(50, prime[i]);
				result[i] = lucas(n, k, prime[i]);
				Mi[i] = m / prime[i];
				yi[i] = inverse(Mi[i], prime[i]);
				LL kali = (Mi[i] * yi[i])%m;
				// printf("%lld %lld %lld\n",result[i], Mi[i], yi[i]);
				kali = (kali * result[i])%m;
				ans = (ans + kali)%m;
			}
		}
		
		printf("%lld\n",ans);
	}
}