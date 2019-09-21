#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9;

string a, b, c;
int l1, l2, l3;
int lps[105];

void makeLPS() { 
	lps[0] = 0;
	int i = 1, len = 0;
	while(i < l3) {
		if (c[i] == c[len]) {
			lps[i++] = ++len;
		} else {
			if (len != 0) len = lps[len - 1];
			else lps[i++] = len;
		}
	}
}

int dp[105][105][105];

int f(int p1, int p2, int p3) {
	if (p3 == l3) return -INF;
	if (p1 >= l1 || p2 >= l2) return 0;
	int &ret = dp[p1][p2][p3];
	if (ret != -1) return ret;
	ret = 0;
	if (a[p1] == b[p2]) {
		if (a[p1] == c[p3]) ret = max(ret, 1 + f(p1 + 1, p2 + 1, p3 + 1));
		else {
			int j = p3;
			while(j != 0) {
				if (a[p1] != c[j]) {
					j = lps[j-1];
				} else {
					ret = max(ret, 1 + f(p1+1, p2+1, j+1));
					break;
				}
			}
			if (j == 0) {
				if (a[p1] == c[0]) ret = max(ret, 1 + f(p1 + 1, p2 + 1, 1));
				else ret = max(ret, 1 + f(p1 + 1, p2 + 1, 0));
			}
		}
	}
	ret = max(ret, f(p1 + 1, p2, p3));
	ret = max(ret, f(p1, p2 + 1, p3));
}

void bt(int p1, int p2, int p3) {
	if (p3 == l3) return;
	if (p1 >= l1 || p2 >= l2) return;
	int ret = f(p1, p2, p3);
	if (a[p1] == b[p2]) {
		if (a[p1] == c[p3]) {
			if (ret == 1 + f(p1 + 1, p2 + 1, p3 + 1)) {
				printf("%c",a[p1]);
				bt(p1 + 1, p2 + 1, p3 + 1);
				return;
			}
		} else {
			int j = p3;
			while(j != 0) {
				if (a[p1] != c[j]) {
					j = lps[j-1];
				} else {
					if (ret == 1 + f(p1 + 1, p2 + 1, j+1)) {
						printf("%c",a[p1]);
						bt(p1 + 1, p2 + 1, j+1);
						return;
					}
				}
			}
			if (j == 0) {
				if (a[p1] == c[0] && ret == 1 + f(p1 + 1, p2 + 1, 1)) {
					printf("%c",a[p1]);
					bt(p1 + 1, p2 + 1, 1);
					return;
				} else {
					printf("%c",a[p1]);
					bt(p1 + 1, p2 + 1, 0);
					return;
				}
			}
		}
	}
	if (ret == f(p1 + 1, p2, p3)) {
		bt(p1 + 1, p2, p3);
		return;
	}
	if (ret == f(p1, p2 + 1, p3)) {
		bt(p1, p2 + 1, p3);
		return;
	}
}

int main() {
	cin >> a >> b >> c;
	l1 = a.length();
	l2 = b.length();
	l3 = c.length();
	makeLPS();
	memset(dp,-1,sizeof(dp));
	
	int ans = f(0,0,0);
	if (ans == 0) return printf("0\n")*0;
	bt(0,0,0);
	puts("");
	// printf("%d\n",f(0,0,0));
}