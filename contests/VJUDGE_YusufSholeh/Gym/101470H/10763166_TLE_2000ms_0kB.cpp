#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m;
	scanf("%d %d",&m, &n);

	int ans = 0;

	for(int x = 0; x <= m; x++) {
		for(int y = x; y <= m; y++) {
			for(int z = y; z <= m; z++) {
				int haha = x*x + y*y;
				int hehe = z*z;
				if (haha == hehe) {
					ans += 1;
				}
			}
		}
	}

	// printf("%d\n",ans);

	for(int i = 3; i <= n; i++) {
		ans += m + 1;
	}

	printf("%d\n",ans);
}