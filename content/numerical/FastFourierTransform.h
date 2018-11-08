/**
 * Author: Simon Lindholm
 * Date: 2015-06-25
 * License: GNU Free Documentation License 1.2
 * Source: http://rosettacode.org/wiki/Fast_Fourier_transform
   Papers about accuracy: http://www.daemonology.net/papers/fft.pdf, http://www.cs.berkeley.edu/~fateman/papers/fftvsothers.pdf
   For integers rounding works if $(|a| + |b|)\max(a, b) < \mathtt{\sim} 10^9$, or in theory maybe $10^6$.
 * Description: Computes $\hat f(k) = \sum_x f(x) \exp(-2\pi i k x / N)$ for all $k$. Useful for convolution:
   \texttt{conv(a, b) = c}, where $c[x] = \sum a[i]b[x-i]$. $a$ and $b$ should be of roughly equal size.
   For convolutions of integers, consider using a number-theoretic transform instead, to avoid rounding issues.
	 This works safely when the cofficient result is under $10^{14}$.
 * Time: O(N \log N)
 * Status: somewhat tested
 */
#pragma once

const double PI = acos(-1);
typedef complex<double> base;
void fft (vector<base> & a, bool invert) {
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
		double ang = 2*PI/len * (invert ? -1 : 1);
		base wlen (cos(ang), sin(ang));
		for (int i=0; i<n; i+=len) {
			base w (1);
			for (int j=0; j<len/2; ++j) {
				base u = a[i+j],  v = a[i+j+len/2] * w;
				a[i+j] = u + v;
				a[i+j+len/2] = u - v;
				w *= wlen;
			}
		}
	}
	if (invert)
		for (int i=0; i<n; ++i)
			a[i] /= n;
}
void multiply (const vector<int> &a, const vector<int> &b, vector<int> &res){
	vector<base> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
	size_t n = 1;
	while (n < max (a.size(), b.size()))  n <<= 1;
	n <<= 1;
	fa.resize (n),  fb.resize (n);
	fft (fa, false),  fft (fb, false);
	for (size_t i=0; i<n; ++i)
		fa[i] *= fb[i];
	fft (fa, true);
	res.resize (n);
	for (size_t i=0; i<n; ++i)
		res[i] = int (fa[i].real() + 0.5); // <- beware if res[i] negative, floor function retard
}
