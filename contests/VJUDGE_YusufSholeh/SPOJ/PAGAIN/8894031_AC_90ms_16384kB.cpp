#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define f first
#define s second
#define mp make_pair

vector<LL> A; // store prime from 2..23 (there are 9 prime)
// if n < 3,825,123,056,546,413,051 (3*10^18), it is enough to test a = 2, 3, 5, 7, 11, 13, 17, 19, and 23.
inline LL fastmul(LL a, LL b, LL n) {
    unsigned long long A = a;
	unsigned long long B = b;
	unsigned long long C = n;
	A *= B;
    return (A % C);
}

inline LL fastexp(LL a, LL b, LL n) {//compute (a^b) mod n
    LL ret = 1;
    while (b) {
        if (b & 1) ret = fastmul(ret, a, n);
		a = fastmul(a, a, n);
        b >>= 1;
    }
    return ret;
}

bool miller_test(LL n, LL s, LL d, LL a) {
	LL as = fastexp(a, s, n); //as = a^s mod n
	if(as == 1 || as == n-1) return true;
	for(int r = 1; r <= d-1; r++) {
		as = fastmul(as, as, n); // as = as^2 mod n
		if (as == 1) return false;
		if (as == n-1) return true;
	}
	return false;
}

inline bool is_prime(LL n) {
	if(n == 2) return true;
    if(n == 1 || (n % 2 == 0) || (n % 3 == 0)) return false;
    LL s = n-1, d = 0;
    while(s % 2 == 0) {
		d++, s /= 2;
    }
    for(int j = 0; j < A.size(); j++) {
		if (A[j] >= n) break;
		if (!miller_test(n, s, d, A[j])) 
			return false;
    }
    return true;
}

void init() {
	A.push_back(2);
	A.push_back(3);
	A.push_back(5);
	A.push_back(7);
	A.push_back(11);
	A.push_back(13);
}

void read() {
	int tc; scanf("%d",&tc);
	while (tc--) {
		LL n;
		scanf("%lld",&n);

		for (LL i = n-1; i >= 0; i--) {
			if (is_prime(i)) {
				printf("%lld\n", i);
				break;
			}
		}
	}
}

int main() {
	init();
	read();
	return 0;
}