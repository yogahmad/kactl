#include<bits/stdc++.h>
using namespace std;

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
		res[i] = int (fa[i].real() + 0.5);
}


#define MAX 300005
char S[MAX];

#define MAXV 1200000
int result[MAXV];
int main() {
	int tc;
	scanf("%d",&tc);
	while(tc--) {
		vector<int> a, b, res;
		scanf("%s", S);
		int len = strlen(S);
		
		for(int i = len-1; i >= 0; i--) a.push_back(int(S[i]) - '0');
		
		scanf("%s", S);
		len = strlen(S);
		
		for(int i = len-1; i >= 0; i--) b.push_back(int(S[i]) - '0');
		
		multiply(a, b, res);
		
		len = res.size();
		int ptr = 0;
		for(int i = 0; i < len; i++) {
			int num = res[i];
			for(int j = ptr; num > 0; num/=10, j++) {
				result[j] = result[j] + (num % 10);
				if (result[j] >= 10) {
					result[j+1] += 1;
					result[j] = result[j] - 10;
				}
			}
			ptr++;
		}
		
		int bound = min(2 * len, MAXV);
		
		int top = 0;
		for(int i = bound; i >= 0; i--) {
			if (result[i] != 0) {
				top = i+1;
				break;
			}
		}
		
		if (top == 0) printf("0");
		for(int i = top-1; i >= 0; i--) {
			printf("%d",result[i]);
			result[i] = 0;
		} printf("\n");
	}
	return 0;
}