#include<bits/stdc++.h>
#define LL long long
using namespace std;

#define MAX 505

int dp[MAX][MAX];
char S[MAX];
int n;
int count_digit[MAX];

int lps[MAX][MAX];

int f(int l, int r) {
	if (l == r) return 1;
	int &ret = dp[l][r];
	if (ret >= 0) return ret;
	ret = 1e9;
	
	ret = min(ret, r-l+1);
	
	int i = l;
	int j = r;
	int pjg = j-i+1;
	int back = lps[i][j-i];
	if (back >= (pjg + 1)/2) {
		back = pjg - back;
		if (back && pjg % back == 0) {
			for(int period = back; period <= pjg; period += back) {
				if (pjg % period == 0) {
					int val;
					if (period == 1) {
						val = count_digit[pjg / period];
					} else {
						val = count_digit[pjg / period] + 2;
					}
					ret = min(ret, val + f(l, l+period-1));
				} else break;
			}
		}
	}
	
	for(int i = l; i < r; i++) {
		ret = min(ret, f(l,i) + f(i+1,r));
	}
	
	return ret;
}

int construct_lps(int idx, string pat) {
	int pjg = pat.length();
	int i = 1, len = 0;
	lps[idx][0] = 0;
	while(i < pjg) {
		if (pat[i] == pat[len]) {
			len++;
			lps[idx][i] = len;
			i++;
		} else {
			if (len != 0) len = lps[idx][len-1];
			else lps[idx][i++] = len;
		}
	}
}

int main() {
	
	for(int i = 1; i < MAX; i++) {
		int a = i;
		int ret = 0;
		while(a > 0) {
			ret++;
			a/=10;
		}
		count_digit[i] = ret;
	}
	
	int cs = 0;
	while(true) {
		scanf("%s",&S);
		n = strlen(S);
		
		// for(int i = 0; i < MAX; i++) {
			// for(int j = 0; j < MAX; j++) {
				// lps[i][j] = 0;
			// }
		// }
		
		for(int i = 0; i < n; i++) {
			string tmp = "";
			for(int j = i; j < n; j++) {
				tmp += S[j];
			}
			construct_lps(i, tmp);
		}
		
		if (S[0] == '0') return 0;
		
		
		
		printf("Case #%d: ",++cs);
		memset(dp,-1,sizeof(dp));
		
		printf("%d\n",f(0,n-1));
	}
}	