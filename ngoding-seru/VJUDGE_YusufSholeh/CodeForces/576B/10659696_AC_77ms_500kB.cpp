#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 5;

int n, p[MAX];
int base[2];
bool done[MAX];

int main() {
	scanf("%d",&n);
	for(int i = 1; i <= n; i++) scanf("%d",&p[i]);

	for(int i = 1; i <= n; i++) {
		if (i == p[i]) {
			printf("YES\n");
			for(int j = 1; j <= n; j++) 
				if (i != j) printf("%d %d\n",i, j);
			return 0;
		}
	}

	int min_cyc = 1e9;
	int pos = 0;

	for(int i = 1; i <= n; i++) {
		if (done[i]) continue;
		done[i] = true;

		int cyc_len = 1;
		int now = p[i];
		while(now != i) {
			cyc_len += 1;
			now = p[now];
			done[now] = true;
		}
		if (cyc_len & 1) goto fail;
		if (cyc_len < min_cyc) {
			min_cyc = cyc_len;
			pos = i;
		}
	}

	memset(done, false, sizeof done);

	if (min_cyc != 2) goto fail;

	base[0] = pos; base[1] = p[pos];
	done[base[0]] = done[base[1]] = true;
	printf("YES\n");
	printf("%d %d\n",base[0], base[1]);	
	for(int i = 1; i <= n; i++) {
		if (done[i]) continue;
		int proc = 0;
		int now = i;
		while(done[now] == false) {
			printf("%d %d\n",now,base[proc]);
			done[now] = true;

			now = p[now];
			proc = 1 - proc;
		}
	}
	
	return 0;
	fail:;
	printf("NO\n");
}