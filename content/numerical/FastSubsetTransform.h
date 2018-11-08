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
 */
#pragma once

void FWHT(vi &P,int bits ,bool inverse = false) { //FWHT xor on vector P
	int x = 1<<bits ,u,v;
    for (int len = 1; 2 * len <= x ; len <<= 1)
        for (int i = 0; i < x; i += 2 * len)
            for (int j = 0; j < len; j++){
                u = P[i + j] ;
                v = P[i + len + j] ;
                P[i + j] = (u + v)%mod ;
                P[i + len + j] = (u - v + mod)%mod ;
            }
    if (inverse){
	int xinv = pmod(x,mod-2) ;
	for (int i = 0; i < x ; i++) P[i] = ((ll)P[i]*(ll)xinv)%mod ;
     }
}
FWHT(P,16); 
	FN(i,1<<16) P[i] = pmod(P[i],N) ; //pmod(x,y)=x^y
FWHT(P,16,true);
void to_transform(ll dim, ll *data) { // and transform
    ll len, i, j, u, v;
    for (len = 1; 2 * len <= dim; len <<= 1) {
        for (i = 0; i < dim; i += 2 * len) {
            for (j = 0; j < len; j++) {
                u = data[i + j];
                v = data[i + len + j];
                data[i + j] = v;
                data[i + len + j] = (u + v);
                moddo(data[i + len + j]);
            }
        }
    }
}
void inv_transform(ll dim, ll *data) {
    ll len, i, j, u, v;
    for (len = 1; 2 * len <= dim; len <<= 1) {
        for (i = 0; i < dim; i += 2 * len) {
            for (j = 0; j < len; j++) {
                u = data[i + j];
                v = data[i + len + j];
                data[i + j] = mod - u + v;
                data[i + len + j] = u;
                moddo(data[i + j]);
            }
        }
    }
}
And matrices : {0 1; 1 1;} Or matrices : {1 1; 1 0}  
inv And : {-1 1; 1 0}  inv Or : {0 1; 1 -1}
                                      
