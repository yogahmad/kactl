/**
* Author: Simon Lindholm
* Date: 2016-09-10
* License: CC0
* Source: based on KACTL's FFT
* Description: Can be used for convolutions modulo specific nice primes
* of the form $2^a b+1$, where the convolution result has size at most $2^a$.
* For other primes/integers, use two different primes and combine with CRT.
* May return negative values.
* Time: O(N \log N)
* Status: Somewhat tested
*/
#pragma once

// just check if g^((p-1)/r) % p != 1 for every possible r (r = prime factor of p-1) 
// instead of find g such that g^1, g^2, g^3, ... g^p-1 are the permutation of {1, 2, 3, ..., p-1}.
bool check_generator_version_langrage(ll g) { 
	for(int i = 1; i <= top; i++) {
		ll value = power(g, (p-1) / prime_factors[i]);
		if (value == 1) return false;
	}
	return true;
}
/** FFT Modular Arithmetic **/
const int mod = 7340033; // c * 2^k + 1 
const ll root = 5; // root = g ^ c % mod 
const ll root_1 = 4404020; // root_l = (root)^-1 % mod
const ll root_pw = 1<<20; // root_pw = (1 << k)
int rev[7340033];
ll getmod(ll a, ll tmod) {return ((a%tmod)+tmod)%tmod;}
void fft (vector<ll> & a, bool invert) {
	int n = (int) a.size();
	for (int i=1, j=0; i<n; ++i) {
		int bit = n >> 1;
		for (; j>=bit; bit>>=1)
			j -= bit;
		j += bit;
		if (i < j)
			swap (a[i], a[j]);
	}
	for (int len=2; len<=n; len<<=1) {
		ll wlen = invert ? root_1 : root;
		for (int i=len; i<root_pw; i<<=1)
			wlen = ll (wlen * 1ll * wlen % mod);
		for (int i=0; i<n; i+=len) {
			ll w = 1;
			for (int j=0; j<len/2; ++j) {
				ll u = a[i+j],  v = ll (a[i+j+len/2] * 1ll * w % mod);
				a[i+j] = getmod(u+v,mod);
				a[i+j+len/2] = getmod(u-v,mod);
				w = ll (w * 1ll * wlen % mod);
			}
		}
	}
	if (invert) {
		for (int i=0; i<n; ++i)
			a[i] = int (a[i] * 1ll * rev[n] % mod);
	}
}
void precalc(){ // calculate inverse of MOD in O(MOD)
	rev[1] = 1;
	for (int i=2; i<mod; i++)
		rev[i] = (mod - (mod/i) * rev[mod%i] % mod) % mod;
}
void multiply (const vector<ll> & a, const vector<ll> & b, vector<ll> & res) {
	vector <ll> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
	size_t n = 1;
	while (n < max (a.size(), b.size()))  n <<= 1;
	n <<= 1;
	fa.resize (n),  fb.resize (n);
	fft (fa, false),  fft (fb, false);
	forn(i,n)
		fa[i] *= fb[i];
	fft (fa, true);
	res.resize (n);
	forn(i,n) // for(i=0;i<n;)
		res[i] = fa[i] % mod;
}
