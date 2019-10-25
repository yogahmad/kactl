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

namespace fft{
	typedef complex<double> base;
	void fft(vector<base> &a, bool inv){
		int n = a.size(), j = 0;
		vector<base> roots(n/2);
		for(int i=1; i<n; i++){
			int bit = (n >> 1);
			while(j >= bit){
				j -= bit;
				bit >>= 1;
			}
			j += bit;
			if(i < j) swap(a[i], a[j]);
		}
		double ang = 2 * acos(-1) / n * (inv ? -1 : 1);
		for(int i=0; i<n/2; i++){
			roots[i] = base(cos(ang * i), sin(ang * i));
		}
		for(int i=2; i<=n; i<<=1){
			int step = n / i;
			for(int j=0; j<n; j+=i){
				for(int k=0; k<i/2; k++){
					base u = a[j+k], v = a[j+k+i/2] * roots[step * k];
					a[j+k] = u+v;
					a[j+k+i/2] = u-v;
				}
			}
		}
		if(inv) for(int i=0; i<n; i++) a[i] /= n;
	}
 
	vector<lint> multiply(vector<lint> &v, vector<lint> &w){
		vector<base> fv(v.begin(), v.end()), fw(w.begin(), w.end());
		int n = 1;
		while(n < max(v.size(), w.size())) n <<= 1;
		n <<= 1;
		fv.resize(n);
		fw.resize(n);
		fft(fv, 0);
		fft(fw, 0);
		for(int i=0; i<n; i++) fv[i] *= fw[i];
		fft(fv, 1);
		vector<lint> ret(n);
		for(int i=0; i<n; i++) ret[i] = (lint)round(fv[i].real());
		return ret;
	}
	vector<lint> multiply(vector<lint> &v, vector<lint> &w, lint mod){
		int n = 1;
		while(n < max(v.size(), w.size())) n <<= 1;
		n <<= 1;
		vector<base> v1(n), v2(n);
		vector<base> r1(n), r2(n);
		for(int i=0; i<v.size(); i++){
			v1[i] = base(v[i] >> 15, v[i] & 32767);
		}
		for(int i=0; i<w.size(); i++){
			v2[i] = base(w[i] >> 15, w[i] & 32767);
		}
		fft(v1, 0);
		fft(v2, 0);
		for(int i=0; i<n; i++){
			int j = (i ? (n - i) : i);
			base ans1 = (v1[i] + conj(v1[j])) * base(0.5, 0);
			base ans2 = (v1[i] - conj(v1[j])) * base(0, -0.5);
			base ans3 = (v2[i] + conj(v2[j])) * base(0.5, 0);
			base ans4 = (v2[i] - conj(v2[j])) * base(0, -0.5);
			r1[i] = (ans1 * ans3) + (ans1 * ans4) * base(0, 1);
			r2[i] = (ans2 * ans3) + (ans2 * ans4) * base(0, 1);
		}
		fft(r1, 1);
		fft(r2, 1);
		vector<lint> ret(n);
		for(int i=0; i<n; i++){
			lint av = (lint)round(r1[i].real());
			lint bv = (lint)round(r1[i].imag()) + (lint)round(r2[i].real());
			lint cv = (lint)round(r2[i].imag());
			av %= mod, bv %= mod, cv %= mod;
			ret[i] = (av << 30) + (bv << 15) + cv;
			ret[i] %= mod;
			ret[i] += mod;
			ret[i] %= mod;
		}
		return ret;
	}
}