#include<bits/stdc++.h>
using namespace std;

#define LL long long
#define MAX 200000

#define MOD 10007

LL pow(LL base, LL expo, LL M) {
	LL res = 1;
	base %= M;
	while(expo > 0) {
		if (expo & 1) res = (res * base)%M;
		base = (base * base) % M;
		expo >>= 1;
	}
	return res;
}

inline LL inverse(LL a, LL M) {
	return pow(a, M-2, M);
}

LL fact[MAX], invfact[MAX];

void pre_fact(LL batas, LL M) {
	fact[0] = fact[1] = invfact[0] = invfact[1] = 1;
	for(LL i = 2; i <= batas; i++) {
		fact[i] = (i * fact[i - 1])%M;
		invfact[i] = inverse(fact[i], M);
	}
}

inline LL nCk(LL a, LL b, LL M) {
	if (b < 0 || a < b) return 0;
	LL ans = (fact[a] * invfact[a - b])%M;
	ans = (ans * invfact[b])%M;
	return ans;
}

inline LL lucas(LL a, LL b, LL M) {
	if (a == 0 && b == 0) return 1;
	LL n = a%M, k = b%M;
	if (n < k) return 0;
	return (nCk(n, k, M) * lucas(a/M, b/M, M)) % M;
}

LL g(LL x, LL y) {
	if (x <= 0 || y <= 0) return 0;
	if (x == 1 && y != 1) return 0;
	if (x != 1 && y == 1) return 0;
	if (x > y) swap(x, y);
	LL unggul = y - x;
	LL satu_titik = x - unggul;
	//printf("%lld\n",satu_titik);
	if (satu_titik % 3 != 1) return 0;
	if (satu_titik == 1) return 1;
	LL ke = (satu_titik + 2)/3;
	LL step_kurang = (ke - 1) * 2;
	//printf("%lld %lld\n",unggul + step_kurang, step_kurang);
	return lucas(unggul + step_kurang, step_kurang/2, MOD);
}

LL dP[200][200];
LL fa(LL x, LL y) {
	if (x < 1 || y < 1) return 0;
	if (x == 1 && y == 1) return 1;
	LL &ret = dP[x][y];
	if (ret >= 0) return ret;
	ret = 0;
	ret = fa(x - 2, y - 1) + fa(x - 1, y - 2);
	return ret;
}

typedef pair<LL,LL> pii;
#define f first
#define s second
#define mp make_pair

pii arr[15];
int dp[15];

int main() {
	pre_fact(MAX - 2, MOD);
	
	LL TC, W, H, R;
	scanf("%lld",&TC);
	for(int cs = 1; cs <= TC; cs++) {
		scanf("%lld %lld %lld",&H, &W, &R);
		for(int i = 1; i <= R; i++) {
			scanf("%lld %lld",&arr[i].f, &arr[i].s);
		}
		arr[++R] = mp(H, W);
		sort(arr + 1, arr + R + 1);
		
		for(int i = 1; i <= R; i++) {
			dp[i] = g(arr[i].f, arr[i].s);
			for(int j = 1; j <= R; j++) {
				if (arr[j].f < arr[i].f && arr[j].s < arr[i].s) {
					LL start_ke_halang = g(arr[j].f, arr[j].s);
					LL halang_ke_sekarang = g(arr[i].f - arr[j].f + 1, arr[i].s - arr[j].s + 1);
					LL banyak = (start_ke_halang * halang_ke_sekarang)%MOD;
					dp[i] = (dp[i] - banyak + MOD)%MOD;
				}
			}
		}
		printf("Case #%d: %lld\n",cs, dp[R] % MOD);
	}
	
	bool cek_brute = 0;
	if (cek_brute) {
		memset(dP, -1, sizeof(dP));
		while(true) {
			LL x, y;
			scanf("%lld %lld",&x, &y);
			printf("%lld\n",fa(x, y) % MOD);
			printf("mantap %lld\n",g(x, y));
		}
	}
}
