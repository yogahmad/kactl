#include<bits/stdc++.h>
#define MAX 1005
#define INF 1000000
using namespace std;
inline char cer(char c) {
	if (c == 'b') return 'd';
	if (c == 'd') return 'b';
	if (c == 'p') return 'q';
	if (c == 'q') return 'p';
	return c;
}
int n, L;
int dp[MAX][MAX][2];
char s1[MAX], s2[MAX];
int f(int l, int r, bool s) {
	int tgt = n - (r - l) - 1;
	if (l > r) return 0;
	int &ret = dp[l][r][s];
	if (ret != INF) return ret;
	ret = INF*5;
	if (s2[tgt] == s1[l]) ret = min(ret, f(l + 1, r, s) + s);
	if (s2[tgt] == cer(s1[r])) ret = min(ret, f(l, r - 1, !s) + !s);
	return ret;
}
int main() {
	while(scanf("%d",&n) != EOF) {
		for(int i = 0; i < MAX; i++) {
			for(int j = 0; j < MAX; j++) {
				dp[i][j][0] = INF;
				dp[i][j][1] = INF;
			}
		}
		scanf("%s %s",&s1, &s2);
		L = strlen(s1);
		int ans = f(0,L - 1,0);
		if (ans >= INF) printf("-1\n");
		else printf("%d\n",ans);
	}
}