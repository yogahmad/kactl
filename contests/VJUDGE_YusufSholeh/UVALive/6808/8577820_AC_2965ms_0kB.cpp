#include<bits/stdc++.h>
using namespace std;

#define MAX 505
#define FFTMAX 1200000
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

void multiply (const vector<int> & a, const vector<int> & b, vector<int> & res) {
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
		res[i] = int (fa[i].real() + 0.5);
}

int r, c;

char S[MAX][MAX];
char Q[MAX][MAX];

void print(const vector<int> &a) {
	cout << "size: " << a.size() << endl;
	for(int i = 0; i < a.size(); i++) cout << a[i] << " "; cout << endl;
}

int main() {
	scanf("%d %d",&r, &c);
	for(int i = 0; i < r; i++) scanf("%s",S[i]);
	
	vector<int> aL, aG;
	
	for(int i = 0; i < r; i++) {
		for(int j = 0; j < c; j++) {
			if (S[i][j] == 'L') {
				aL.push_back(1);
				aG.push_back(0);
			} else {
				aL.push_back(0);
				aG.push_back(1);
			}
		}
	}
	
	int q; scanf("%d",&q);
	for(int cs = 1; cs <= q; cs++) {
		int a, b;
		scanf("%d %d",&a, &b);
		for(int i = 0; i < a; i++) scanf("%s",Q[i]);
		
		vector<int> mL, mG;
		for(int i = 0; i < r; i++) {
			for(int j = 0; j < c; j++) {
				if (i >= a || j >= b) {
					mL.push_back(0);
					mG.push_back(0);
				} else {
					if (Q[i][j] == 'L') {
						mL.push_back(1);
						mG.push_back(0);
					} else if (Q[i][j] == 'G') {
						mL.push_back(0);
						mG.push_back(1);
					} else {
						cout << "ASU " << i << " " << j << " " << Q[i][j] << endl;
					}
				}
			}
		}
		
		reverse(mL.begin(), mL.end());
		reverse(mG.begin(), mG.end());
		
		// printf("%d %d %d\n",r,c,r*c);
		// print(mL); 
		// print(mG);
		vector<int> resL, resG;
		vector<int> tmpL = aL;
		vector<int> tmpG = aG;
		multiply(tmpL, mL, resL);
		multiply(tmpG, mG, resG);
		
		int index = r*c-2;
		int best = 0;
		int x = 0, y = 0, tL = 0, tG = 0;
		for(int i = 0; i < r; i++) {
			for(int j = 0; j < c; j++) {
				index++;
				if (r - i < a || c - j < b) continue;
				// cout << i << " " << j << " " << resL[index] << " " << resG[index] << endl;
				int total = resL[index] + resG[index];
				if (total > best) {
					best = total;
					x = i; y = j;
					tL = resL[index];
					tG = resG[index];
				}
			}
		}
		
		printf("Case #%d: %d %d %d %d\n",cs,x+1,y+1,tG,tL);
	}
	return 0;
}	