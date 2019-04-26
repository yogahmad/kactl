#include<bits/stdc++.h>
#define LL long long
using namespace std;

#define MAX 50005

const LL base = 31;
char S[MAX];

int main() {
	int tc; scanf("%d",&tc);
	for(int cs = 1; cs <= tc; cs++) {
		scanf("%s",S);
		int len = strlen(S);
		
		int j = len-1;
		
		int ans = 0;
		LL hashL = 0, hashR = 0, hash = 1;
		for(int i = 0; i < len; i++) {
			if (i >= j) break;
			LL valL = (LL)S[i] - 'A' + 1;
			LL valR = (LL)S[j] - 'A' + 1;
			hashL = hashL * base + valL;
			hashR = hashR + valR * hash;
			hash = hash * base;
			if (hashL == hashR) {
				ans += 2;
				hashL = 0, hashR = 0, hash = 1;
				if (i + 1 == j - 1) {
					ans += 1;
					break;
				}
			}
			j--;
		}
		if (hashL != hashR) ans += 1;
		printf("Case #%d: %d\n",cs, ans);
	}
}	