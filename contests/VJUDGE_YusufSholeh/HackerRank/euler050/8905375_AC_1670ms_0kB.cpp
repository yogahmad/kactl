#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define f first
#define s second
#define mp make_pair

const LL MAXN = 1000000000000;
const int MAXP = 10000000;

bool bol[MAXP];
LL prime[MAXP];
LL pref[MAXP];
LL consecutive[MAXP];
int top = 0;
int topPrefix = 0;

void generateSieve() {
	for(int i = 2; i < MAXP; i++) {
		if (bol[i] == false) {
			prime[++top] = i;
			for(int j = i+i; j < MAXP; j+=i) bol[j] = true;
		}
	}
}

/*
	MILLER RABIN
	check wether n is prime
	2^s * d = n-1
	
	random a from 2..n-1 , 
		x = a^d mod n
*/

vector<long long> A; // store prime from 2..23 (there are 9 prime)
// if n < 3,825,123,056,546,413,051 (3*10^18), it is enough to test a = 2, 3, 5, 7, 11, 13, 17, 19, and 23.
inline long long fastmul(long long a, long long b, long long n) {
    long long ret = 0;
    while (b) {
        if (b & 1) ret = (ret + a) % n;
        a = (a + a) % n;
        b >>= 1;
    }
    return ret;
}

inline long long fastexp(long long a, long long b, long long n) {//compute (a^b) mod n
    long long ret = 1;
    while (b) {
        if (b & 1) ret = fastmul(ret, a, n);
		a = fastmul(a, a, n);
        b >>= 1;
    }
    return ret;
}

inline bool millerTest(long long n, long long s, long long d, long long a) {
	long long ad = fastexp(a, d, n); //ad = a^d mod n
	if(ad == 1 || ad == n-1) return true;
	for(int r = 1; r <= s-1; r++) {
		ad = fastmul(ad, ad, n); // ad = ad^2 mod n
		if (ad == 1) return false;
		if (ad == n-1) return true;
	}
	return false;
}

inline bool isPrimeMillerRabin(long long n) {
	if(n == 2) return true;
    if(n == 1 || (n % 2 == 0)) return false;
    long long d = n-1;
    long long s = 0;
    while(d % 2 == 0) {
		s++;
		d /= 2;
    }
    for(int j = 0; j < A.size(); j++) {
		if (A[j] > n-1) break;
		if (millerTest(n, s, d, A[j]) == false) 
			return false;
    }
    return true;
}

void init() {
	generateSieve();
	for(int i = 1; i <= 9; i++) A.push_back(prime[i]);
	for(int i = 1; i <= top; i++) {
		pref[i] = pref[i-1] + prime[i];
		if (pref[i] >= MAXN) {
			topPrefix = i;
			break;
		}
	}
}

void solve(LL n) {
	int ub = upper_bound(pref + 1, pref + topPrefix + 1, n) - pref;
	ub--;
	
	for(int diff = ub; diff >= 1; diff--) {
		for(int i = 0; i+diff <= topPrefix; i++) {
			if (pref[i+diff] - pref[i] > n) continue;
			if (isPrimeMillerRabin(pref[i+diff] - pref[i])) {
				int ans = diff;
				LL anscons = pref[i+diff] - pref[i];
				printf("%lld %d\n",anscons, ans);
				return;
			}
		}
	}
	
}

void read() {
	int tc; scanf("%d",&tc);
	while (tc--) {
		LL n;
		scanf("%lld",&n);
		solve(n);
	}
}

int main() {
	init();
	read();
	return 0;
}