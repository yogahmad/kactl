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
int MOD;
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
	for (size_t i=0; i<n; ++i) {
		long long tmp = (long long)(fa[i].real() + 0.5);
		res[i] = tmp % MOD;
	}
}

#define MAXN 8005
int n;
int a[MAXN], b[MAXN];
int dp[MAXN][128];
int ans[MAXN];
int dp2[MAXN][128];

void process(int l, int r) {
	int mid = (l + r) >> 1;

	
	vector<int> Lxor[128], Rxor[128];
	for(int i = 0; i < 128; i++) {
		if (i == a[mid] || i == b[mid]) {
			if (a[mid] == b[mid]) Lxor[i].push_back(2);
			else Lxor[i].push_back(1);
		} else {
			Lxor[i].push_back(0);
		}
		if (i == a[mid+1] || i == b[mid+1]) {
			if (a[mid+1] == b[mid+1]) Rxor[i].push_back(2);
			else Rxor[i].push_back(1);
		} else {
			Rxor[i].push_back(0);
		}
		dp[mid][i] = 0;
		dp2[mid+1][i] = 0;
	}
	dp[mid][a[mid]] = 1;
	dp[mid][b[mid]] += 1;
	dp2[mid+1][a[mid+1]] = 1;
	dp2[mid+1][b[mid+1]] += 1;
	for(int i = mid-1; i >= l; i--) {
		for(int j = 0; j < 128; j++) {
			dp[i][j] = dp[i+1][j^a[i]];
			dp[i][j] += dp[i+1][j^b[i]];
			if (dp[i][j] >= MOD) dp[i][j] -= MOD;
			Lxor[j].push_back(dp[i][j]);
		}
	}
	
	for(int i=mid+2; i <= r; i++) {
		for(int j = 0; j < 128; j++) {
			dp2[i][j] = dp2[i-1][j^a[i]];
			dp2[i][j] += dp2[i-1][j^b[i]];
			if (dp2[i][j] >= MOD) dp2[i][j] -= MOD;
			Rxor[j].push_back(dp2[i][j]);
		}
	}
	
	// printf("XX %d %d %d\n",l, r, mid);
	for(int i = 0; i < 128; i++) {
		vector<int> res;
		// if (i == 0) {
			// for(int k = 0; k < Lxor[i].size(); k++) {
				// printf("%d ",Lxor[i][k]);
			// } printf("\n");
			// for(int k = 0; k < Rxor[i].size(); k++) {
				// printf("%d ",Rxor[i][k]);
			// } printf("\n");
		// }
		multiply(Lxor[i], Rxor[i], res);
		for(int k = 0; k < r - l + 1; k++) {
			ans[k+1] += res[k];
			if (ans[k+1] >= MOD) ans[k+1] -= MOD;
		}
	}
}

void rec(int l, int r) {
	if (l == r) {
		if (a[l] == 0) ans[0]++;
		if (a[r] == 0) ans[0]++;
		return;
	}
	rec(l, (l+r)/2);
	rec((l+r)/2 + 1, r);
	process(l, r);
}

int main() {
	scanf("%d %d",&n, &MOD);
	for(int i = 1; i <= n; i++) scanf("%d",&a[i]);
	for(int i = 1; i <= n; i++) scanf("%d",&b[i]);
	
	rec(1, n);
	
	for(int i = 0; i < n; i++) printf("%d\n",ans[i]);
}