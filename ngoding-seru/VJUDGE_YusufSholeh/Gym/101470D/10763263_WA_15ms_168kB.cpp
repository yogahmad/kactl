#include <bits/stdc++.h>
using namespace std;

int x, y;
int main() {
	freopen("d.in", "r", stdin);
	scanf("%d %d",&x, &y);
	int n; scanf("%d",&n);
	while(n--) {
		int A; scanf("%d",&A);
		if (A == 1) {
			goto YES;
		} else {
			if (y % A == 0) {
				if ((x - 2)% A == 0) {
					goto YES;
				}
			} 
			if (x % A == 0) {
				if ((y - 2)%A == 0) {
					goto YES;
				}
			}
		}
		printf("NO\n");
		continue;
		YES:;
		printf("YES\n");
	}
}