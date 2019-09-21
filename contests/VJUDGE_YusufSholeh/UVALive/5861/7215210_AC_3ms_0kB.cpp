#include<bits/stdc++.h>
#define MAX 105
using namespace std;

int x[MAX], y[MAX];

inline int check(int a, int b, int c, int d, int r) {
	int absx = abs(c - a);
	int absy = abs(d - b);
	int absr = r;
	return (absx*absx + absy*absy <= absr*absr);
}

int main() {
	while(true) {
		int n;
		scanf("%d",&n);
		if (!n) break;
		
		int r;
		scanf("%d",&r);
		for(int i = 1; i <= n; i++) scanf("%d %d",&x[i], &y[i]);
		
		int ans = 0;
		
		for(int i = 1; i <= n-2; i++) {
			for(int j = i+1; j <= n-1; j++) {
				for(int k = j+1; k <= n; k++) {
					int wpij = check(x[i], y[i], x[j], y[j], r);
					int wpik = check(x[i], y[i], x[k], y[k], r);
					int wpkj = check(x[j], y[j], x[k], y[k], r);
					
					ans += (wpij + wpik + wpkj == 2);
				}
			}
		}
		
		printf("%d\n",ans);
	}
}