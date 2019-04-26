#include<bits/stdc++.h>
#define MAX 100005
using namespace std;

int n;
int arr[MAX];
int sepuluh[MAX];
int dp[10000005];
bool vis[10000005];

int countDigit(int num) {
	int ret = 0;
	while(num > 0) {
		ret++;
		num/=10;
	}
	return ret;
}

int id[MAX][10];

inline void getId(int pos, int num) {
	int ujung = 0;
	while(num > 0) {
		id[pos][ujung++] = num % 10;
		num /= 10;
	}
}

inline int rubah(int idx, int pos, int y) {
	return arr[idx] - sepuluh[pos] * id[idx][pos] + sepuluh[pos] * y;
}

int len = -1;

int main() {
	sepuluh[0] = 1;
	for(int i = 1; i <= 10; i++) sepuluh[i] = 10 * sepuluh[i-1];
	
	scanf("%d",&n);
	for(int i = 1; i <= n; i++) {
		scanf("%d",&arr[i]);
		if (len == -1) len = countDigit(arr[i]);
		getId(i, arr[i]);
	}
	
	int ans = 0;
	for(int i = n; i >= 1; i--) {
		// printf("===============\ni : %d\n",i);
		if (vis[arr[i]] == false) {
			vis[arr[i]] = true;
			dp[arr[i]] = 0;
		}
		for(int j = 0; j < len; j++) {
			for(int k = (j < len-1) ? 0 : 1; k < 10; k++) {
				int diff = id[i][j] - k;
				if (diff < 0) diff = - diff;
				int next = rubah(i, j, k);
				// printf("%d\n",next);
				if (vis[next] == false) continue;
				dp[arr[i]] = max(dp[arr[i]], diff + dp[next]);
				ans = max(ans, dp[arr[i]]);
			}
		}
		// printf("%d %d %d\n",i,arr[i],dp[arr[i]]);
	}
	
	printf("%d\n",ans);
}