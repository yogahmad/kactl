#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int ans[N];
int f[N];

int dp(int x, int k) {
	if (x == 0) {
		return 0;
	}
	if (f[x] != 0) return f[x];
	set<int> st;
	st.insert(dp(x-1,k));

	if (x % 2 == 0) {
		int val = dp(x/2,k);
		if (k % 2 == 0) {
			val = 0;
		}
		st.insert(val);
	}

	int cur = 0;
	for(;;) {
		if (st.find(cur) == st.end()) 
			return f[x] = cur;
		cur += 1;
	}
}

int nim(int x, int k) {
	if (k % 2 == 0) {
		if (x % 2 == 1) {
			if (x == 1) return 1;
			return 0;
		} else {
			if (x == 2) return 2;
			return 1;
		}
	} else {
		if (x < 54) return ans[x];
		if (x % 2 == 1) return 0;
		if (nim(x/2,k) == 1) return 2;
		return 1;
	}
}

int main() {
	for(int x = 1; x < 3000; x++) {
		ans[x] = dp(x, 1);
	}

	int n, k;
	int ans = 0;
	scanf("%d %d",&n, &k);
	for(int i = 1; i <= n; i++) {
		int xx;
		scanf("%d",&xx);
		ans ^= nim(xx, k);
	}
	
	puts(ans > 0 ? "Kevin" : "Nicky");

	return 0;
}