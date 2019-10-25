/**
 * Author: Lucian Bicsi
 * Date: 2015-06-25
 * License: GNU Free Documentation License 1.2
 * Source: csacademy
 * Description: Transform to a basis with fast convolutions of the form
 * $\displaystyle c[z] = \sum\nolimits_{z = x \oplus y} a[x] \cdot b[y]$,
 * where $\oplus$ is one of AND, OR, XOR. The size of $a$ must be a power of two.
 * Time: O(N \log N)
 * Status: tested
 * Usage: N should be in the form 1<<X
 */
#pragma once

template <typename T>
struct FWT {
	void fwt(vector<T>&io, int n,int t) {
		for (int d = 1; d < n; d <<= 1) {
			for (int i = 0, m = d<<1; i < n; i += m) {
				for (int j = 0; j < d; j++) { /// Don't forget modulo if required
					T x = io[i+j], y = io[i+j+d];
					if(t==0)io[i+j] = (x+y)%MOD, io[i+j+d] = (x+MOD-y)%MOD;	// xor
					else if(t==1)io[i+j] = (x+y)%MOD; // and
					else io[i+j+d] = (x+y)%MOD; // or
				}
			}
		}
	}
	void ufwt(vector<T>&io, int n,int t) {
		for (int d = 1; d < n; d <<= 1) {
			for (int i = 0, m = d<<1; i < n; i += m) {
				for (int j = 0; j < d; j++) { /// Don't forget modulo if required
					T x = io[i+j], y = io[i+j+d];
					 /// Modular inverse if required here
					if(t==0)io[i+j] = (x+y)*dua%MOD, io[i+j+d] = (x-y+MOD)*dua%MOD; // xor
					else if(t==1)io[i+j] = (x-y+MOD)%MOD; // and
					else io[i+j+d] = (y-x+MOD)%MOD; // or
				}
			}
		}
	}
	// a, b are two polynomials and n is size which is power of two
	void convolution(vector<T>&a, vector<T>&b, int n,int t) {
		fwt(a, n,t);
		fwt(b, n,t);
		for (int i = 0; i < n; i++)
			a[i] = a[i]*b[i]%MOD;
		ufwt(a, n,t);
	}
};